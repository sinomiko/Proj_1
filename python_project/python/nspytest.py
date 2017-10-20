#!/usr/bin/python
# -*- coding: iso-8859-1 -*-
#
# $Id:$
#
# Copyright (c) Ericsson Espa帽a S.A., 2011.
# All rights reserved.
#
# This product or document is proprietary to and embodies the
# confidential technology of Ericsson Espa帽a S.A.
# Possession, use, duplication or distribution of this product
# or document is authorized only pursuant to a valid written
# license from Ericsson Espa帽a S.A
#

import os
import re
import sys
import yaml
import imp
import getpass
from optparse import OptionParser

##########################
## BEGIN METHOD main()
##########################
def main():
    assert getpass.getuser() == 'netspira', "Please, use the user netspira to run test suites"
    parser = get_parser_options()
    (options, args) = parser.parse_args()
    test_suite_options = None

    if (len(args)<1):
        parser.print_help(None)
        exit(-1)
        assert os.path.exists(options.log_directory), "Log direcotry does not exist!!"

    test_suite_config = args[0]
    logs_directory = options.log_directory
    distribution_file = options.dist_file
    dbname = options.dbname
    dbreference_name = options.dbreference_name
    regression_id = options.regression_id
    mtt_baseline_path = options.mtt_baseline_path

    if (options.debug == False and len(args) > 1):
        print "..... ERROR: --debug option not activated and received extra options for test-suite: %s" % args[1:]
        sys.exit(1)

    if (len(args) > 1):
        test_suite_options = " ".join(args[1:])
        print "..... WARNING: Running nspystest with DEBUG test_suite_options: [%s]" % test_suite_options

    # getting the provided priority threshold if any.
    priority_threshold = None
    if (options.priority):
        if (re.match("LOW|MEDIUM|HIGH|SUPER", options.priority)):
            if (options.priority == "SUPER"):
                priority_threshold = 1000
            elif (options.priority == "HIGH"):
                priority_threshold = 100
            elif (options.priority == "MEDIUM"):
                priority_threshold = 50
            else:
                priority_threshold = 0
        elif (re.match("\d+", options.priority)):
            priority_threshold = int(options.priority)
        else:
            #ignore priority
            print "WARNING: bad priority='%s' IGNORED"

    # do some magic, to instance the TestSuite class
    test_suite_class = load_test_suite_env(test_suite_config)

    # initialize the class
    try:
        if not options.debug:
            sasn_test_suite = test_suite_class(test_suite_config,
                                           logs_directory,
                                           distribution_file)

        else:
            sasn_test_suite = test_suite_class(test_suite_config,
                                       logs_directory,
                                       distribution_file,
                                       dbname,
                                       regression_id,
                                       dbreference_name,
                                       test_suite_options)

        # if --mtt-baseline-path is specified
        if mtt_baseline_path:
            sasn_test_suite.set_mtt_baseline_path(mtt_baseline_path)

        # set the priority_threshold
        if (priority_threshold):
            sasn_test_suite.setPriorityThreshold(priority_threshold)

        # Action!
        try:
            sasn_test_suite.run()
        except:
            del sasn_test_suite
             raise
    except:
        from NSTpyfw.utils.sharedValuesTable import get_shared_value
        print get_shared_value("SSH_STORY")
        raise

    return sasn_test_suite


## END METHOD main()


###################################
## BEGIN METHOD get_parser_options()
###################################
def get_parser_options():
    """
    Return a OptionParser object to extract all the options passed as arguments

    @rtype: OptionParser
    """
    usage = "usage: %prog [options] config_test_suite.yml"

    parser = OptionParser(usage = usage)
    parser.allow_interspersed_args = False

    parser.add_option("-l", "--local",
                  default=None,
                  dest = "dist_file",
                  help="Local distribution file to install in a PPU Entity")

    parser.add_option("-o", "--output",
                  default="/tmp",
                  dest = "log_directory",
                  help="Final directory where result files will be")

    parser.add_option("-p", "--prio",
                  default=None,
                  dest = "priority",
                  help="Priority Threshold. Integer values or either one of the following values are accepted: {LOW(0)|MEDIUM(50)|HIGH(100)|SUPER(1000)}")

    parser.add_option("-b", "--db",
                  default="default_db",
                  dest = "dbname")

    parser.add_option("-r", "--dbreference",
                  default="default_db_reference",
                  dest = "dbreference_name")

    parser.add_option("-n", "--regression-id",
                  default=0,
                  dest = "regression_id",
                  help="Number to associate test-suite runs to the same regression. Normally it is the pid of the regression script")

    parser.add_option("-d", "--debug",
                  action="store_true",
                  default=False,
                  dest = "debug",
                  help="Debug option if activated allow passing extra options to test-suite (Not allowed for Jenkins regressions)")

    parser.add_option("--mtt-baseline-path",
                  default=None,
                  dest = "mtt_baseline_path",
                  help="Path to a baseline to compare HLs and run a MTT regression")



    return parser
## END METHOD get_parser_options()

def load_test_suite_env(ts_yml_file):
    '''
    This method loads a new TestSuite of NSTpyfw dynamically. To do that,
    a specific configuration file is needed. This YAML file MUST contain
    the "nspytest" field. The entity may be any object type that extends
    from TestSuite class, e.g. AnalyserTestSuite, etc...

    @param ts_yml_file: A file's path with specific configuration of TestSuite.
    @type ts_yml_file: str
    @return: The entity generated dynamically
    @rtype: TestSuite instance name class
    '''

    node_info = yaml.load(file(ts_yml_file))

    #checks if the "type" field exists
    assert("nspytest" in node_info)

    nspytest_data =  node_info["nspytest"]

    #checks if the arguments needed are into "type" field
    assert(("test_suite_module" in nspytest_data) and\
           ("test_suite_class" in nspytest_data) and\
           ("test_suite_path" in nspytest_data))


    test_suite_path = nspytest_data["test_suite_path"]

    sys.path.append(test_suite_path)

    ##Setting django enviroment varibles: a terror!!
    #current work directory anyhow
    os.chdir(test_suite_path) ## change to project directory

    cmd_import = "from %s import %s" %(nspytest_data["test_suite_module"], nspytest_data["test_suite_class"])
    exec cmd_import in globals()


    #checks that the module and class exits
    new_module = None
    try:
        #checks if the module is already loaded
        new_module  = sys.modules[nspytest_data["test_suite_module"]]
    except KeyError:
        pass

    if not(new_module):
        #When the module is not loaded, is looked for.
        fp, pathname, description = imp.find_module(nspytest_data["test_suite_module"])

        try:
            #if the module was found, it tries to load. If the module was not found
            #the next line must throw a Exception
            new_module = imp.load_module(nspytest_data["test_suite_module"], fp, pathname, description)
        finally:
            # Since we may exit via an exception, close fp explicitly.
            if fp:
                fp.close()

    #Checks if the module was found and loaded
    assert(new_module)

    #checks the class is in the module
    class_name = getattr(new_module, nspytest_data["test_suite_class"])
    assert(class_name)

    return class_name

## END METHOD load_test_suite_env()



if __name__ == '__main__':
    main()
