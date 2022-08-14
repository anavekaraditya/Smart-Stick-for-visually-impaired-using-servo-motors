#include <Servo.h>

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
int pos = 0;
int limit = 100;
int curDist = 200;
int left[200],right[200];
int leftflag=0;
int rightflag=0;
Servo myservo;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   myservo.attach(9);
   pinMode(4, OUTPUT);
}

void loop() {
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   curDist = dist();
   Serial.print(curDist);
  Serial.print('\n');
  if (curDist<=limit){
    Serial.print("Obstacle ahead\n");
    digitalWrite(4, HIGH);
    delay(1000);
    digitalWrite(4, LOW);
    Serial.print("Scanning\n");
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      left[pos]=dist();
      //delay(15);                       // waits 15ms for the servo to reach the position
  	}
  	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      right[pos]=dist();
      //delay(15);                       // waits 15ms for the servo to reach the position
  	}
    for(int i=0;i<=60; i++){
      if (left[i]<=limit){
         leftflag = 1;
         break; 
      }
    }
    for(int i=0;i<=60; i++){
      if (right[i]<=limit){
    	rightflag = 1;
    	break;
    	}
    }
    if (leftflag==1 && rightflag==1)
      Serial.print("Turn around");
    else if (leftflag==1)
      Serial.print("Turn Right");
    else if (rightflag==1)
      Serial.print("Turn Left");
    delay(5000);
  }
  
 
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

int dist(){
      digitalWrite(pingPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(pingPin, LOW);
      pinMode(echoPin, INPUT);
      long duration = pulseIn(echoPin, HIGH);
      long cm = microsecondsToCentimeters(duration);
      //Serial.print(cm);
      //Serial.print("cm\n");
  	  return cm;

   }
