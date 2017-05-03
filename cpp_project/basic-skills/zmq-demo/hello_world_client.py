import zmq

context = zmq.Context()
print "Connecting to hello world server..."
#socket = context.socket(zmq.REQ)
#socket = context.socket(zmq.DEALER)
socket = context.socket(zmq.SUB)
socket.connect ("tcp://localhost:5555")
socket.setsockopt(zmq.SUBSCRIBE, "World")

while True:
  message = socket.recv()
  print "Received reply: " ,"[", message, "]"
#for request in range (1000):
# print "Sending request ", request,"..."
# socket.send ("Hello")
# message = socket.recv()
# print "Received reply ", request, "[", message, "]"
