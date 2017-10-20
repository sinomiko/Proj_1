#!/usr/bin/python
#coding=utf-8

def plot():
    import numpy as np
    import matplotlib.pyplot as plt
    plt.figure(1)  # 创建图表1
    plt.figure(2)  # 创建图表2
    ax1 = plt.subplot(211)  # 在图表2中创建子图1
    ax2 = plt.subplot(212)  # 在图表2中创建子图2
    x = np.linspace(0, 3, 100)
    for i in xrange(5):
        plt.figure(1)  # ① # 选择图表1
        plt.plot(x, np.exp(i * x / 3))
        plt.sca(ax1)  # ② # 选择图表2的子图1
        plt.plot(x, np.sin(i * x))
        plt.sca(ax2)  # 选择图表2的子图2
        plt.plot(x, np.cos(i * x))
    plt.show()


class StackIntern:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def clear(self):
        del self.items[:]

    def size(self):
        return len(self.items)

    def isEmpty(self):
        return  self.size() == 0

    def top(self):
        return self.items[self.size()-1]


def dec2bin(dec_num):
    #十进制转二进制 采用“除2取余"
    rem_stack = StackIntern()

    while dec_num > 0:
        rem = dec_num % 2
        rem_stack.push(rem)
        dec_num = dec_num //2

    bin_string = ""
    i = 0
    while not rem_stack.isEmpty():
        bin_string = bin_string + str(rem_stack.pop())


    return  bin_string

class Stack():
    def __init__(self,top=None):
        self.ll = LinkedList(top)

    def push(self, new_element):
        "Push (add) a new element onto the top of the stack"
        self.ll.insert_first(new_element)

    def pop(self):
        "Pop (remove) the first element off the top of the stack and return it"
        return self.ll.delete_first()

def testStack():
    # Test cases
    # Set up some Elements
    e1 = Element(1)
    e2 = Element(2)
    e3 = Element(3)
    e4 = Element(4)

    # Start setting up a Stack
    stack = Stack(e1)

    # Test stack functionality
    stack.push(e2)
    stack.push(e3)
    print stack.pop().value
    print stack.pop().value
    print stack.pop().value
    print stack.pop()
    stack.push(e4)
    print stack.pop().value

class Queue:
    def __init__(self):
        self.items = []

    def enqueue(self, item):
        self.items.append(item)

    def dequeue(self):
        return self.items.pop(0)

    def clear(self):
            del self.items[:]

    def size(self):
        return len(self.items)

    def isEmpty(self):
        return  self.size() == 0

    def __str__(self):
        str_item ="/"
        num = 0
        for item in self.items:
            print("item" + str(num) +"  "+ item)
            str_item = str_item +item +"/"
            num = num +1
        return str_item

def josephus(namelist, num):
    #著名的 约瑟夫斯问题（Josephus Problem）是应用队列（确切地说，是循环队列）的典型案例。
    #在 约瑟夫斯问题 中，参与者围成一个圆圈，从某个人（队首）开始报数，报数到n+1的人退出圆圈，然后从退出人的下一位重新开始报数；
    #重复以上动作，直到只剩下一个人为止。
    sim_queue = Queue()
    for name in namelist:
        sim_queue.enqueue(name)

    while sim_queue.size() > 1:
        for i in xrange(num):
            print("num-->" + str(i))
            sim_queue.enqueue(sim_queue.dequeue())
            print(sim_queue)

        print(sim_queue.dequeue())

    return  sim_queue.dequeue()

class Node:
    def __init__(self, initdata):
        self.__data = initdata
        self.__next = None

    def getData(self):
        return self.__data

    def getNext(self):
        return self.__next

    def setData(self, newdata):
        self.__data = newdata

    def setNext(self, newnext):
        self.__next = newnext

class SinCycLinkedlist:
    def __init__(self):
        self.head = Node(None)
        self.head.setNext(self.head)

    def add(self, item):
        temp = Node(item)
        temp.setNext(self.head.getNext())
        self.head.setNext(temp)

    def remove(self, item):
        prev = self.head
        while prev.getNext() != self.head:
            cur = prev.getNext()
            if cur.getData() == item:
                prev.setNext(cur.getNext())
            prev = prev.getNext()

    def search(self, item):
        cur = self.head.getNext()
        while cur != self.head:
            if cur.getData() == item:
                return True
            cur = cur.getNext()

        return False

    def empty(self):
        return self.head.getNext() == self.head

    def size(self):
        count = 0
        cur = self.head.getNext()
        while cur != self.head:
            count += 1
            cur = cur.getNext()

        return count


