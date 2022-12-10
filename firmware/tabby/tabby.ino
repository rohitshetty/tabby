#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "credentials.h"

#include <NeoPixelBrightnessBus.h>
#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelSegmentBus.h>


#define colorSaturation 255
const uint16_t PixelCount =60;


const char* ssid = SECRET_STASSID;
const char* password = SECRET_STAPSK;


NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

// int A = {182,2,232];
RgbColor A(182, 2, 232);
RgbColor B(2,106,242);
RgbColor C(9,219,79);
RgbColor D(245,233,0);
RgbColor E(235,108,0);

RgbColor colors[] = {A,B,C,D,E};

void setup() {
  // Serial.begin(115200);
  // Serial.println("Booting");
  strip.Begin();
  strip.Show();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    // Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() { 
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    // Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    // Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));

    strip.SetPixelColor(0, blue);
    strip.SetPixelColor(1, blue);
    strip.SetPixelColor(2, blue);
    strip.SetPixelColor(3, blue);
    strip.Show();
  });
  ArduinoOTA.onError([](ota_error_t error) {
    strip.SetPixelColor(0, red);
    strip.SetPixelColor(1, red);
    strip.SetPixelColor(2, red);
    strip.SetPixelColor(3, red);
    strip.Show();

    //    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      //      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      //      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      //      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      //      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      //      Serial.println("End Failed");
    }
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));

    strip.SetPixelColor(0, blue);
    strip.SetPixelColor(1, blue);
    strip.SetPixelColor(2, blue);
    strip.SetPixelColor(3, blue);
    strip.Show();
  });
  ArduinoOTA.onError([](ota_error_t error) {
    strip.SetPixelColor(0, red);
    strip.SetPixelColor(1, red);
    strip.SetPixelColor(2, red);
    strip.SetPixelColor(3, red);
    strip.Show();

    //    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      //      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      //      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      //      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      //      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      //      Serial.println("End Failed");
    }
  });

  ArduinoOTA.begin();
  // Serial.println("Ready");
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());
  strip.SetBrightness(100);
  
  for (int j=0; j < 6; j++) {

  RgbColor color = colors[j];
  for (int i = 0; i < PixelCount; i++) {
    // RgbColor color (payload[i * 3], payload[i * 3 + 1], payload[i * 3 + 2]);

    strip.SetPixelColor(i, color);
  }

  strip.Show();
  delay(5000);
    
  }


}

// Rgbcolor getColor(int i) {
//   switch(i) {
//     case 0:
//       return A;
//     case 1:
//       return B;
//     case 2: 
//       return C;
//     case 3:
//       return D;
//     case 4:
//       return E;
//     default;
//       return A;
//   }
// }

void loop() {
  ArduinoOTA.handle();




}
