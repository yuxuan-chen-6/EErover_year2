#define trigPin1 18//left
#define echoPin1 5
#define trigPin2 27//right
#define echoPin2 26
#define trigPin3 19//front
#define echoPin3 23
#define lightPin1 25//frontleft
#define lightPin2 33//frontright
#define MAX_DISTANCE 400
#define dirPin 14//right high:后 low:前
#define stepPin 4
#define stepsPerRevolution 400
#define dirPin2 15//left: high:前 low:后
#define stepPin2 2


long duration1;
long duration2;
int distance1;
int distance2;
long duration3;
int distance3;


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
}

void forward(){
   digitalWrite(dirPin, LOW);
   digitalWrite(dirPin2, HIGH);

   for(int i=0; i<1000; i++){
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

   for(int i=0; i<1800; i++){
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

  for(int i=0; i<1300; i++){
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

  for(int i=0; i<1300; i++){
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

  for(int i=0; i<3450; i++){//310
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

  for(int i=0; i<6600; i++){//310
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(400);
    digitalWrite(stepPin, LOW);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(400);
   }
  Serial.println("turning");
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

void loop() {
    while(1){
        unsigned int D1, D2, D3;
        uint16_t L1, L2;
        sensors(D1, D2, D3, L1, L2);

        int RightLarger=D2-D1;
        int LeftLarger=D1-D2;
        int LowerError=10;
        int UpperError=100;

        if(D1==1400){
          D1=50;
        }

        
        if(L2>300&D2>60){
          backward();
          turnsmallright();
          forward();
          //turnaround();
        }

        else if(L2>300&D1>60){
          backward();
          turnsmallleft();
          forward();
          //turnaround();
        }
        
        // else if(L1>300&D1>20&D2>20){
        //   backward();
        //   //turnaround();
        // }

        // else if(L2>300&D1>20&D2>20){
        //   backward();
        //   //turnaround();
        // }

        
        else if(50<D2&&D2<1500){//右转
          forward2();
          turnright();
          //turnaround()
          forward();
          forward2();
          //turnaround();
        }

        else if(50<D1&&D1<1500){//左转
          forward2();
          turnleft();
          //turnaround()
          forward();
          forward2();
          //turnaround();
        }

        else if(D1<15&&D2<15&&L2>200){
          turn();
        }
        
        else if(D1>20&&D1<80&&D2>20&&D2<80){
          forward();
          //turnaround();
        }

        

        else if(RightLarger>LowerError&&RightLarger<UpperError){
          rightoffset();
          forward();
          //turnaround();
        }

        else if(LeftLarger>LowerError&&LeftLarger<UpperError){
          leftoffset();
          forward();
          //turnaround();
        }

        else if(RightLarger>LowerError&&RightLarger<UpperError&&L2>300){
          turnsmallright();
          forward();
          //turnaround();
        }

        else if(LeftLarger>LowerError&&LeftLarger<UpperError&&L2>300){
          leftoffset();
          forward();
          //turnaround();
        }

        else if(D2<3){
          leftoffset();
          forward();
          //turnaround();
        }

        else if(D1<3){
          rightoffset();
          forward();
          //turnaround();
          
        }

        

        else{
          forward(); 
          //turnaround();
          
        }

    }

}
