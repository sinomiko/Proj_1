#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pexpect
class installSASN(object):
    """
    class to install SDK on SASN maintenance pool
    """
    def installSASNCMD(self):

        p = pexpect.spawn('ssh netspira@%s' % self.__host_name)
        try:
            i = p.expect(['(?i)password:', '(?i)continue connecting (yes/no)?'], timeout=10)
            if i == 0 :
                p.sendline("lucas21")
            elif i == 1:
                p.sendline('yes\n')
                p.expect('(?i)password:')
                p.sendline("lucas21")

            p.sendline("scp root@netrax3-2-10:/software/changeSDK.sh /root/")
            i = p.expect(['(?i)password:', '(?i)continue connecting (yes/no)?'], timeout=3)
            if i == 0 :
                p.sendline("lucas21")
            elif i == 1:
                p.sendline('yes\n')
                p.expect('(?i)password:')
                p.sendline("lucas21")

            p.sendline("cd /tmp/NightswatchLastSASN/ \n")

            p.sendline("rm -rf cxp9000000* \n")

            p.sendline("wget https://nexus.netspira.eld.es.eu.ericsson.se/nexus/service/local/repositories/\
            development_proxy/content/com/ericsson/sasn/cxp9000000_14a15br1a38_00_maintenance_14a15b_branch_69\
            /sasn-cxp9000000_14a15br1a38_00_maintenance_14a15b_branch_69.tar.gz  --no-check-certificate\n")

            ret = 0
        except pexpect.EOF:
            print "host:%s return EOF, download SASN build failed" % self.__host_name
            p.close()
            ret = -1
        except pexpect.TIMEOUT:
            print "host:%s return TIMEOUT, download SASN build failed" % self.__host_name
            p.close()
            ret = -2
        return ret

    def QueryInstallSASNStatus(self):
        p = pexpect.spawn('ssh netspira@%s' % self.__host_name)
        try:
            i = p.expect(['(?i)password:', '(?i)continue connecting (yes/no)?'], timeout=10)
            if i == 0 :
                p.sendline("lucas21")
            elif i == 1:
                p.sendline('yes\n')
                p.expect('(?i)password:')
                p.sendline("lucas21")

            p.sendline("cd ~")
            p.sendline("tail 15 nohup.out\n")
            p.close()

            ret = 0
        except pexpect.EOF:
            print "host:%s return EOF, failed" % self.__host_name
            p.close()
            ret = -1
        except pexpect.TIMEOUT:
            print "host:%s return TIMEOUT, failed" % self.__host_name
            p.close()
            ret = -2
        return ret


    def __init__(self):
         self.__host_sim = ["netrax3-2-10","netrax3-2-115","netrax3-2-36","netrax3-2-58","netrax3-2-82"]
         self.__host_name=""

    def install_all_host(self):
         all_host_name=self.__host_sim
         for self.__host_name in  self.__host_sim:
              rt = self.installSASNCMD()

    def install_one_injector(self,host_name):
         self.__host_name=host_name
         print "install_one_injector"
         rt = self.installSASNCMD()

    def QueryAllHostInstallStatus(self):
         all_host_name=self.__host_sim
         for self.__host_name in  self.__host_sim:
              rt = self.QueryInstallSASNStatus()

    def QueryOneHostInstallStatus(self,host):
        self.__host_nam=host
        rt = self.QueryInstallSASNStatus()

if __name__  == "__main__":
    iSASN=installSASN()
    print  "This script will install SASN on SASN maintenance pool \n"
    print  "if query install status SASN on many host in maintenance pool,please input mode: 'all'\n"
    print  "if query install status on one host in maintenance pool,please input mode: 'one'\n"
    print  "other input is exit program\n"
    mode=raw_input("input mode:")

    if mode=='qm':
        iSASN.QueryAllHostInstallStatus()
    elif mode=='qo':
        host_name=raw_input("input host_name:")
        iSASN.QueryOneHostInstallStatus(host_name)

    else:
        print "mode is not correct,exit program"






