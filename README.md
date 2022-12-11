# tabby

Control WS2812 (Or any LED strip controllable by Neopixel library, with changes ofc) over the browser using Websockets.

I wanted to have a background light for my work setup that I can tweak minimally as needed. Hence, Tabby.

ToDo:

- [x] PoC connect WS8212 to ESP8266 and establish websocket connection from browser
- [ ] Add Frontend UI to gather IP address to prevent hard coding
- [ ] Save the IP in Session to avoid asking for the IP in subsequent loads
- [ ] Save the selected Color in the non-volatile memory of the Arduino
- [ ] Instructions on deployment of the SPA
- [ ] Explore ways to discover the device over network to automatically pick up the IP (probably not possible in android chrome due to non support mDNS, but other platform can use mDNS)

## Source code

`firmware/tabby` - has the arduino sketch that can be loaded into Arduino IDE and the libraries installed.
Dependencies: TBA

`web-controller` - Simple React App that can connect to the ESP8266 and send the color code

## Hardware

ESP8266 is connected to WS2812B LED strip. WS2812B can individually set RGB for the LEDs (but only global brightness). The firmware sets up the controller to act as a websocket server running on port 81.
Incoming message Bytes are then set as RGB and brightness for each of the LEDs in the string.

## Software

**Firmware** for the controller sets it up as the Websocket server that expects 4 byte message. first 3 bytes are RGB and the last byte is the brightness value.
Firmware also sets up the controller for OTA updates, so after initial Flashing, subsequent flashing can be done over the Air using Arduino IDE.

**Web Controller** is a simple React app that connects to the websocket server and sends over the selected RGB and Alpha value (mapped as brightness)
