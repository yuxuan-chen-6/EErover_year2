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

#include <Ticker.h>


#define trigPin1 18//left

#define echoPin1 5

#define trigPin2 27//right

#define echoPin2 26

#define trigPin3 19//front

#define echoPin3 23

#define lightPin1 35//frontleft

#define lightPin2 33//frontright

#define MAX_DISTANCE 400

#define dirPin 14//right high:后 low:前

#define stepPin 4

#define stepsPerRevolution 400

#define dirPin2 15//left: high:前 low:后

#define stepPin2 2

#define UART_BAUDRATE 115200

#define RXD2 16 // FPGA side : (ARDUNIO_IO[9])

#define TXD2 17 // FPGA side : (ARDUNIO_IO[8])


long duration1;

long duration2;

int distance1;

int distance2;

long duration3;

int distance3;


HardwareSerial Fpga(2);

MPU6050 mpu6050(Wire);


const char* ssid = "Ethan";

const char* password = "asdfghjkl";


const char* webSocketServer = "3.93.153.98";

const uint16_t webSocketPort = 9000;

const uint16_t webSocketPort2 = 6000;

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

float yellow_red_diff, blue_yellow_diff, red_blue_diff;

int state=0;

String payload = "";

String message = "";




Ticker timer_1;

Ticker transmit;





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

    default:

      Serial.printf("nothing");

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

    default:

      Serial.printf("nothing2");

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

  // Declare pins as output:

  pinMode(stepPin, OUTPUT);

  pinMode(dirPin, OUTPUT);

  pinMode(stepPin2, OUTPUT);

  pinMode(dirPin2, OUTPUT);

  pinMode(trigPin1, OUTPUT);

  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);

  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);

  pinMode(echoPin3, INPUT);

  Serial.begin(115200);

  Serial.print("start");

  Fpga.begin(115200, SERIAL_8N1, RXD2, TXD2);

  //Serial.begin(115200);

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

  webSocket2.onEvent(webSocketEvent2);

  webSocket.setReconnectInterval(500);

  webSocket2.setReconnectInterval(500);




  timer_1.attach_ms(1,LED_angle);

  //timer_1.start();

  // transmit.attach_ms(0.1,timer);

}




void forward(){

   digitalWrite(dirPin, LOW);

   digitalWrite(dirPin2, HIGH);




   for(int i=0; i<1400; i++){

     digitalWrite(stepPin, HIGH);

     digitalWrite(stepPin2, HIGH);

     delayMicroseconds(400);

     digitalWrite(stepPin, LOW);

     digitalWrite(stepPin2, LOW);

     delayMicroseconds(400);

   }

   Serial.println("moving forward");

}




void forward2(){

   digitalWrite(dirPin, LOW);

   digitalWrite(dirPin2, HIGH);




   for(int i=0; i<1600; i++){

     digitalWrite(stepPin, HIGH);

     digitalWrite(stepPin2, HIGH);

     delayMicroseconds(400);

     digitalWrite(stepPin, LOW);

     digitalWrite(stepPin2, LOW);

     delayMicroseconds(400);

   }

   Serial.println("moving forward");

}




void backward(){

  digitalWrite(dirPin, HIGH);

  digitalWrite(dirPin2, LOW);

  

  for(int i=0; i<1400; i++){

    digitalWrite(stepPin, HIGH);

    digitalWrite(stepPin2, HIGH);

    delayMicroseconds(400);

    digitalWrite(stepPin, LOW);

    digitalWrite(stepPin2, LOW);

    delayMicroseconds(400);

   }

   Serial.println("moving backward");

}




void turnleft(){

  digitalWrite(dirPin, LOW);

  digitalWrite(dirPin2, LOW);




  for(int i=0; i<1400; i++){

    digitalWrite(stepPin, HIGH);

    digitalWrite(stepPin2, HIGH);

    delayMicroseconds(400);

    digitalWrite(stepPin, LOW);

    digitalWrite(stepPin2, LOW);

    delayMicroseconds(400);

   }

  Serial.println("turning left");

}




