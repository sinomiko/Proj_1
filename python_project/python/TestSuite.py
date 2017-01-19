# -*- coding: iso-8859-1 -*-
#
# $Id: testSuite.py,v 1.78 2013/03/20 15:48:27 xantgui Exp $
#
# Copyright (c) Ericsson Espa锟絘 S.A., 2011.
# All rights reserved.
#
# This product or document is proprietary to and embodies the
# confidential technology of Ericsson Espa锟絘 S.A.
# Possession, use, duplication or distribution of this product
# or document is authorized only pursuant to a valid written
# license from Ericsson Espa锟絘 S.A
#
''''
Main class in order to do a new regression Test Suite.
'''

from NSTpyfw import NO_LOAD_NEEDED
from NSTpyfw.logger import Logger
from NSTpyfw.metrics.disk_free_info import DiskFreeInfo
from NSTpyfw.yamlConfigurable import YamlConfigurable
from NSTpyfw import sharedValuesHandler
from NSTpyfw.testmgmt.testSuiteResult import TestSuiteResult
from NSTpyfw.testmgmt.testCaseResult import TestCaseResult, TestCaseResultCode
from NSTpyfw.testmgmt.testResultsReporter import TestResultReporter
from NSTpyfw.testmgmt.exceptions import NetworkTestError
from NSTpyfw.testmgmt.testCase import TestCase
from NSTpyfw.testmgmt.mttRegressionTestCase import MttRegressionTestCase
from multiprocessing import Process, Queue
from Queue import Empty
from NSTpyfw.ppuEntity import PPUEntity
from NSTpyfw.utils.testCaseTimeout import TestCaseTimeout
from NSTpyfw.utils.execution_mode import ExecutionMode
from NSTpyfw.configManager import ConfigManager
from NSTpyfw.configuration.oneConfig import ConfigurationInformation
from NSTpyfw.utils.libssh.tunnelier import SSHTunnelier
import NSTpyfw.sshConnectionResultMgr
from NSTpyfw.utils.local_shell_connection import LocalShellConnection
from NSTpyfw.utils.exception.testmgmt import InvalidTestCaseYamlFileException
from NSTpyfw.utils.rollbacker import Rollbacker
from NSTpyfw.utils.exception.localshellconnection import LocalShellConnectionException
from NSTpyfw.testmgmt.testInitializer import TestInitializer
from NSTpyfw.utils.exception.ssr import AliWithIPZeroException
from NSTpyfw.utils.oamCommands import OAMCommands
import yaml
import sys, traceback
import logging
import glob
import imp
import os
import time
import re
import subprocess

class TestSuite(YamlConfigurable):
  '''
    Handles a SASN regressions with NSTpyfw. This class contains the main logic
    to run every test suite. There are three important methods which contain
    all the main logic to run (see L{run} method):
        1. L{main_pre_condition}
        2. L{main_start}
        3. L{main_post_condition}

    If it is needed, every test suite can run a specific logic overwriting
    L{pre_condition}, L{start} and L{post_condition} methods. The specific
    logic defined in L{pre_condition} and L{post_condition} will be run at the
    end of L{main_pre_condition} and L{main_post_condition} methods. The
    L{start} method must be used to set into the test cases general parameter
    of the test suites (the same data for all the test cases).

    @cvar TIMED_OUT_TESTCASE_ERROR: Default value to set in the
                                    L{NSTpyfw.testmgmt.TestCaseResult} as
                                    "result" when the time out happens
    @cvar MAX_TEST_CASE_DURATION: Default value to set the time out for a test
                                  cases execution.

    @ivar SUCCESS_EXIT_CODE: This code is returned when a process ends properly
    @ivar COMMON_ERROR_EXIT_CODE: This code is returned when a process does not
                                  end properly
    @ivar NETWORK_FATAL_ERROR_EXIT_CODE: This specific error code is returned
                   when a process detects a network error. If this error is
                   found, the test suite would end immediately.
    @ivar EXECUTION_MODE_OPTIONS: Execution modes allowed are "standalone",
                   "standalone-remote" and "cluster". One of them should be
                   chosen depending on the execution environment:
                   standalone: the SUT is localhost (example: NSTanalyzer)
                   standalone-remote: the SUT is a remote unique machine \
                   (example: NSTgy on VMs)
                   cluster: the SUT is a remote cluster (example: NSTgy on a cluster)

    @ivar DEFAULT_SAVE_CORE_DUMP_THRESHOLD: Specific default value to set when the new core
                   dumps found must be save in the test case directory
    '''
    TIMED_OUT_TESTCASE_ERROR = 10
    MAX_TEST_CASE_DURATION = 600

    #Specific errors to exit of a process
    SUCCESS_EXIT_CODE = 0
    COMMON_ERROR_EXIT_CODE = 1
    NETWORK_FATAL_ERROR_EXIT_CODE = 30
    EXECUTION_MODE_OPTIONS = ["standalone", "standalone-remote", "cluster", "ssr_hl", "com"]

    ROUTER_SSR_CONFIGURATION = ["/opt/nstest/config/gi-ssr-config.mako"]

    #Specific default value to set when the new core dumps found must be save in the test case directory
    DEFAULT_SAVE_CORE_DUMP_THRESHOLD = 10

    # these two class variables will be used to pass information between the
    # process which runs the test case and the main process.
    current_test_case_class_name = ""
    current_test_case_name = ""
    current_test_case_filename = ""



    def __init__(self, config_file_path, log_directory = None,
                 distribution_file_path = None):
        '''
        Creates a new SASN Test Suite. It will be formed by several Test Case.
        If will be possible to configure a specific distribution to run the
        test cases.  To configure the Test Suite is necessary a configuration
        file with several mandatory fields.

        @param config_file_path: The test suite YAML file path.
        @type  config_file_path: str
        @param log_directory: The directory path to store the test suite logs.
                              It's optional.  If not defined, the default
                              directory is "/tmp"
        @type  log_directory: str
        @param distribution_file_path: The distribution file path to install.
                                       It's optional.  If not defined, the test
                                       suite would be run in an existing
                                       installation of SASN.  @type
                                       distribution_file_path: str
        '''
        #Initialize config yaml variables
        self.name = ""
        self.type = ""
        self.description = ""
        self.test_specification_doc_list = None
        #############################
        #TODO: Removes the variable when the compatibility for old test suite was not needed
        self.ppu_entity_config = None
        #############################
        self.execution_mode = ""
        self.hardware_mode = None
        self.force_restart_of_entity = False
        self.dut_config_templates = None
        self.dut_yml_file = None
        self.dut_only_ipv4_config = False
        self.test_cases_pattern_list = []
        self.tc_cluster_only = []
        self.skip_test_cases_pattern_list = []
        self.test_cases_priority_rules = []
        self.logger_config = None
        self.logger_level = None
        self.modules_set_logging = []
        self.verbose = None
        self.warning_loggers = None
        self.max_testcase_duration = None
        self.save_logs_for_passed_tests = False
        self.save_test_yaml_files = False
        self.check_if_sessions_are_deleted = False
        self.check_distribution_info = True
        self.sasn_log_level = "DEBUG"
        self.core_dumps_action = TestCase.DEFAULT_CORE_DUMPS_ACTION
        self.save_core_dumps_threshold = self.DEFAULT_SAVE_CORE_DUMP_THRESHOLD
        self.common_assertions = None
        self.my_ppu_entity = None

        #Init. external variables
        self.distribution_file = distribution_file_path
        self.mtt_baseline_path = None


        #Init. internal variables
        self.run_test_cases_list = []
        self.skipped_test_cases_list = []
        self.priority_rulez = []
        self.test_case_result = None
        self.priority_threshold = 0
        self.prio_cache = {}
        self.use_type_connection = "nssh"
        self.use_mt = False
        ## Amount of APPVMS to be used in the test
        self.appvms = 2
        # If present do not load IPOS
        self.do_not_load_ipos = None


        #initialize parent class
        YamlConfigurable.__init__(self)

        #load yaml configuration of SASN
        self.config_yaml_file = config_file_path
        self.config_test_suite = yaml.load(file(self.config_yaml_file))
        self.set_node(self.config_test_suite)
        self.load_yaml_config()

        # here we already have initialized the self.name and self.test_specification_doc_list 
        # variable, so we can propperly initialize the TestSuiteResult var.
        self.result = TestSuiteResult(self.name, self.__module__, self.test_specification_doc_list)


        #creates the directory to test suite
        self.log_directory = self.__create_ts_directory(log_directory)

        #Parse level values
        if not (self.logger_level):
            self.logger_level = logging.DEBUG
        else:
            self.logger_level = eval("logging.%s" %(self.logger_level))

        if not (self.verbose):
            self.verbose = logging.ERROR
        else:
            self.verbose = eval("logging.%s" %(self.verbose))


        if not (self.max_testcase_duration):
            self.max_testcase_duration = TestSuite.MAX_TEST_CASE_DURATION

        Logger(config_file = self.logger_config, verbose = self.verbose)
