#coding=utf-8
import urllib2
import urllib
import re
import time
import os
import uuid
#获取二级页面url

def download( year):

   # http://yjsjw.usst.edu.cn/yjsphoto/142460384.jpg
   index=0
   while index<150:

        student_id=int(year)*10000000+7660550+index;
        index=index+1
        pic_path = 'c:\\yjsphoto\\'
        if not os.path.exists(pic_path):
            os.makedirs(pic_path)
        target = pic_path+"\\%s.jpg" % (str(student_id))
        item=' '
        try :
             item="http://yjsjw.usst.edu.cn/yjsphoto/%s.jpg"%student_id
             download_img = urllib.urlretrieve(item, target)#将图片下载到指定路径中
        except:
            print "student_id does exist"
            continue
        print "The photos location is:"+target
        time.sleep(1)


if __name__ == '__main__':
    year = raw_input("Input year you want to scratch (13/14/15):")
    download(year)
    print "Finished."


#http://yjsjw.usst.edu.cn/yjsphoto/142460384.jpg