void turnsmallright(){

  digitalWrite(dirPin, HIGH);

  digitalWrite(dirPin2, HIGH);




  for(int i=0; i<1000; i++){

    digitalWrite(stepPin, HIGH);

    digitalWrite(stepPin2, HIGH);

    delayMicroseconds(400);

    digitalWrite(stepPin, LOW);

    digitalWrite(stepPin2, LOW);

    delayMicroseconds(400);

   }

  Serial.println("turning right");

}




void turnsmallleft(){

  digitalWrite(dirPin, LOW);

  digitalWrite(dirPin2, LOW);




  for(int i=0; i<1000; i++){

    digitalWrite(stepPin, HIGH);

    digitalWrite(stepPin2, HIGH);

    delayMicroseconds(400);

    digitalWrite(stepPin, LOW);

    digitalWrite(stepPin2, LOW);

    delayMicroseconds(400);

   }

  Serial.println("turning right");

}

 




void turnright(){

  digitalWrite(dirPin, HIGH);

  digitalWrite(dirPin2, HIGH);




  for(int i=0; i<1400; i++){

    digitalWrite(stepPin, HIGH);

    digitalWrite(stepPin2, HIGH);

    delayMicroseconds(1000);

    digitalWrite(stepPin, LOW);

    digitalWrite(stepPin2, LOW);

    delayMicroseconds(1000);

   }

  Serial.println("turning right");

}




void turn(){

  digitalWrite(dirPin, HIGH);

  digitalWrite(dirPin2, HIGH);




  for(int i=0; i<5000; i++){//310

    digitalWrite(stepPin, HIGH);

    digitalWrite(stepPin2, HIGH);

    delayMicroseconds(400);

    digitalWrite(stepPin, LOW);

    digitalWrite(stepPin2, LOW);

    delayMicroseconds(400);

   }

  Serial.println("turning");

}




void turnaround(){

  digitalWrite(dirPin, HIGH);

  digitalWrite(dirPin2, HIGH);




  for(int i=0; i<5600; i++){//310

    digitalWrite(stepPin, HIGH);

    digitalWrite(stepPin2, HIGH);

    delayMicroseconds(400);

    digitalWrite(stepPin, LOW);

    digitalWrite(stepPin2, LOW);

    delayMicroseconds(400);

   }

   cor();




  Serial.println("turning around");

}




void rightoffset(){




  digitalWrite(dirPin, HIGH);

  digitalWrite(dirPin2, HIGH);




  for(int i=0; i<400; i++){

    digitalWrite(stepPin, HIGH);

    digitalWrite(stepPin2, HIGH);

    delayMicroseconds(400);

    digitalWrite(stepPin, LOW);

    digitalWrite(stepPin2, LOW);

    delayMicroseconds(400);

   }

  Serial.println("rightoffset");

}




void leftoffset(){




  digitalWrite(dirPin, LOW);

  digitalWrite(dirPin2, LOW);




  for(int i=0; i<400; i++){

    digitalWrite(stepPin, HIGH);

    digitalWrite(stepPin2, HIGH);

    delayMicroseconds(400);

    digitalWrite(stepPin, LOW);

    digitalWrite(stepPin2, LOW);

    delayMicroseconds(400);

   }

  Serial.println("leftoffset");

}




void stopmove(){

  digitalWrite(stepPin, LOW);

  digitalWrite(stepPin2, LOW);

  Serial.println("stopped");

}




