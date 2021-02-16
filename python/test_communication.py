import time
import zmq

if __name__ == "__main__":
    context = zmq.Context()
    sender = context.socket(zmq.PUSH)
    sender.connect("tcp://127.0.0.1:10000")

    receiver = context.socket(zmq.PULL)
    receiver.connect("tcp://127.0.0.1:10001")

    while True:
        print("Sending Hello World!")
        sender.send(b"Hello World!", zmq.DONTWAIT)
        time.sleep(5)
