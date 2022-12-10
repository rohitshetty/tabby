from pynput import keyboard

import time
Key = keyboard.Key

control_keys = [
  Key.alt,
  Key.alt_gr,
  Key.alt_l,
  Key.alt_r,
  Key.backspace,
  Key.caps_lock,
  Key.cmd,
  Key.cmd_l,
  Key.cmd_r,
  Key.ctrl,
  Key.ctrl_l,
  Key.ctrl_r,
  Key.delete,
  Key.down,
  Key.end,
  Key.enter,
  Key.esc,
  Key.f1,
  Key.home,
  Key.insert,
  Key.left,
  Key.media_next,
  Key.media_play_pause,
  Key.media_previous,
  Key.media_volume_down,
  Key.media_volume_mute,
  Key.media_volume_up,
  Key.menu,
  Key.num_lock,
  Key.page_down,
  Key.page_up,
  Key.pause,
  Key.print_screen,
  Key.right,
  Key.scroll_lock,
  Key.shift,
  Key.shift_l,
  Key.shift_r,
  Key.space,
  Key.tab,
  Key.up
]


class KeyEventListener:

  def on_release(self,key):
    value = self.get_key_value(key)
    self.queue.put({
      "value": value,
      "time": time.perf_counter()  *  1000000,
      "event": "on_release"
    })

  def on_press(self,key):
    value = self.get_key_value(key)
    self.queue.put({
      "value": value,
      "time": time.perf_counter() *  1000000,
      "event": "on_press"
    })


  def get_key_value(self,key):
    if isinstance(key, keyboard.Key):
        return 200 + control_keys.index(key)
    else: 
      return ord(key.char)


  def start (self, queue):
    self.queue =  queue
    listener = keyboard.Listener(
      on_press = self.on_press,
      on_release = self.on_release
    )

    listener.start()