#        logging.getLogger("root").setLevel(logging.WARNING)

        ## Set migration tool usage
        cm = ConfigManager()
        mt_config = {"use_mt": self.use_mt}
        cm.loadConfig("migration_tool", mt_config, True)

        #it checks whether the sasn cluster config file exists in order to
        #be able to continue with the test.
        ppu_entity_config = None
        ##############################
        #TODO: Removes the logic when the compatibility for old test suite was not needed
        if self.ppu_entity_config:
            ppu_entity_config = yaml.load(file(self.ppu_entity_config))
            if ("standalone" in ppu_entity_config.keys()):
                ppu_entity_config["execution_mode"] = self.EXECUTION_MODE_OPTIONS[0]
            else:
                ppu_entity_config["execution_mode"] = self.EXECUTION_MODE_OPTIONS[2]

            logging.getLogger("NSTlogger").error("Please, update your test suite to use the NSTpyfw "\
                    "unique config ASAP. The compatibility mode for old versions will be removed soon.")
        ##############################
        else:
            exec_mode = ExecutionMode()
            temp_execution_mode = exec_mode.get_execution_mode(self.execution_mode)
            assert temp_execution_mode != None , \
                                           "Wrong execution_mode %s" \
                                           % self.execution_mode
            if self.execution_mode != temp_execution_mode:
                logging.getLogger("NSTlogger").warning("TestSuite - New execution mode was set "\
                   " [%s] while defined one was [%s]" % (temp_execution_mode, self.execution_mode))
            else:
                logging.getLogger("NSTlogger").info("TestSuite - Execution mode:"\
                   " %s" % temp_execution_mode)
            self.execution_mode = temp_execution_mode

            self.network_config_file = exec_mode.get_configuration_file(self.execution_mode)

#             if not os.path.exists(self.network_config_file):
#                 if self.execution_mode == "standalone-remote":
#                     self.network_config_file = "/opt/nstest/etc/gi-network-cluster-config.yml"
#                 elif self.execution_mode == "cluster":
#                     self.network_config_file = "/opt/nstest/etc/gi-network-standalone-remote-config.yml"

            logging.getLogger("NSTlogger").info("TestSuite - Network config"\
                   " file defined --> %s" % (self.network_config_file))

            #creates a PPU Entity for this Test Suite dynamically.
            network_config = yaml.load(file(self.network_config_file))
            ppu_entity_config = network_config["ppu_entity"]
            #add the execution_mode to the ppu_entity_config
            ppu_entity_config["execution_mode"] = self.execution_mode
            #add the hardware_mode to the ppu_entity_config
            ppu_entity_config["hardware_mode"] = self.hardware_mode
            ## Add the type of connection
            ppu_entity_config["use_type_connection"] = self.use_type_connection
            ## Add the number of APPVM that the test will need
            ppu_entity_config["max_number_appvms"] = self.appvms
            #complete ppu_entity_config with information from the network_config
            act_ppu_index = 0
            for entity_key in ("master", "backup", "standalone","ppu"):
                if ppu_entity_config.get(entity_key):
                    for i_entity, entity in enumerate(ppu_entity_config[entity_key]):
                        #From SSR releases a new entry profile has been defined
                        if network_config["ppu_entity"].get("profile"):
                            entity["profile"] = network_config["ppu_entity"]["profile"]
                        else:
                            #For oracle versions hardware entry will be used
                            entity["profile"] = network_config["hardware"]
                        if entity_key == "standalone":
                            entity["name"] = \
                              network_config["_hostnames"]["backup-server"]
                        elif entity_key == "master":
                            entity["name"] = \
                              network_config["_hostnames"]["server" + str(i_entity)]
                        elif entity_key == "backup":
                            if i_entity == 0:
                                entity["name"] = \
                                  network_config["_hostnames"]["backup-server"]
                            else:
                                entity["name"] = \
                                  network_config["_hostnames"]["backup-server" + str(i_entity)]
                        elif entity_key == "ppu":
                            assert "role" in entity, "No role configured in entity number %d." % i_entity
                        ## End If
                    ## End For
                ## End If
            ## End For
        ## End If
        assert ppu_entity_config, "Wrong ppu_entity_config value found. Please, check your test suite yaml."

        self.my_ppu_entity = self.generate_dynamic_entity\
                                  (ppu_entity_config)

        # aggregate the ppu entity to the testSuiteResult artifact, so it can
        # extract interesting data on reports.
        self.result.setTargetSUTInfo( self.my_ppu_entity )

        self.initial_df_info = None

        ## Check if the environment is SSR to deactivate by default
        ## the security
        if ExecutionMode().get_is_ssr(self.execution_mode):
            self.my_ppu_entity.perform_action("configuration", "enable RPCM")
            self.my_ppu_entity.perform_action("security", "disable")
            self.my_ppu_entity.perform_action("commit", "set parallel")
            self.my_ppu_entity.enable_testing_mode("smaller tsm tables", True)
        ## End If

    ## END METHOD __init__()

    def __repr__(self):
        """
        Return a string representation of this object, for debugging.

        @rtype: str
        """
        out = '{TestSuite'
        for i in ("name", "type", "description", "param", "my_ppu_entity"):
            out += ' %s=%s' % (i, repr(eval("self."+i)))
        out += '}'

        return out
    ## END METHOD __repr__()
    def __del__(self):
        """
        Destructor.
        """
        if self is not None and self.my_ppu_entity is not None:
            self.my_ppu_entity.destroy()
        ## End If
        del(self.my_ppu_entity)

    ## END METHOD __del__()

    def setPriorityThreshold(self, priority_threshold):
        """
        Sets priority threshold
        """
        self.priority_threshold = priority_threshold
    ## END METHOD setPriorityThreshold

    def set_mtt_baseline_path(self, mtt_baseline_path):
        """
        Sets the mtt baseline path for this kind of execution
        """
        self.mtt_baseline_path = mtt_baseline_path

    def run(self):
        """
        This method invokes the main logic of the test suite. The logic of the
        test suite is in three methods : L{main_pre_condition}, L{main_start}
        and L{main_post_condition}.
        """
        #Runs the pre-conditions of the test suite
        self.main_pre_condition()

        #Runs the test cases of the test suite
        self.main_start()

        #Runs the post-conditions of the test suite
        self.main_post_condition()


    def start_process_wrapper (self, current_test_case, queue):
        '''
        Contains the logic for a test case so it can be started in an
        The queue is used for returning the test case verdict

        @param current_test_case: The test case yaml file path to run in an independent
                          process.
        @type  current_test_case: str
        @param queue: The queue is used for returning the test case verdict
        @type  queue: Queue
        '''
        #TODO use the received one instead of re-creating it
        #self.my_ppy_entity = my_ppu_entity

        # xiakfer, Eclipse/PyDev multiprocess debugging:
        # A new process is forked here. Eclipse/PyDev cannot follow the fork
        # into the subprocess, but can be attached manually to the subprocess.
        # On the other hand, GDB is capable of following the forked process,
        # Python included.
        # Workaround for eclipse/pydved: remote debugging option of manually
        # inserting calls to pydevd.settrace(). Subsequent PyDev breakpoints
        # are obeyed.
        # We explicit settrace call to establish the remote debugging session
        # for the process, and afterwards just use the normal debugger
        # breakpoints.
        # Insert the pydevd.settrace code somewhere early in the initialization
        # of the subprocess. Still a bit of a hack, but better than suspending
        # the process manually
        #
        # NOTE that pydevd.settrace is run in tc_proc.start
        # (start_process_wrapper), where the suprocess is initialized.
        #
        if os.environ.get("PYDEVDEBUGTESTSUITEPROC"):
            #xiakfer:
            logging.getLogger("NSTlogger").\
                    debug('settint trace for pydev debugging')
            # pydevd's settrace default values:
            try:
                import pydevd
                pydevd.settrace(stdoutToServer = True,
                                stderrToServer = True,
                                suspend = True,
                                trace_only_current_thread = False)
            except ImportError:
                logging.getLogger("NSTlogger").\
                        warning("PyDevd not found in PYTHONPATH.PyDev "\
                                "multiprocess debugging cannot be triggered")



        #Updating the test case process with the shared values
        sharedValuesHandler.get_shared_value_handler().update_process()

        # Retrieve some values from the sharedValued File.
        current_test_case.tc_filename = TestSuite.current_test_case_filename

        # Update the Shared Values with the main thread
        TestSuite.current_test_case_class_name = current_test_case.__class__.__name__
        TestSuite.current_test_case_name = current_test_case.name

        # Dumping the shared values to the file. We want this data even if the
        # TestCase crasshes by an assert ...
        sharedValuesHandler.get_shared_value_handler().update_shared_values()

        logging.getLogger("NSTlogger").testinfo( \
                "TestSuite - Test Case Description: %s" %(current_test_case.description))

