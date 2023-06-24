const int trigPin1 = 18;
const int echoPin1 = 5;
#define lightPin1 25

long duration1;

int distance1;
int light1;


void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  Serial.begin(115200);
}

void loop() {
  delay(50);
  // 测量左边儿传感器的距离
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  light1 = analogRead(lightPin1); 
  // Serial.print("Frontleft light:");
  // Serial.println(light1);
  // Serial.print("\t\t");

  // 打印距离数据到串口
  Serial.print(distance1);
  Serial.print(",");
  Serial.println(light1);
  
  
  //delay(1000);
}
