import urllib, urllib2, sys


host = 'http://ali.api.intdata.cn'
path = '/stock/hs_level2/real'
method = 'GET'
appcode = '你自己的AppCode'
querys = 'code=sz000002'
bodys = {}
url = host + path + '?' + querys

request = urllib2.Request(url)
request.add_header('Authorization', 'APPCODE ' + appcode)
response = urllib2.urlopen(request)
content = response.read()
if (content):
    print(content)