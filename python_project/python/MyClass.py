#!/usr/bin/python
#coding=utf-8
#TODO:类方法
class MyClass:

    name1="default"
    def __init__(self):
        self.name1="MyClass"
    def method(self):
        print self.name1
        print "I have a MyClass method1"
    def __IAMethod(self):
        print "I have a MyClass __IAMethod "
    def setName1(self,name):
        self.name1=name



Instance=MyClass()
Instance.method()
Instance.setName1("second")
Instance.method()


Instance2=MyClass()
Instance2.method()
Instance2.name1="third"
Instance2.method()

class MyClass2(MyClass):
    def __init__(self):
        self.name1="MyClass2"
    def method(self):
        print self.name1
        print "I have a MyClass2 method"

class Myclass3(MyClass2):
    pass
InstanceM2=MyClass2()
InstanceM2.method()
InstanceM2.name1="MyClass2:2"
InstanceM2.method()

print  issubclass(MyClass2,MyClass)
print MyClass2.__bases__
print  InstanceM2.__class__

#TODO:异常捕获
try:
    x=input('Enter the first number:')
    y=input('Enter the second number:')
    print x/y
except (ZeroDivisionError,TypeError),e:
    print "error the second is zero"
    print "hold on"
    print  e
else:
    print "nothing wrong"
finally:
    print  "finally"

#TODO:覆盖父类构造函数
class Bird:
    def __init__(self):
        self.hungry=True;
    def eat(self):
        if self.hungry:
            print 'yumy'
            self.hungry=False
        else:
            print 'No 3X'

class SongBird(Bird):
    def __init__(self):
        Bird.__init__(self)
        # 或者直接赋值
        # Bird.hungry=True
        # 或者super方法
        # super(SongBird,self).__init__()
        self.sound="门前大桥下"
    def sing(self):
        print self.sound

sb=SongBird()
sb.sing()
sb.eat()
sb.eat()

class Rectangle:
    def __init__(self):
        self.width=0
        self.heith=0
    def setSize(self,size):
        self.width,self.heith=size
    def getSize(self):
        return  self.width,self.heith
    size=property(setSize,getSize)

r=Rectangle()
r.width=10
r.heith=20
# r.size
r.size=150,100

print "r:"+str(r.getSize())

#TODO:迭代器
class Fibs:
    def __init__(self):
        self.a=0
        self.b=1
    def next(self):
        self.a,self.b=self.b,self.a+self.b
        return  self.a
    def __iter__(self):
        return self

fibs=Fibs()

for f in  fibs:
    if f>1000:
        print  f
        # 内建异常
        raise  StopIteration

#TODO:生成器
def flatten(nested):
    for sublist in nested:
        for element in sublist:
            yield element


nested=[[1,2],[3,4],[5]]
for num in flatten(nested):
    print num

list(flatten(nested))

