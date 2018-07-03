from concurrent.futures import ThreadPoolExecutor


def normal_print(content):
    print content

def safe_print(content):
    print "{0}\n".format(content),


with ThreadPoolExecutor(max_workers=10) as executor:
    print "Normal Print:"
    for i in range(10):
        executor.submit(normal_print, i)

print "---"

with ThreadPoolExecutor(max_workers=10) as executor:
    print "Safe Print:"
    for i in range(10):
        executor.submit(safe_print, "========================================================================================================================================================================="+str(i))