#include <math.h>
#include <ctype.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include <string.h>
#include <MPU6050_tockn.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>


#define UART_BAUDRATE 115200
#define RXD2 16 // FPGA side : (ARDUNIO_IO[9])
#define TXD2 17 // FPGA side : (ARDUNIO_IO[8])

HardwareSerial Fpga(2);
MPU6050 mpu6050(Wire);

const char* ssid = "Three_5486E7";
const char* password = "SW50PDAb?";

const char* webSocketServer = "192.168.0.159";
const uint16_t webSocketPort = 3200;
const uint16_t webSocketPort2 = 3300;
const char* webSocketPath = "/ws";
const char* webSocketProtocol = "arduino";

WebSocketsClient webSocket;
WebSocketsClient webSocket2;

int count = 0;
bool right = 0;
bool left = 0;
int colour = 0;
int output = 0;
int stored = 0;
float yellow_angle, red_angle, blue_angle;
float diff1, diff2, diff3;
int state=0;
String payload = "";
String message = "";

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WebSocket] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WebSocket] Connected to server at %s:%d\n", webSocketServer, webSocketPort);
      break;
    case WStype_TEXT:
      Serial.printf("[WebSocket] Received payload: %s\n", payload);
      break;
  }
}

void webSocketEvent2(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WebSocket2] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WebSocket2] Connected to server at %s:%d\n", webSocketServer, webSocketPort2);
      break;
    case WStype_TEXT:
      Serial.printf("[WebSocket2] Received payload: %s\n", payload);
      break;
  }
}

void sendBinaryData(String data) {
  webSocket.sendTXT(data);
}

void sendBinaryData2(String message) {
  webSocket2.sendTXT(message);
}

int byte2int(byte* buf, int size) {
  int val = 0;
  for (int i = (size - 1); i >= 0; i--) {
    val += buf[i] << (8 * i);
  }
  return val;
}

void setup() {
  Serial.print("start");
  Fpga.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  while (!Serial);
  //mpu.begin();
  Wire.begin();
  //Serial.begin(9600);
  //Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  Serial.println("Done!\n");
  Serial.println("ESP32 UART Receiver");

  webSocket.begin(webSocketServer, webSocketPort, webSocketPath, webSocketProtocol);
  webSocket2.begin(webSocketServer, webSocketPort2, webSocketPath, webSocketProtocol);
  webSocket.onEvent(webSocketEvent);
  webSocket2.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
  webSocket2.setReconnectInterval(5000);
}

void LED_angle() {
  if (output == 1 && (state == 0 || state == 3)) {
    //red_angle=0;
    state=1;
    red_angle = mpu6050.getAngleZ();
    if (red_angle > 360){
      red_angle=red_angle-360;
    }
    else if(red_angle < -360){
      red_angle=red_angle+360;
    }
    //Serial.print("red");
  }
  if (output == 2 &&  state == 1) {
    //yellow_angle=0;
    state=2;
    yellow_angle = mpu6050.getAngleZ();
    if (yellow_angle > 360){
      yellow_angle=yellow_angle-360;
    }
    else if (yellow_angle < -360) {
      yellow_angle=yellow_angle+360;
    }
    //Serial.print("yellow");
  }
  if (output == 3 && state== 2) {
    //blue_angle=0;
    state=3;
    blue_angle = mpu6050.getAngleZ();
    if (blue_angle > 360){
      blue_angle=blue_angle-360;
    }
    else if (blue_angle < -360){
      blue_angle=blue_angle+360;
    }
    //Serial.print("blue");
  }
}


double angle_Diff(float angle1, float angle2) {
  double diff = angle1 - angle2;
  return diff;
}

void calculate_Angle(float& diff1, float& diff2, float& diff3) {
  if (yellow_angle != 0 && red_angle != 0) {
    diff1 = angle_Diff(yellow_angle, red_angle); //theta
  }
  if (yellow_angle != 0 && blue_angle != 0) {
    diff2 = angle_Diff(blue_angle, yellow_angle);
  }
  if (red_angle != 0 || red_angle != 0) {
    diff3 = angle_Diff(red_angle, blue_angle); //omega
  }
}

