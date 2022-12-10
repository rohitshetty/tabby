import matplotlib.cm as cm
from matplotlib.colors import Normalize
import time
import websocket
from collections import deque
from math import sqrt, exp
norm = Normalize(vmin=0, vmax=257)

class LightStream:
  
  def start_stream(self, queue):
    previous_time = None
    ws=websocket.WebSocket()
    ws.connect("ws://192.168.0.187:81")

    keyboard_stream = deque([0]*60*3,maxlen=60*3)

    while True:
      # send_start = time.perf_counter() * 1000000
      # if previous_time is None:
      #   previous_time = send_start

      msg = queue.get()
      
      if msg is None:
        continue
      
      value = msg.get('value')
      time_p = msg.get('time')
      event = msg.get('event')

      # sent_delta = send_start - previous_time
      # print("sent_delta",sent_delta)
      # print(type(time_p))

      # while (((time.perf_counter() * 1000000) -  time_p) < sent_delta):
      #   continue
      # print("current_delta,", time.perf_counter() * 1000000 -  time_p)
      
      # previous_time = time_p
      color = cm.viridis(norm(value));
      print(color)
      print("value:", value, color, norm(value))

      keyboard_stream.append(int(color[0]*256))
      keyboard_stream.append(int(color[1]*256))
      keyboard_stream.append(int(color[2]*256))

      light_stream = list(keyboard_stream.copy())
      light_stream.reverse()
      # print(light_stream)
      ws.send_binary(bytearray(light_stream))


