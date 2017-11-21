#!/usr/bin/env python
# -*- coding:utf-8 -*-
# -*- author:miko-*-
# python3抓取bing主页所有背景图片
import urllib.request
import urllib,re,sys,os
def get_bing_backphoto():

    if (os.path.exists('img')== False):
        os.mkdir('img')
    for i in range(0,24):
        url = 'https://cn.bing.com/?toHttps=1&redig=265CBC0D09884CB58695FFDF89ADE88E'
        #url = 'http://cn.bing.com/HPImageArchive.aspx?format=js&idx='+str(i)+'&n=1&nc=1361089515117&FORM=HYLH1'
        html = urllib.request.urlopen(url).read()
        if html == 'null':
            print( 'open & read bing error!')
            sys.exit(-1)
        html = html.decode('utf-8')
        #print (html)
        reg = re.compile('"url":"(.*?)","urlbase"',re.S)
        text = re.findall(reg,html)
        #http://s.cn.bing.net/az/hprichbg/rb/LongJi_ZH-CN8658435963_1366x768.jpg
        for imgurl in text :
            right = imgurl.rindex('/')
            name = imgurl.replace(imgurl[:right+1],'')
            savepath = 'img/'+ name
            print (imgurl)
            urllib.request.urlretrieve(imgurl, savepath)
            #print (name + ' save success!')
get_bing_backphoto()