#         self.my_ppu_entity.init_ssh_connections()

        if (current_test_case.get_save_logs_for_passed_tests() == None):
            current_test_case.set_save_logs_for_passed_tests\
                             (self.save_logs_for_passed_tests)

        if (hasattr(current_test_case,'check_if_sessions_are_deleted') and \
                current_test_case.get_check_if_sessions_are_deleted() == None):
            current_test_case.set_check_if_sessions_are_deleted\
                             (self.check_if_sessions_are_deleted)

        if (current_test_case.get_sasn_log_level() == None):
            current_test_case.set_sasn_log_level(self.sasn_log_level)

        if (current_test_case.get_core_dumps_action() == None):
            current_test_case.set_core_dumps_action(self.core_dumps_action)


        if (current_test_case.get_save_core_dumps_threshold() == None):
            current_test_case.set_save_core_dumps_threshold(self.save_core_dumps_threshold)

        if current_test_case.modules_set_logging == None:
            current_test_case.modules_set_logging = self.modules_set_logging

        if current_test_case.use_mt == None:
            current_test_case.use_mt = self.use_mt

        if hasattr(current_test_case, "common_assertions") and self.common_assertions:
            if not current_test_case.common_assertions:
                current_test_case.common_assertions = {}
            for item in self.common_assertions:
                if self.common_assertions[item]:
                        current_test_case.common_assertions[item].extend(self.common_assertions[item])
                    else:
                        current_test_case.common_assertions[item] = self.common_assertions[item]

        #Specific logic is run by every test case created.
        self.start(current_test_case)

        if current_test_case.max_testcase_duration:
            max_current_testcase_duration = current_test_case.max_testcase_duration
        else:
            max_current_testcase_duration = self.max_testcase_duration

        TestCaseTimeout().set_value(max_current_testcase_duration)
        TestCaseTimeout().test_started()

        try:
            current_test_case.run()
        except KeyboardInterrupt:
            sys.exit(-1)
        except NetworkTestError:
            etype, value, traceb = sys.exc_info()
            error_exception_lines = traceback.format_exception(etype, value, traceb)
            logging.getLogger("NSTlogger").exception(error_exception_lines)
        except AliWithIPZeroException:
            logging.getLogger("NSTlogger").error("SSR error platform detected")
            self.__ali_with_IP_zero_procedure()
            current_test_case.exception_condition()
        except:
            current_test_case.exception_condition()

        queue.put (current_test_case.get_verdict())

        if (current_test_case.get_verdict().result == TestCaseResultCode.\
                                                      SUCCESS_RESULT):
            logging.getLogger("NSTlogger").\
                    testinfo("TestCase: %s - Result: PASSED" \
                        %(current_test_case.get_verdict().test_case_name))
        else:
            logging.getLogger("NSTlogger").\
                    testinfo("TestCase: %s - Result: FAILED" \
                        %(current_test_case.get_verdict().test_case_name))

         #The warning.log file is removed if empty
        warning_file_path = os.path.join(current_test_case.log_directory, "WARNING.log")
        warning_file = open(warning_file_path)
        warning_data = warning_file.read()
        warning_file.close()
        if len(warning_data) == 0:
            os.remove(warning_file_path)
        current_test_case = None

        # We save again the shared values, the TestSuite may have added some
        # new variables to the Shared stash.
        sharedValuesHandler.get_shared_value_handler().update_shared_values()

        sys.exit()
    ## END METHOD start_process_wrapper()

    def main_start(self):
        '''
        Runs the test cases defined in the Test Suite config file. Every test
        case found, that is not present in skip list, will be executed. It
        creates a Process per test case in a transparent way.

        When it is needed to set general parameter of the test suite to the
        test case, it can overwrite the L{start} method.
        '''

       logging.getLogger("NSTlogger").testinfo("")
       logging.getLogger('NSTlogger').testinfo("###########################################")
       logging.getLogger("NSTlogger").testinfo("###########################################")
       logging.getLogger("NSTlogger").testinfo("RUN TEST CASES")
       logging.getLogger("NSTlogger").testinfo("###########################################")
       logging.getLogger("NSTlogger").testinfo("")

        # Add the current_test_case_class_name
        sharedValuesHandler.get_shared_value_handler().add_shared_value(\
                      "from NSTpyfw.testmgmt.testSuite import TestSuite",
                                "TestSuite.current_test_case_class_name")
        sharedValuesHandler.get_shared_value_handler().add_shared_value(\
                      "from NSTpyfw.testmgmt.testSuite import TestSuite",
                                "TestSuite.current_test_case_name")
        sharedValuesHandler.get_shared_value_handler().add_shared_value(\
                      "from NSTpyfw.testmgmt.testSuite import TestSuite",
                                "TestSuite.current_test_case_filename")
        # Updating shared values
        sharedValuesHandler.get_shared_value_handler().update_shared_values()

        # We add to the self.result (type:TestSuiteResult) the results of each
        # of the test cases included in the run_test_cases_list.
        is_first_test_case = True
        self.my_ppu_entity.destroy(True)
        for test_case in self.run_test_cases_list:
            logging.getLogger("NSTlogger").testinfo("")
            logging.getLogger("NSTlogger").testinfo("###########################################")
            logging.getLogger("NSTlogger").testinfo("###########################################")
            logging.getLogger("NSTlogger").testinfo("TEST CASE BEGIN ")
            logging.getLogger("NSTlogger").testinfo("###########################################")
            logging.getLogger("NSTlogger").testinfo("")

            queue = Queue()

            self.result.startTestCase()

            test_case_name = test_case.split("/").pop()
            TestSuite.current_test_case_filename  = test_case_name
            sharedValuesHandler.get_shared_value_handler().update_shared_values()

            #Creates the current test case class dynamically.
            try:
                current_test_case = self.generate_dynamic_entity(test_case)
                if self.mtt_baseline_path:
                    # Run the TC in MTT regression mode
                    current_test_case = MttRegressionTestCase(current_test_case,
                                                              self.mtt_baseline_path)
            except InvalidTestCaseYamlFileException, e:
                logging.getLogger("NSTlogger").error("Wrong test case yaml file found [%s]: %s" \
                                                     % (test_case, str(e)))
                self.test_case_result = \
                     TestCaseResult(\
                          classname = "",
                          test_case_name = test_case,
                          test_case_file_name = test_case,
                          result = TestCaseResultCode.UNDEFINED_TESTCASE_ERROR,
                          stdout = None, stderr = str(e).splitlines())

                # aggregate the result of the execution
                self.result.addResult(self.test_case_result)
                continue

            if is_first_test_case == True:
                current_test_case.already_restarted = self.force_restart_of_entity
            #Creates a TC directory
            tc_log_directory = self.__create_tc_directory(self.log_directory, \
                                                          current_test_case.name)
            Logger(file_log = os.path.join(tc_log_directory, current_test_case.name+".log"), \
                   level = self.logger_level, warning_loggers = self.warning_loggers)

            #If the flag is enable, the TC yaml file will be stored into the tc log directory
            if self.save_test_yaml_files:
                self.__save_file(test_case, tc_log_directory)

            #sets generic values to test case
            current_test_case.set_ppu_entity(self.my_ppu_entity)
            current_test_case.set_log_directory(tc_log_directory)

            tc_proc = Process(target=self.start_process_wrapper,
                              args=(current_test_case,queue))

            # xiakfer, Eclipse/PyDev multiprocess debugging:
            # A new process is forked here. Eclipse/PyDev cannot follow the
            # fork into the subprocess, but can be attached manually to the
            # subprocess.
            # On the other hand, GDB is capable of following the forked
            # process, Python included.
            # Workaround for eclipse/pydved: remote debugging option of
            # manually inserting calls to pydevd.settrace(). Subsequent PyDev
            # breakpoints are obeyed.
            # We explicit settrace call to establish the remote debugging
            # session for the process, and afterwards just use the normal
            # debugger breakpoints.
            # Insert the pydevd.settrace code somewhere early in the
            #
            # NOTE that pydevd.settrace is run in tc_proc.start
            # (start_process_wrapper), where the suprocess is initialized.
            #
            tc_proc.start()

            if current_test_case.max_testcase_duration:
                max_current_testcase_duration = current_test_case.max_testcase_duration
            else:
                max_current_testcase_duration = self.max_testcase_duration

            TestCaseTimeout().set_value(max_current_testcase_duration)
            TestCaseTimeout().test_started()

            tc_proc.join (max_current_testcase_duration)
            logging.getLogger("NSTlogger").debug\
                             ("either the test case is over or it took more "\
                              "than %d seconds", self.max_testcase_duration)
            #Setting a new time out to do tasks until the next test is run
            TestCaseTimeout().set_value(max_current_testcase_duration)
            TestCaseTimeout().test_started()
            #Updating the shared values in the test suite process
            sharedValuesHandler.get_shared_value_handler().update_process()

            if tc_proc.is_alive():
                logging.getLogger("NSTlogger").error ("\
                     the test case is still alive after the allowed time")

                logging.getLogger("NSTlogger").error ("\
                     killing process for test case %s"%test_case_name)

                try:
                    self.__kill_test_case_process(tc_proc.pid)
                except LocalShellConnectionException:
                    logging.getLogger("NSTlogger").error ("Test cases process could not be killed. Saving logs and forcing exit")
                    self.my_ppu_entity.save_log_files(self.log_directory)
                    pgid = os.getpgid(tc_proc.pid)
                    os.killpg(pgid, 9)

                current_test_case.exception_condition()

                error_message = "killing process: running more than %d seconds"\
                                 % max_current_testcase_duration
                self.test_case_result = \
                     TestCaseResult(\
                          classname = TestSuite.current_test_case_class_name,
                          test_case_name = TestSuite.current_test_case_name,
                          test_case_file_name = TestSuite.current_test_case_filename,
                          result = TestCaseResultCode.TIMED_OUT_TESTCASE_ERROR,
                          stdout = None, stderr = [error_message])
            else:
                logging.getLogger("NSTlogger").debug ("getting verdict from the testcase")
                #Try to get the TestCaseResult from the queue with timeout 10 seconds
                try:
                    self.test_case_result = queue.get_nowait()
                except Empty:
                    error_message = "No TestCaseResult was found"
                    self.test_case_result = \
                         TestCaseResult(\
                              classname = TestSuite.current_test_case_class_name,
                              test_case_name = TestSuite.current_test_case_name,
                              test_case_file_name = TestSuite.current_test_case_filename,
                              result = TestCaseResultCode.TIMED_OUT_TESTCASE_ERROR,
                              stdout = None, stderr = [error_message])

            # aggregate the result of the execution
            self.result.addResult(self.test_case_result)
            is_first_test_case = False

            logging.getLogger("NSTlogger").testinfo("")
            logging.getLogger("NSTlogger").testinfo("###########################################")
            logging.getLogger("NSTlogger").testinfo("TEST CASE END")
            logging.getLogger("NSTlogger").testinfo("###########################################")
            logging.getLogger("NSTlogger").testinfo("###########################################")
            logging.getLogger("NSTlogger").testinfo("")
        # Now we add to the self.result (type:TestSuiteResult) the skipped test cases.
        for test_case in self.skipped_test_cases_list:
            self.result.startTestCase()

            myNodeInfo    = yaml.load(file(test_case))#载入测试范例集
            if ( "type" in myNodeInfo and "class" in myNodeInfo["type"]):
                TestSuite.current_test_case_class_name = myNodeInfo["type"]["class"]
                TestSuite.current_test_case_name = myNodeInfo["name"]
            else:
                logging.getLogger("NSTlogger").warning("%s Yaml file seems to "\
                        "be incorrect. This error is IGNORED by the FW, but "\
                        "you should check what the heck is happening with your"\
                        " config file." %(test_case))
                # instead of obtaining the name of the class for this tc, we
                # just put the TC definition file, so you can trace the problem.
                TestSuite.current_test_case_class_name = test_case.split("/").pop()
                TestSuite.current_test_case_name = test_case.split("/").pop()

            message = "skipping %s test case (%s)" % (test_case, TestSuite.current_test_case_class_name)
            self.test_case_result = \
                 TestCaseResult(classname = TestSuite.current_test_case_class_name,
                                test_case_name = TestSuite.current_test_case_name,
                                test_case_file_name = TestSuite.current_test_case_filename,
                                result = TestCaseResultCode.TESTCASE_SKIPPED,
                                stdout = [message], stderr = None)

            # friendly and informative message ... logging purposes.
            logging.getLogger("NSTlogger").\
                    testinfo("TestCase: %s - Result: SKIPPED" %(test_case))

    ## END METHOD main_start()


    def main_pre_condition(self):
        '''
        Installs a new distribution, load a new configuration and restart the
        SASN.  If there is a defined distribution file, this will be installed.
        After that, it loads a new configuration for the SASN server. When the
        config is loaded, the SASN server can be restarted in order to apply
        the configuration and to delete statistics, alarms... of the other
        executions.

        If necessary, it can add specific logic to this method overwriting the
        L{pre_condition} method. The L{pre_condition} method is invoked at the
        end of the main method.
        '''

        # TestCaseTimeout().set_value(self.max_testcase_duration)
        # TestCaseTimeout().test_started()
        #
        # self.result.startTestSuite()
        #
        Logger(file_log = os.path.join(self.log_directory, "pre-condition.log"), \
               level = self.logger_level, warning_loggers = self.warning_loggers)

        logging.getLogger("NSTlogger").testinfo("")
        logging.getLogger("NSTlogger").testinfo("")
        logging.getLogger("NSTlogger").testinfo("")
        logging.getLogger("NSTlogger").testinfo("TEST SUITE PRE-CONDITION")
        logging.getLogger("NSTlogger").testinfo("###########################################")
        logging.getLogger("NSTlogger").testinfo("###########################################")
        logging.getLogger("NSTlogger").testinfo("")

        # To avoid errors in vSASN when there is no config loaded:
        if ExecutionMode().get_is_vsasn():
            if not self.my_ppu_entity.get_active_control_entity().is_sasn_function_present():
                logging.getLogger("NSTlogger").debug("loading SIMPLE_COM_CONFIGURATION in main_pre_condition")

                configurator = self.my_ppu_entity.get_active_control_entity().get_configurator()
                old_config_method = configurator.get_configuration_method()
                configurator.set_configuration_method("com")
                self.my_ppu_entity.set_configuration(self.SIMPLE_COM_CONFIGURATION,
                                                     yml_file = self.dut_yml_file,
                                                     only_ipv4_config = self.dut_only_ipv4_config,
                                                     log_directory = self.log_directory,
                                                     force = True,
                                                     config_method = "com")
                #This apply is only for waiting until commit finish.
                self.my_ppu_entity.apply()
                configurator.set_configuration_method(old_config_method)

            else:
                logging.getLogger("NSTlogger").debug("not loading SIMPLE_COM_CONFIGURATION, SasnFunction is present")

            self.ppu_entity_config["installation_mode"] = False
            self.my_ppu_entity = self.generate_dynamic_entity(self.ppu_entity_config)

        #Removes temporary config values stored for recreate my_ppu_entity in case of VSASN environment is found
        del(self.ppu_entity_config)


        TestCaseTimeout().set_value(self.max_testcase_duration)
        TestCaseTimeout().test_started()

        # aggregate the ppu entity to the testSuiteResult artifact, so it can
        # extract interesting data on reports.
        self.result.setTargetSUTInfo( self.my_ppu_entity )

        self.result.startTestSuite()

        if self.save_test_yaml_files:
            self.__save_file(self.config_yaml_file, self.log_directory)

        self.initial_df_info = DiskFreeInfo()
        volume_info = self.initial_df_info.get_mounted_volume(self.log_directory)

        logging.getLogger("NSTlogger").info(self.initial_df_info)

        if int(volume_info["Use%"].replace("%", ""))> 90:


        process = subprocess.Popen("rpm -qa |grep NST", shell=True,
                                 stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE, close_fds=True)

        return_code = process.wait()
        std_output = process.stdout.read()

        assert return_code == 0, "Some problems found searching the installed NST modules."
        logging.getLogger("NSTlogger").info("Installed NST modules:\n%s", std_output)

        #installs the defined distribution file in PPU Entity
        if (self.distribution_file!= None):
            logging.getLogger("NSTlogger").testinfo( \
                "TestSuite - Installing a new distribution ...")
            self.my_ppu_entity.install_distribution(\
                self.distribution_file)
        else:
            logging.getLogger("NSTlogger").warning( \
                "TestSuite - WARNING!! Local distribution file has not been defined.\n" \
                "This test suite will try to use the current distribution" \
                "running on host.")

        #checks if sasn is installed
        if not(self.my_ppu_entity.get_is_installed_sasn()):
            logging.getLogger("NSTlogger").error("TestSuite - There is not" \
                  " a SASN distribution installed on" \
                  " the current host. End of execution")
            exit(-1)

        #checks if heuristic is installed
        if not(self.my_ppu_entity.get_is_installed_heuristics()):
            logging.getLogger("NSTlogger").warning(\
                "TestSuite - There is not a heuristic distribution installed")

        #Checks the ditributions in the cluster or PPU
        if self.check_distribution_info and (self.my_ppu_entity.check_distribution()):
            logging.getLogger("NSTlogger").testinfo( \
                "TestSuite - Every PPU in the cluster have the same distribution")

        self.check_rollback()

        TestInitializer().test_suite_init_check(self.my_ppu_entity)

        ## The next step is try to load the Base IPOS configuration
        ##
        if ExecutionMode().get_is_ssr(self.execution_mode):
            self.my_ppu_entity.wait_commit_finish()
            simple_configuration = self.ROUTER_SSR_CONFIGURATION
            if self.do_not_load_ipos:
                logging.getLogger("NSTlogger").\
                    warning('do_not_load_ipos Flag is activated in the test' \
                            ' case configuration this can make the current' \
                            ' test case to fail, be sure that this is what' \
                            ' you want!!!!')
            else:
               ## Save current execution mode
                saved_execution_mode = self.my_ppu_entity.execution_mode
                self.my_ppu_entity.execution_mode = "ipos"
                ## Try to change the configuration
                result = self.my_ppu_entity.set_configuration( \
                                simple_configuration, \
                                yml_file = self.dut_yml_file, \
                                only_ipv4_config = self.dut_only_ipv4_config, \
                                log_directory = self.log_directory)
                ## Check if change was successfull
                if result: ## Configured successfully
                    logging.getLogger("NSTlogger").\
                            debug('SSR Router Configuration loaded with success')
                    ## Wait to see if SASN was changed
                    self.my_ppu_entity.wait_commit_finish()
                else: ## Something went wrong
                    (return_code, _, stderr) = self.my_ppu_entity\
                                                   .get_last_load_result()
                    if NO_LOAD_NEEDED == return_code:
                        ## Configuration not loaded because did not change
                            warning('SSR Router configuration error: [%s]' \
                                    % stderr)
                    ## End If
                ## End If
                ConfigurationInformation().one_config_loaded()
                self.my_ppu_entity.execution_mode = saved_execution_mode
            ## End If

                 #TODO: Workaround - Maybe this part of code can be compatible with the SSR one in the future.
        elif ExecutionMode().get_is_vsasn():
            #Before trying to load or restart the ppu, we should wait until any commit in progress finish.
            self.my_ppu_entity.wait_commit_finish()
        ## End If
        is_system_active = False
        try:
            is_system_active = self.my_ppu_entity.is_system_active()
        except UnableToRetrieveMetric, exp:
            logging.getLogger("NSTlogger").testinfo("Exception checking system active: %s)" % str(exp))
            is_system_active = False

        if (self.dut_config_templates):
            logging.getLogger("NSTlogger").debug( \
                "TestSuite - Loading dut config")
            logging.getLogger("NSTlogger").testinfo( \
                "TestSuite - Setting the configuration to the PPU Entity...")

            if (self.my_ppu_entity.set_configuration(self.dut_config_templates, yml_file = self.dut_yml_file, \
                                                     only_ipv4_config = self.dut_only_ipv4_config, log_directory = self.log_directory, force = not is_system_active)):
                (_, stdout, stderr) = NSTpyfw.sshConnectionResultMgr.\
                                          get_last_ssh_connection_result()
                stdout.extend(stderr)
                logging.getLogger("NSTlogger").\
                            testinfo("TestSuite - Initial configuration result :\n%s"\
                            %("\n".join(stdout)))

                ## TODO: This if. Workaround used only while COM is not supported for vSASN
                if (not self.use_mt) and ExecutionMode().get_is_vsasn(ExecutionMode().get_current_execution_mode()):
                    try:
                        self.my_ppu_entity.apply()
                        is_system_active = True
                        logging.getLogger("NSTlogger").testinfo("TestSuite - (VSASN) Initial configuration applied -> Result :\n%s"\
                                                                %("\n".join(stdout)))

                    except KeyboardInterrupt:
                        raise
                    except:
                        is_system_active = False
            else:
                logging.getLogger("NSTlogger").\
                            testinfo("TestSuite - The config is already loaded in the server.")
        else:
            logging.getLogger("NSTlogger").debug( \
                "TestSuite - NOT Loading dut config")

            if (not is_system_active) or (self.force_restart_of_entity):
                logging.getLogger("NSTlogger").debug( \
                    "TestSuite - Loading simple config. forced or not active")
                ts_execution_mode = self.my_ppu_entity.execution_mode
                logging.getLogger("NSTlogger").debug("self.my_ppu_entity.execution_mode: %s",
                                                      self.my_ppu_entity.execution_mode)
                logging.getLogger("NSTlogger").debug("main_pre_condition: is_system_active:%s, force_restart_of_entity: %s",
                                                      is_system_active, self.force_restart_of_entity)
                self.my_ppu_entity.execution_mode = "hl"
                ## Set migration tool usage ##
                config_man = ConfigManager()
                mt_config = {"use_mt": True}
                config_man.loadConfig("migration_tool", mt_config, True)

                simple_configuration = self.SIMPLE_HL_CONFIGURATION
                try:
                    self.my_ppu_entity.set_configuration(simple_configuration, yml_file = self.dut_yml_file, \
                                                     only_ipv4_config = self.dut_only_ipv4_config, log_directory = self.log_directory, force = not is_system_active)

                finally:
                    self.my_ppu_entity.wait_commit_finish()
                    mt_config = {"use_mt": self.use_mt}
                    config_man.loadConfig("migration_tool", mt_config, True)
                    self.my_ppu_entity.execution_mode = ts_execution_mode

        if (not is_system_active) or (self.force_restart_of_entity):
            logging.getLogger("NSTlogger").testinfo( \
                "TestSuite - Restarting the PPU Entity...")
            #restarts the PPU Entity
            self.my_ppu_entity.restart(abrupt = True)
            (_, stdout, stderr) = NSTpyfw.sshConnectionResultMgr.\
                                          get_last_ssh_connection_result()
            stdout.extend(stderr)
            logging.getLogger("NSTlogger").testinfo( \
                "TestSuite - Restart result : \n%s" %("\n".join(stdout)))

             elif self.dut_config_templates:
            logging.getLogger("NSTlogger").testinfo( \
                "TestSuite - Applying Test Suite configuration...")
            try:
                self.my_ppu_entity.apply()
            except AliWithIPZeroException:
                logging.getLogger("NSTlogger").error("SSR error platform detected")
                self.my_ppu_entity.perform_workaround("ali zero")

        else:
            logging.getLogger("NSTlogger").testinfo("TestSuite - No apply or restart of the PPU Entity required")
        self.my_ppu_entity.update_architecture()


        if self.my_ppu_entity.is_ipv6_enable():
            logging.getLogger("NSTlogger").info ("ipv6 IS enabled")
            #checks the network status before running the first test case
            network_status = self.my_ppu_entity.check_network_status()
            logging.getLogger("NSTlogger").\
                    testinfo("Network status (OK = 0): %s" %network_status)

            if network_status == PPUEntity.NETWORK_STATUS_CODE["TENTATIVE"]:
                raise NetworkTestError("Fatal network error found. The network status is 'TENTATIVE'.")
        else:
            logging.getLogger("NSTlogger").info ("ipv6 IS NOT enabled")

        if not (self.tc_cluster_only == None) and hasattr(self.my_ppu_entity, "execution_mode") and self.my_ppu_entity.execution_mode == "cluster":
            logging.getLogger("NSTlogger").testinfo("The following test cases will be added for cluster execution-mode: %s" % self.tc_cluster_only)
            self.test_cases_pattern_list = self.tc_cluster_only + self.test_cases_pattern_list

        if (len(self.test_cases_pattern_list) > 0):
            #Looking for and set the test cases to run or skip
            self._load_test_cases(self.test_cases_pattern_list, self.skip_test_cases_pattern_list)

        #Specific logic is run by every test case created.
        self.pre_condition()
