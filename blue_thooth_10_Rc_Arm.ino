/////////////////////
//make sure to include the enA and enB pins for the DC motors 
//enA and enB must be connected to pwm pins 
//if pwm pins don't work try a new set of pwm pins 
//on the arduino board 
/////////////////////
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;

char t;
int IN1 = 2;
int IN2 = 3; 
int IN3 = 4;
int IN4 = 5;
int enA = 6; // 10;
int enB = 11; // 9;

int pos = 130;
int pos1 = 140;
int pos2 = 45;
int pos3 = 30; 

int dir = 5;


void setup() {
pinMode(IN1,OUTPUT);   //left motors forward
pinMode(IN2,OUTPUT);   //left motors reverse
pinMode(IN3,OUTPUT);   //right motors forward
pinMode(IN4,OUTPUT);   //right motors reverse
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
// myservo.attach(9);  // 7attaches the servo on pin 9 to the servo object]
myservo1.attach(10); // 8 
myservo2.attach(12);  
myservo3.attach(13);
myservo1.write(pos1);
myservo2.write(pos2);
myservo3.write(pos3); 
Serial.begin(9600);
 
}
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 if ((pos1 > 170) || (pos2 > 170) || (pos3 > 170))
    dir = -5;
    
 if ((pos1 < 10 ) || (pos2 < 10) || (pos3 < 10))
    dir = 5;  
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(IN1,HIGH);
  digitalWrite(IN3,HIGH);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  }
 
else if(t == 'T'){      //move reverse (all motors rotate in reverse direction)
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

else if(t == 'A'){
   pos1 = pos1 + dir;
   myservo1.write(pos1); 
   Serial.println(pos1);
   }

else if(t == 'B'){
   pos2 = pos2 + dir;   
   myservo2.write(pos2);
   Serial.println(pos2);
   }

else if(t == 'C'){
   pos3 = pos3 + dir ;
   myservo3.write(pos3);
   Serial.println(pos3); 
   }

else if(t == 'D'){
    if (dir > 0)
      dir = -5;
    else 
      dir = 5;
    delay(1000);
   }
   else
   {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
   }
   
 
delay(500);
} 
