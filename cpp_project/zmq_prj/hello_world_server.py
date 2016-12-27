import zmq
import time

context = zmq.Context()
#socket = context.socket(zmq.REP)
#socket = context.socket(zmq.DEALER)
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:5555")
i=0
while True:
# message = socket.recv()
# print "Received request: ", message

 time.sleep(3)
 print socket.send("%s %d"%("World",i))
 i=i+1
 print socket.send("%s %d"%("World",i))
