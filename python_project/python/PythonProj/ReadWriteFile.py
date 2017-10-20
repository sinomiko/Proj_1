outfile=open("helloworld.txt","w")
for num1 in range(1,10):
    for num2 in range(1,10):
        if  num2<=num1 :
            outfile.write("{}*{}={} ".format(num2, num1 ,num1 * num2))
    outfile.write(" \n")


outfile.flush()
outfile.close()

infile=open("helloworld.txt","r")
for line in infile.readlines():
    print line

infile.close()

import sys
sys.stdout.write("foo\n")
sys.stderr.write("foo2 \n")

def test_var_kwargs(farg, **kwargs):
    print "formal arg:", farg
    for key in kwargs:
        print "arg: {}:{}".format(key, kwargs[key])

test_var_kwargs(2,a="sd",b="ds")

def return_stuff(var):
    return [1, 2,{'a':1, 'b':2},'string']

a=return_stuff(1)
print a

x=222
def t1():
    global x
    x=111



t1()
print x

import  os
for ld in os.listdir("c:/Miko"):
    print ld

print os.listdir("c:/Miko")

class Person(object):
    def __init__(self, first_name, last_name):
        self.first_name = first_name
        self.last_name = last_name
    def get_first_name(self):
        return self.first_name
    def set_first_name(self, new_name):
        self.first_name = new_name
p = Person("John", "Smith")
#p.set_first_name("FooJohn")
print p.get_first_name()
print dir(p)[-4:]


class Single(object):
    def __i