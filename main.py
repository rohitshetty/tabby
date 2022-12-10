from pynput import keyboard

from src.KeyEventListener import KeyEventListener
from src.LightStream import LightStream
import queue as Queue
from threading import Thread

# ws=websocket.WebSocket()
# ws.connect("ws://192.168.0.187:81")

# q=[0]*60*3
# ws.send_binary(bytearray(q))

# q[len(q) - 3]=255
# keyboard_queue = deque(q, maxlen=60*3)


def main ():
  queue = Queue.Queue()
  key_listener = KeyEventListener()
  light_stream = LightStream()

  streamer = Thread(target=light_stream.start_stream, args=(queue,))
  streamer.setDaemon(True)
  key_listener.start(queue)

  streamer.start()
  streamer.join()


if __name__ == "__main__":
  main()