void sensors(unsigned int& distance1, unsigned int& distance2, unsigned int& distance3, uint16_t& light1, uint16_t& light2) {

  delay(400);




  digitalWrite(trigPin1, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin1, LOW);




  duration1 = pulseIn(echoPin1, HIGH);

  distance1 = duration1 * 0.034 / 2;




  digitalWrite(trigPin2, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin2, LOW);




  duration2 = pulseIn(echoPin2, HIGH);

  distance2 = duration2 * 0.034 / 2;




  digitalWrite(trigPin3, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin3, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin3, LOW);




  duration3 = pulseIn(echoPin3, HIGH);

  distance3 = duration3 * 0.034 / 2;




  Serial.print("D1:");

  Serial.print(distance1);

  Serial.print("\t\t");

  Serial.print("D2:");

  Serial.println(distance2);

  Serial.print("\t\t");

  




  light1 = analogRead(lightPin1);

  Serial.print("Frontleft light:");

  Serial.println(light1);

  Serial.print("\t\t");




  light2 = analogRead(lightPin2);

  Serial.print("Frontright light:");

  Serial.println(light2);

  Serial.print("\t\t");




  delay(1000);

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

  if (output == 2 &&  (state == 0 ||state == 1)) {

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

  if (output == 3 && (state == 0 ||state== 2)) {

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

  if (diff>180){

    diff=360-diff;

  }

  return diff;

}




void calculate_Angle(float& yellow_red_diff, float& blue_yellow_diff, float& red_blue_diff3) {

  if (yellow_angle != 0 && red_angle != 0) {

    yellow_red_diff = angle_Diff(yellow_angle, red_angle); //theta

  }

  if (yellow_angle != 0 && blue_angle != 0) {

    blue_yellow_diff = angle_Diff(blue_angle, yellow_angle);

  }

  if (red_angle != 0 || red_angle != 0) {

    red_blue_diff = angle_Diff(red_angle, blue_angle); //omega

  }

}






void cor(){

    mpu6050.update();

    timer();

  

    

    //LED_angle();

    float diff1 = 0.0;

    float diff2 = 0.0;

    float diff3 = 0.0;

    calculate_Angle(diff1, diff2, diff3);

    message = "{\"ID\":\"1\",\"Dif1\":\"" + String(diff1) + "\",\"Dif2\":\"" + String(diff2) + "\"}";

    sendBinaryData(message);

    Serial.print("red");

    Serial.print(red_angle);

    Serial.print("yellow");

    Serial.print(yellow_angle);

    Serial.print("blue");

    Serial.print(blue_angle);

    webSocket2.loop();

    

  }

//  HTTPClient http;

//  http.begin("http://192.168.0.159:3100/run-python");

//  http.POST("");

//  http.end();

  // Serial.println("HTTP request sent");




void timer(){

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

    }

    webSocket.loop();

}




void loop() {

        unsigned int D1, D2, D3;

        uint16_t L1, L2;

        sensors(D1, D2, D3, L1, L2);




        int RightLarger=D2-D1;

        int LeftLarger=D1-D2;

        int LowerError=5;

        int UpperError=100;




        if(D1==1400){

          D1=50;

        }




        

        if(L1>300&D2>60){

          backward();

          turnsmallright();

          forward();

          turnaround();

        }




        else if(L1>300&D1>60){

          backward();

          turnsmallleft();

          forward();

          turnaround();

        }

        

        else if(L1>300&D1>20&D2>20){

          backward();

          turnaround();

        }




        else if(L2>300&D1>20&D2>20){

          backward();

          turnaround();

        }




        

        else if(50<D2&&D2<1500){//右转

          forward2();

          turnright();

          //turnaround()

          forward();

          forward2();

          turnaround();

        }




        else if(50<D1&&D1<1500){//左转

          forward2();

          turnleft();

          //turnaround()

          forward();

          forward2();

          turnaround();

        }




        else if(D1<15&&D2<15&&L1>200){

          turn();

        }

        

        else if(D1>20&&D1<80&&D2>20&&D2<80){

          forward();

          turnaround();

        }




        




        else if(RightLarger>LowerError&&RightLarger<UpperError){

          rightoffset();

          forward();

          turnaround();

        }




        else if(LeftLarger>LowerError&&LeftLarger<UpperError){

          leftoffset();

          forward();

          turnaround();

        }




        else if(RightLarger>LowerError&&RightLarger<UpperError&&L1>300){

          turnsmallright();

          forward();

          turnaround();

        }




        else if(LeftLarger>LowerError&&LeftLarger<UpperError&&L1>300){

          leftoffset();

          forward();

          turnaround();

        }




        else if(D2<3){

          leftoffset();

          forward();

          turnaround();

        }




        else if(D1<3){

          rightoffset();

          forward();

          turnaround();

          

        }




        




        else{

          forward();

          turnaround();

          

        }

      count++;

      Serial.print(output);




}