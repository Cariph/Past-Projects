
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
#if 0

Servo myservo1;
Servo myservo2;
Servo myservo3;

#endif

char t;
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
int enA = 10;
int enB = 11;

int pos = 130;
int pos1 = 140;
int pos2 = 45;
int pos3 = 30; 




void setup() {
pinMode(IN1,OUTPUT);   //left motors forward
pinMode(IN2,OUTPUT);   //left motors reverse
pinMode(IN3,OUTPUT);   //right motors forward
pinMode(IN4,OUTPUT);   //right motors reverse
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);

myservo.attach(12);  // attaches the servo on pin 9 to the servo object]
myservo.write(pos);

#if 0
myservo.attach(8);  // attaches the servo on pin 9 to the servo object]

myservo1.attach(9);
myservo2.attach(12);
myservo3.attach(13);
myservo1.write(pos1);
myservo2.write(pos2);
myservo3.write(pos3); 
#endif

Serial.begin(9600);
 
}
 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(IN1,HIGH);
  digitalWrite(IN3,HIGH);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  }
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(IN2,HIGH);
  digitalWrite(IN4,HIGH);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(IN3,HIGH);
  analogWrite(enB,200); 
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(IN1,HIGH);
  analogWrite(enA,200);
}
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
#if 0
  else if(t == 'A'){
   pos = pos+5;
   myservo.write(pos);
   delay(100);
   Serial.println(pos); 
   }
else if(t == 'a'){
   pos = pos-5;
   myservo.write(pos);
   delay(100);
   Serial.println(pos);
   }

else if(t == 'E'){
   pos1 = pos1+5;
   myservo1.write(pos1);
   delay(100);
   Serial.println(pos1); 
   }

else if(t == 'e'){
   pos1 = pos1-5;
   myservo1.write(pos1);
   delay(100);
   Serial.println(pos1);
   }
else if(t == 'C'){
   pos2 = pos2+5;
   myservo2.write(pos2);
   Serial.println(pos2); 
   }

else if(t == 'c'){
   pos2 = pos2-5;
   myservo2.write(pos2);
   Serial.println(pos2);
   }
else if(t == 'D'){
   pos3 = pos3+5;
   myservo3.write(pos3);
   Serial.println(pos3); 
   }

else if(t == 'd'){
   pos3 = pos3-5;
   myservo3.write(pos3);
   Serial.println(pos3);
   }
#endif

   else
   {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
   
   }
   
 
delay(500);
}
