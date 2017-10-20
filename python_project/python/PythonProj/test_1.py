import random
num = random.randint(1,100)
while num != 0:
     inNum = int(raw_input("please input number:"))
     print type(inNum)
     print type(num)
     if num > inNum:
         print "{} is bigger than {}".format(num, inNum)
     elif num == inNum:
         print "{} is equal {}".format(num, inNum)
         break
     else:
         num=0
         print "{} is smaller than {}".format(num, inNum)
else:
    print "equal trigger"
# x = random.randint(1,100)
# for i in range(100):
#     if i < x:
#         print "{} is too low".format(i)
#     elif i == x:
#         print "Guessed {} correctly".format(i)
#         break
#     else:
#         print "Missed: i= {}, x ={}".format(i, x)
# else:
#         print "The number {} was not guessed".format(x)
