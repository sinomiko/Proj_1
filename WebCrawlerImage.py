#coding=utf-8
import urllib2
import urllib
import re
import time
import os
import uuid
#获取二级页面url
def findUrl2(html):
    "http://bbs.fengniao.com/forum/pic/slide_101_5581752_75587059.html"
    re1 = r'http://bbs.fengniao.com/forum/pic/\w+\.html'
    url2list = re.findall(re1,html)
    url2lstfltr = list(set(url2list))
    url2lstfltr.sort(key=url2list.index)
    #print url2lstfltr
    return url2lstfltr
#获取html文本
def getHtml(url):
    html = urllib2.urlopen(url).read().decode('utf-8')
    #print html
    return html


def download(html_page , pageNo):
    #定义文件夹的名字
    x = time.localtime(time.time())
    foldername = str(x.__getattribute__("tm_year"))+"-"+str(x.__getattribute__("tm_mon"))+"-"+str(x.__getattribute__("tm_mday"))
    #http://img3.fengniao.com/forum/attachpics/833/21/33284130_1500.jpg
    re1=r'http://img3.fengniao.com/forum/attachpics/.+/.+/.+\.jpg'
    rg = re.compile(re1)
    myItems= rg.findall(html_page)

    for item in myItems:

        picpath = 'c:\\FengNiao\\%s\\%s'  % (foldername,str(pageNo))
        filename = str(uuid.uuid1())
        if not os.path.exists(picpath):
            os.makedirs(picpath)
        target = picpath+"\\%s.jpg" % filename
        print   item
        print "The photos location is:"+target
        download_img = urllib.urlretrieve(item, target)#将图片下载到指定路径中
        time.sleep(1)
    return download_img


if __name__ == '__main__':
    pageNo = raw_input("Input the page number you want to scratch (1-100):")


    if pageNo==1:
         html = getHtml("http://bbs.fengniao.com/jinghua-101.html")
    else:
         html = getHtml("http://bbs.fengniao.com/jinghua-101-%s.html"% pageNo)
    #print html
    detllst = findUrl2(html)
    for detail in detllst:
        try:
           html2 = getHtml(detail)
        except :
            print  "This page does not have any pictures"
            continue
        #print html2
        download(html2,pageNo)
    print "Finished."