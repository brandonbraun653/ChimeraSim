import time
import zmq

if __name__ == "__main__":
    context = zmq.Context()
    sender = context.socket(zmq.PUSH)
    sender.connect("tcp://127.0.0.1:11010")

    receiver = context.socket(zmq.PULL)
    receiver.connect("tcp://127.0.0.1:11000")

    while True:
        print("Waiting for data")
        received_data = receiver.recv()
        sender.send(bytearray(10))