void calculateCoordinates(float omega, float theta, float* x, float* y) {
  float a = 27;
  float b = 18;
  float d1 = a / (2.0 * tan(omega / 2.0));
  float d2 = a / (2.0 * tan(theta / 2.0));
  float d3 = b;
  float xRelative = (d1 * d1 - d2 * d2 + a * a) / (2.0 * a);
  float yRelative = sqrt(d1 * d1 - xRelative * xRelative);
  if (d3 < yRelative) {
    yRelative = -yRelative;
  }
  *x = 0.0 + xRelative;
  *y = 0.0 + yRelative;
}

void loop() {
  mpu6050.update();
  if (Fpga.available() >= 4) {
    byte buf[4];
    Fpga.readBytes(buf, 4);
    unsigned int a = byte2int(buf, 4);
    String binary = String(a, BIN);
    int binaryLength = binary.length();

    if (binaryLength < 32) {
      while (binaryLength < 32) {
        binary = "0" + binary;
        binaryLength++;
      }
    }

    if (binary == "00000000010100100100001001000010" || binary == "00000000010110010100001001000010" || binary == "00000000010001110100001001000010") {
      count = 1;
      left = false;
      right = false;
      if (binary == "00000000010100100100001001000010") {
        colour = 1;
        payload = "{\"BeaconColour\":\"red\"";
      }
      if (binary == "00000000010110010100001001000010") {
        colour = 2;
        payload = "{\"BeaconColour\":\"yellow\"";
      }
      if (binary == "00000000010001110100001001000010") {
        colour = 3;
        payload = "{\"BeaconColour\":\"blue\"";
      }
    }
    if (count == 3) {
      String bottomXaxis = binary.substring(0, 16);
      String bottomYaxis = binary.substring(16, 32);

      unsigned int bottomXaxisValue = strtoul(bottomXaxis.c_str(), nullptr, 2);
      unsigned int bottomYaxisValue = strtoul(bottomYaxis.c_str(), nullptr, 2);

      double dividedBottomXaxis = bottomXaxisValue / 639.0;
      double multipliedBottomXaxis = dividedBottomXaxis * 440.0;

      double dividedBottomYaxis = bottomYaxisValue / 479.0;
      double multipliedBottomYaxis = dividedBottomYaxis * 330.0;

      payload += ",\"BottomXaxis\":\"" + String(multipliedBottomXaxis) + "\"";
      payload += ",\"BottomYaxis\":\"" + String(multipliedBottomYaxis) + "\"}";

      sendBinaryData(payload);
      Serial.print(payload);
      Serial.println();

    }
    if (count == 2) {
      String topXaxis = binary.substring(0, 16);
      String topYaxis = binary.substring(16, 32);

      unsigned int topXaxisValue = strtoul(topXaxis.c_str(), nullptr, 2);
      unsigned int topYaxisValue = strtoul(topYaxis.c_str(), nullptr, 2);

      double dividedTopXaxis = topXaxisValue / 639.0;
      double multipliedTopXaxis = dividedTopXaxis * 440.0;

      double dividedTopYaxis = topYaxisValue / 479.0;
      double multipliedTopYaxis = dividedTopYaxis * 330.0;

      payload += ",\"TopXaxis\":\"" + String(multipliedTopXaxis) + "\"";
      payload += ",\"TopYaxis\":\"" + String(multipliedTopYaxis) + "\"";
    }

    if (left && right) {
      output = colour;
      Serial.print(output);
      Serial.println();
      Serial.print("detected");
      Serial.println();
    }

    if (left == 0 || right == 0) {
      output = 0;
      Serial.print(output);
      Serial.println();
      Serial.print("no beacons");
      Serial.println();
    }

    LED_angle();
    float diff1 = 0.0;
    float diff2 = 0.0;
    float diff3 = 0.0;
    calculate_Angle(diff1, diff2, diff3);
    message = "{\"ID\":\"1\",\"Dif1\":\"" + String(diff1) + "\",\"Dif2\":\"" + String(diff2) + "\"}";
    sendBinaryData(payload);
    Serial.print("red");
    Serial.print(red_angle);
    Serial.print("yellow");
    Serial.print(yellow_angle);
    Serial.print("blue");
    Serial.print(blue_angle);

    count++;

    Serial.print(output);
  }
  HTTPClient http;
  http.begin("http://192.168.0.159:3100/run-python");
  http.POST("");
  http.end();
  Serial.println("HTTP request sent");
  webSocket.loop();
  webSocket2.loop();
}