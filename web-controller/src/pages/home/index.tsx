import React, { useState, useEffect } from "react";
import { RgbaColorPicker } from "react-colorful";
import "./style.css";
import useWebSocket, { ReadyState } from "react-use-websocket";
const Home = () => {
  const [color, setColor] = useState({ r: 200, g: 150, b: 35, a: 1 });
  const { sendMessage } = useWebSocket("ws://192.168.0.187:81");

  useEffect(() => {
    console.log("color", color);

    // ws.send(colorArray);
    const colorArray = new Uint8Array([
      color.r,
      color.g,
      color.b,
      color.a * 255,
    ]);

    // @ts-ignore
    // colorArray[0] = color.r;
    // // @ts-ignore
    // colorArray[1] = color.g;
    // // @ts-ignore
    // colorArray[2] = color.b;
    console.log(colorArray);
    sendMessage(colorArray);
  }, [color]);

  return (
    <div className="responsive example">
      <RgbaColorPicker color={color} onChange={setColor} />
    </div>
  );
};

export default Home;
