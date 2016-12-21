import zmq

context = zmq.Context()
print "Connecting to hello world server..."
#socket = context.socket(zmq.REQ)
socket = context.socket(zmq.DEALER)
socket.connect ("tcp://localhost:5555")

for request in range (10):
 print "Sending request ", request,"..."
 socket.send ("Hello")
 message = socket.recv()
 print "Received reply ", request, "[", message, "]"