## END METHOD pre_condition()


 def main_post_condition(self):
        '''
        This method logs the test suite results.
        '''

        TestCaseTimeout().set_value(self.max_testcase_duration)
        TestCaseTimeout().test_started()

        self.result.endTestSuite()

        Logger(file_log = os.path.join(self.log_directory, "post-condition.log"), \
               level = self.logger_level, warning_loggers = self.warning_loggers)

        # print all reports using the TestResultReporter artifact.
        self.result.setTargetSUTInfo( self.my_ppu_entity )
        reporter = TestResultReporter(self.config_yaml_file, self.result,
                                                      self.log_directory)
        try:
            reporter.genReports()
        except Exception as exception:
            logging.getLogger("NSTlogger").error("Error while generating report: %s"%exception.args)


        final_df_info = DiskFreeInfo()
        initial_volume_info = self.initial_df_info.get_mounted_volume(self.log_directory)
        final_volume_info = final_df_info.get_mounted_volume(self.log_directory)

        logging.getLogger("NSTlogger").info(final_df_info)
        available_ts_dif = int(initial_volume_info["Available"]) - int(final_volume_info["Available"])
        use_ts_dif = int(initial_volume_info["Use%"].replace("%", "")) - int(final_volume_info["Use%"].replace("%", ""))
        logging.getLogger("NSTlogger").testinfo("Free disk space available (Kb): before TS [%s]; After TS [%s]; Difference [%s]" \
                                                % (initial_volume_info["Available"], final_volume_info["Available"], available_ts_dif))
        logging.getLogger("NSTlogger").testinfo("Free disk use ( %% ): before TS [ %s ]; After TS [ %s ]; Difference [ %s ]" \
                                                % (initial_volume_info["Use%"], final_volume_info["Use%"], use_ts_dif))


        if int(final_volume_info["Use%"].replace("%", ""))> 90:
            logging.getLogger("NSTlogger").warning("Disk information: Free space available less than 10%% after TS execution; Use%% [%s]" %(final_volume_info["Use%"]))


        #Specific logic is run by every test case created.
        self.post_condition()

        self.my_ppu_entity.destroy()
        del self.my_ppu_entity
        SSHTunnelier().stop_all_tunnels()


    ## END METHOD post_condition()



    def generate_dynamic_entity(self, entity_config):
        '''
        This method creates a new entity dynamically. To do that,
        a specific configuration is needed. This configuration can be
        provided either as a YAML file or as a python dictionary.
        This configuration MUST contain
        the "type" field. The entity may be any object type that extends
        from YamlConfigurable class, e.g. PPUEntity, AnalyzerTestCase, etc...
        Example::
            ##############################################################
            # Data to be used by "nspytest"                              #
            ##############################################################
            nspytest:
                test_suite_path: "/opt/nstest/lib/NSTanalyzer/"
                test_suite_module: AnalyzerTestSuite
                test_suite_class: AnalyzerTestSuite

        Where:
            - nspytest: It is a tag to be read by the script "nspytest".
            - test_suite_path: The primary path where the logic of the test
                               suite is found.
            - test_suite_module: The module of the test suite is found.
                                 Usually, it is the name file without .py where
                                 the class is.
            - test_suite_class: The class of the test suite is found.

        @param entity_config: A file path or a specific configuration.
        @type entity_config: str or dict
        @return: The entity generated dynamically
        @rtype: object
        '''

        assert type(entity_config) in (str, dict)
        if type(entity_config) == str:
            try:
                node_info = yaml.load(file(entity_config))
            except Exception, e:
                raise InvalidTestCaseYamlFileException(str(e))
        else:
            node_info = entity_config

        #checks if the "type" field exists
        assert("type" in node_info)

        entity_type =  node_info["type"]
        #checks if the arguments needed are into "type" field
        assert(("module" in entity_type) and ("class" in entity_type))

        #checks that the module and class exits
        new_module = None
        try:
            #checks if the module is already loaded
            new_module  = sys.modules[entity_type["module"]]
        except KeyError:
            pass

        if not(new_module):
            #When the module is not loaded, is looked for.
            fp, pathname, description = imp.find_module(entity_type["module"])

            try:
                #if the module was found, it tries to load. If the module was not found
                #the next line must throw a Exception
                new_module = imp.load_module(entity_type["module"], fp, pathname, description)
            finally:
                # Since we may exit via an exception, close fp explicitly.
                if fp:
                    fp.close()

        #Checks if the module was found and loaded
        assert(new_module), "The module [%s] was not found" % entity_type["module"]

        #checks the class is in the module
        class_name = getattr(new_module, entity_type["class"])
        assert(class_name), "The class [%s] was not found" % entity_type["class"]

        #creates the new class
        tmp_entity = class_name()

        #checks the new entity is correct.
        #The new entity must be YamlConfigurable object or extends from this
        aux = getattr(tmp_entity, 'set_node')
        assert(aux)
        tmp_entity.set_node(node_info)
        tmp_entity.load_yaml_config()

        logging.getLogger("NSTlogger").debug("exit generate_dynamic_entity")
        return tmp_entity

    ## END METHOD generate_dynamic_entity()

    def start(self, test_case):
        """
        This method is executed by L{main_start} method and must be overridden by
        children of this class.  It must be used to set the specific values in
        the Test Case.

        @param test_case: A L{TestCase} object to be used to set specific
                          values from the test suite.
        @type test_case: L{TestCase}
        """
        logging.getLogger("NSTlogger").testinfo("")
        logging.getLogger("NSTlogger").testinfo("TEST SUITE START")
        logging.getLogger("NSTlogger").testinfo("###########################################")
        pass

    def pre_condition(self):
        """
        This method is executed at the end of L{main_pre_condition} method and must be overridden by
        children of this class.  It must be used to executed specific logic of
        Test Suite in pre-condition state.
        """
        logging.getLogger("NSTlogger").testinfo("")
        logging.getLogger("NSTlogger").testinfo("TEST SUITE SPECIFIC PRE-CONDITION")
        logging.getLogger("NSTlogger").testinfo("###########################################")
        pass

    def post_condition(self):
        """
        This method is executed at the end of L{main_post_condition} method and must be overridden by
        children of this class.  It must be used to executed specific logic of
        Test Suite in post-condition state.
        """
        logging.getLogger("NSTlogger").testinfo("")
        logging.getLogger("NSTlogger").testinfo("TEST SUITE SPECIFIC POST-CONDITION")
        logging.getLogger("NSTlogger").testinfo("###########################################")
        pass


    def _load_test_cases(self, test_cases_pattern_list, skip_test_cases_pattern_list):
        """
        Search and set the test cases to run or skip.

        This method is called before running the L{pre_condition} of specific test suite when
        the following attributes have been defined in the test suite yaml::
            ...
            ##############################################################
            # TEST CASE REGRESSION CONFIGURATION                         #
            ##############################################################
            # List with path and patterns to look for a new test cases to run
            test_cases_pattern_list :
                - "/opt/nstest/test/NSTanalyzer/caregression/caregression-*"
                - "/opt/nstest/test/NSTanalyzer/cr6009/cr6009-*"
                - "/opt/nstest/test/NSTanalyzer/cr6030/cr6030-*"
                - "/opt/nstest/test/NSTanalyzer/cr6248/TC-OpMini-*"

            # List with path and patterns to look for a test cases to skip
            skip_test_cases_pattern_list:
                - "/opt/nstest/test/NSTanalyzer/caregression/caregression-dns*"

        However, this method can be used inside L{pre_condition} of a test suite
        when you need to generate a list of test cases dynamically. To avoid to
        invoke the method twice, it must take into account to remove
        the example above from your test suite yaml.

        @param test_cases_pattern_list: List of the test-case pattern paths to run
        @param skip_test_cases_pattern_list: List of the test-case pattern paths to skip
        """
        logging.getLogger("NSTlogger").\
                testinfo("TestSuite - Looking for test cases to run...")
        #Looking for the test cases to run
        test_cases_found = []
        for pattern in test_cases_pattern_list:
            logging.getLogger("NSTlogger").\
                    debug("TestSuite - Looking for test cases to run " \
            "in %s ..." % (pattern))
            aux = glob.glob(pattern)
            aux.sort()
            test_cases_found += aux


        logging.getLogger("NSTlogger").\
                debug("TestSuite - Test cases found [%s]" % (test_cases_found))


        #Looking for the test cases to skip
        skip_test_cases_found = []
        if skip_test_cases_pattern_list is not None:
            for pattern in skip_test_cases_pattern_list:
                logging.getLogger("NSTlogger").\
                        debug("TestSuite - Looking for test cases to skip in %s ..." % (pattern))
                skip_test_cases_found += glob.glob(pattern)

        #Sets the final list with the test cases found less test cases skipped
        temp_tc_list = []
        for test_case in test_cases_found:
            if test_case in skip_test_cases_found:
                self.skipped_test_cases_list.append(test_case)
            else:
                temp_tc_list.append(test_case)

        # Sort and filter test cases by priorities
        self.__loadPriorityCriteria()
        temp_tc_list.sort(self.__priorityCriteria, None, 1)
        self.run_test_cases_list, self.skipped_test_cases_list = \
                                    self.__filterByPrioThreshold(\
                                           temp_tc_list,
                                           self.skipped_test_cases_list)

        # print :-)
        logging.getLogger("NSTlogger").\
                testinfo("TestSuite - List of test cases to run %s ..."\
                        %(self.run_test_cases_list))

    def __save_file(self, file_path, log_directory):
        """
        Saves a file into the log_directory.
        """
        logging.getLogger("NSTlogger").info("TestSuite - Saving file [%s] into [%s] ..." % (file_path, log_directory))
        shell_con = LocalShellConnection()
        try:
            shell_con.put_file(file_path, log_directory)
            logging.getLogger("NSTlogger").info("TestSuite - File [%s] is saved in [%s]" % (file_path, log_directory))
        except Exception, exc:
            logging.getLogger("NSTlogger").info("TestSuite - Impossible to save file [%s] in [%s]: %s" % (file_path, log_directory, exc))

    def __create_ts_directory(self, log_directory):
        """
        Create a new directory to be used by the test suite.

        @param log_directory: The absolute path where the test suite directory
                              will be created.
        @type  log_directory: str
        """

        current_time = time.strftime("%Y-%m-%d-%H%M%S", time.localtime())
        if not log_directory:
            log_directory = "/tmp"

        ts_directory = os.path.join(log_directory, self.name+"-"+current_time)
        if not os.path.exists(ts_directory):
            try:
                os.makedirs(ts_directory)
            except:
                logging.getLogger("NSTlogger").\
                        warning("Directory could not be created: %s"\
                               %(ts_directory))
                return None

        return ts_directory

    def __create_tc_directory(self, log_directory, tc_name):
        """
        Create a new directory to be used by the test case.

        @param log_directory: The absolute path where the test case directory
                              will be created.
        @type  log_directory: str
        @param tc_name: The test case name to be used as directory name.
        @type  tc_name: str
        """

        if not log_directory:
            log_directory = "/tmp"

        ts_directory = log_directory+"/"+tc_name+"/"

        if not os.path.exists(ts_directory):
            try:
                os.makedirs(ts_directory)
            except:
                logging.getLogger("NSTlogger").\
                        warning("Directory could not be created: %s" %(ts_directory))
                return None

        return ts_directory

    def __loadPriorityCriteria(self):
        """
        This method reads the test_cases_priority_rules if exists, and
        initialize the priority_rulez list attribute.  If it doesn't exist, for
        compatibility issues, the DEFAULT_RULE, with priority 0, will be created.
        The generated list will be used for ordering, regarding the defined
        priority, the test cases. Of course, priorities will be used not only
        to define somekind of order between test cases, but for provide a
        mechanism to execute test cases by using a priority threshold.

        The test_cases_priority_rules elements must have the following format::

            test_cases_priority_rules :
                 - <pattern> : <priority>

        Where, pattern is a RegExp, that will be compiled and used afterwards
        to match the files on the run_test_cases_list.  priority is a integer.

        Is it possible also to redefine the integer value for the DEFAULT_RULE
        in the following way::

            test_cases_priority_rules :
                 - DEFAULT_RULE : -100

        Example::

            ##############################################################
            # TEST CASE REGRESSION CONFIGURATION                         #
            ##############################################################
            # List with path and patterns to look for a new test cases to run
            test_cases_pattern_list :
                - "/opt/nstest/test/NSTanalyzer/caregression/caregression-*"
                - "/opt/nstest/test/NSTanalyzer/cr6009/cr6009-*"
                - "/opt/nstest/test/NSTanalyzer/cr6030/cr6030-*"
                - "/opt/nstest/test/NSTanalyzer/cr6248/TC-OpMini-*"

            # List with path and patterns to look for a test cases to skip
            skip_test_cases_pattern_list:
                - "/opt/nstest/test/NSTanalyzer/caregression/caregression-dns*"

            test_cases_priority_rules:
                - caregression-ftp: 200
                - caregression-dns: 10
                - caregression-http-pipelining: 12
                - caregression-http: 11
                - caregression-http-test: 123
                - DEFAULT_RULE: 0

            priority_threshold: 0

        NOTE that the defined order is very important. In the previous example,
        for instance, the defined rule caregression-http-test will not have any
        effect cause the previous one will match will all the
        /caregression-http*/ test cases in the list.
        """
        default_rule = re.compile(".*")
        default_prio = 0
        if (len(self.test_cases_pattern_list) > 0):
            for entry in (self.test_cases_priority_rules):
                if ("DEFAULT_RULE" in entry):
                    default_prio = entry["DEFAULT_RULE"]
                else:
                    pattern = entry.keys()[0]
                    try:
                        rule = re.compile(pattern)
                        prio = entry[pattern]
                        self.priority_rulez.append({"rule": rule, "prio": prio})
                    except:
                        logging.getLogger("NSTlogger").\
                                warning("Got a problem compiling the following "\
                                        "pattern: '%s'. Ignoring this priority "\
                                        "rule." % pattern)

        self.priority_rulez.append({"rule": default_rule, "prio": default_prio})

    def __priorityCriteria(self, a, b):
        """
        sorting comparison function.
        """
        prio_a = self.__retrievePrioFor(a)
        prio_b = self.__retrievePrioFor(b)

        if (prio_a > prio_b):
            return 1
        elif (prio_a < prio_b):
            return -1
        else:
            return 0

    def __retrievePrioFor(self, tc):
        """
        We can reduce the cost of this function by using a cache of assigned
        priorities.
        """
        if tc in self.prio_cache:
            return self.prio_cache[tc]

        for rule in self.priority_rulez:
            if rule["rule"].findall(tc):
                self.prio_cache[tc] = rule["prio"]
                return rule["prio"]

        # NOTE we SHOULDN'T reach this point. The DEFAULT_RULE should be reached
        #      if any of the defined rules matched
        return -1

      def __filterByPrioThreshold(self, tc_prioritized_list, tc_skipped_list):
        """
        Assuming the tc_prioritized_list is already ordered by priority
        """
        index = 0
        for tc in tc_prioritized_list:
            if (self.__retrievePrioFor(tc) < self.priority_threshold):
                tc_skipped_list.extend(tc_prioritized_list[index:])
                return tc_prioritized_list[:index], tc_skipped_list
            index += 1

        return tc_prioritized_list, tc_skipped_list


    def __kill_test_case_process(self, test_case_pid):
        """
        Kills the TestCase process and its children (if exist)
        """
        pgid = os.getpgid(test_case_pid)
        local_shell = LocalShellConnection()

        cmd = "ps axjf |grep %s" % pgid
        (_, std_output, _) = local_shell.send_command(cmd, timeout = 30)
        logging.getLogger("NSTlogger").testinfo("Killing test case process output:\n%s" %std_output)
        parent_pid_list_2_kill = []

        for line in std_output:
            line = line.rstrip()
            tokens = line.split()
            current_parent_pid = int(tokens[0])
            current_pid =  int(tokens[1])
            if (current_pid == test_case_pid) or (current_parent_pid in parent_pid_list_2_kill):
                parent_pid_list_2_kill.append(current_pid)
                cmd = "sudo kill %s" % current_pid
                (status, _, _) = local_shell.send_command(cmd, timeout = 30)
                if status == 0:
                    logging.getLogger("NSTlogger").testinfo("Killed process with pid (%s)" %(current_pid))
                else:
                     logging.getLogger("NSTlogger").error("The process with pid (%s) was not killed" %(current_pid))


    def check_rollback(self):
        """
        Function used to check if there is any Rollback to do
        """
        rollback = Rollbacker()
        to_rollback = rollback.next_command()
        while to_rollback is not None:
            try:
                result = rollback.execute_command(to_rollback, ppu_entity=self.my_ppu_entity)
                if not result:
                    logging.getLogger("NSTpyfw").warning("Unable to rollback the command: %s" % to_rollback)
                ## End If
                logging.getLogger("NSTpyfw").info("Rollback with success the command: %s" % to_rollback)
            except Exception, exp:
                logging.getLogger("NSTpyfw").warning("Unable to rollback the command: %s" % to_rollback)
                logging.getLogger("NSTpyfw").exception(exp)
            ## End Try
            to_rollback = rollback.next_command()
        ## End While
    ## END METHOD check_rollback()
##################################
## END CLASS TestSuite
##################################