def SinCycLinkedlistTest():
    s = SinCycLinkedlist()
    print('s.empty() == %s, s.size() == %s' % (s.empty(), s.size()))
    s.add(19)
    s.add(86)
    s.remove(19)
    print('s.empty() == %s, s.size() == %s' % (s.empty(), s.size()))
    print('86 is%s in s' % ('' if s.search(86) else ' not',))
    print('4 is%s in s' % ('' if s.search(4) else ' not',))
    print('s.empty() == %s, s.size() == %s' % (s.empty(), s.size()))
    s.remove(19)
    print('s.empty() == %s, s.size() == %s' % (s.empty(), s.size()))


class vportIdList:

    def __init__(self, vport_index):
        self.header = Node(None)
        self.index = vport_index

    def add(self, data):
        temp = Node(data)
        temp.setNext(self.header.getNext())
        self.header.setNext(temp)

    def clear(self):
         prev = self.header.getNext()
         while prev is not None:
             print(str(prev) + str(prev.getData()))
             prev = prev.getNext()
             self.header.setNext(prev)

    def __str__(self):
        cur = self.header.getNext()
        str_list = ""
        while cur is not None:
            str_list = str_list + " / " + str(cur.getData())
            cur = cur.getNext()

        return str_list


def vportIdListTest():
    vlist = vportIdList(2001)
    vlist.add(1)
    vlist.add(2)
    vlist.add(3)
    vlist.add(4)
    vlist.add(5)
    vlist.add(6)
    vlist.add(7)
    vlist.add(8)
    vlist.add(9)
    vlist.add(10)
    print(vlist)

    vlist.clear()
    print(vlist)

"""The LinkedList code from before is provided below.
Add three functions to the LinkedList.
"get_position" returns the element at a certain position.
The "insert" function will add an element to a particular
spot in the list.
"delete" will delete the first element with that
particular value.
Then, use "Test Run" and "Submit" to run the test cases
at the bottom."""

class Element(object):
    def __init__(self, value):
        self.value = value
        self.next = None

class LinkedList(object):
    def __init__(self, head=None):
        self.head = head

    def append(self, new_element):
        current = self.head
        if self.head:
            while current.next:
                current = current.next
            current.next = new_element
        else:
            self.head = new_element

    def get_position(self, position):
        """Get an element from a particular position.
        Assume the first position is "1".
        Return "None" if position is not in the list."""
        counter = 1
        current = self.head
        if position < 1:
            return None
        while current and counter <= position:
            if counter == position:
                return current
            current = current.next
            counter += 1
        return None

    def insert(self, new_element, position):
        """Insert a new node at the given position.
        Assume the first position is "1".
        Inserting at position 3 means between
        the 2nd and 3rd elements."""
        counter = 1
        current = self.head
        if position > 1:
            while current and counter < position:
                if counter == position - 1:
                    new_element.next = current.next
                    current.next = new_element
                current = current.next
                counter += 1
        elif position == 1:
            new_element.next = self.head
            self.head = new_element

    def delete(self, value):
        """Delete the first node with a given value."""
        current = self.head
        previous = None
        while current.value != value and current.next:
            previous = current
            current = current.next
        if current.value == value:
            if previous:
                previous.next = current.next
            else:
                self.head = current.next


    def insert_first(self, new_element):
        new_element.next = self.head
        self.head = new_element


    def delete_first(self):
        if self.head:
            deleted_element = self.head
            temp = deleted_element.next
            self.head = temp
            return deleted_element
        else:
            return None

def testLinkedList():
    # Test cases
    # Set up some Elements
    e1 = Element(1)
    e2 = Element(2)
    e3 = Element(3)
    e4 = Element(4)

    # Start setting up a LinkedList
    ll = LinkedList(e1)
    ll.append(e2)
    ll.append(e3)

    # Test get_position
    # Should print 3
    print ll.head.next.next.value
    # Should also print 3
    print ll.get_position(3).value

    # Test insert
    ll.insert(e4,3)
    # Should print 4 now
    print ll.get_position(3).value

    # Test delete
    ll.delete(1)
    # Should print 2 now
    print ll.get_position(1).value
    # Should print 4 now
    print ll.get_position(2).value
    # Should print 3 now
    print ll.get_position(3).value

def binarySearch(listData, value):
    low = 0
    high = len(listData)-1

    while low <= high:
        mid = (low + high)/2
        if listData[mid] == value:
            return mid
        elif listData[mid] < value:
            low = mid + 1
        else:
            high = mid - 1
    return -1

def testBinarySearch():
    list_data = [1,2,3,4,5,6,7,8,9]
    index = binarySearch(list_data,9)
    print("ist_data[%s] = %s"%(str(index),str(9)))

if __name__ == '__main__':
#    print("main")
#    print(josephus(["A", "B", "C", "D", "E", "F"], 3))

#    SinCycLinkedlistTest()
#    vportIdListTest()
#    testLinkedList()
#    testStack()
    testBinarySearch()




