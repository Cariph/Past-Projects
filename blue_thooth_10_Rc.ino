

char t;
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
int enA = 10;
int enB = 11;

#define ENABLE_ALL 1

void setup() {
pinMode(IN1,OUTPUT);   //left motors forward
pinMode(IN2,OUTPUT);   //left motors reverse
pinMode(IN3,OUTPUT);   //right motors forward
pinMode(IN4,OUTPUT);   //right motors reverse
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
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

#ifdef ENABLE_ALL
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
#endif
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  }
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(IN2,HIGH);
  digitalWrite(IN4,HIGH);
#ifdef ENABLE_ALL
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,LOW);
#endif

  analogWrite(enA, 200);
  analogWrite(enB, 200);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(IN3,HIGH);
#ifdef ENABLE_ALL
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
#endif

  analogWrite(enB,200); 
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(IN1,HIGH);
#ifdef ENABLE_ALL
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
#endif

  analogWrite(enA,200);
}
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
else {      //STOP (all motors stop)
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
 
   
 
delay(1000);
}
