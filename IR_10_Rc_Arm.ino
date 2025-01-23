#include <IRremote.h>
#define Forward 0x962814CA
#define Backward 0x5990708A
#define Right 0xB012615A
#define Left 0xB2CC429A
#define SW7 0x7A6E10BA
#define SW8 0x97123E8A
#define SW6 0x1C22DE05
#define SW5 0x8D2A4BAF
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;

int IN1 = 10; //2;
int IN2 = 11; //3;
int IN3 = 12; //4;
int IN4 = 13; //5;
int enA = 5; // 6; // 10;
int enB = 6; // 11; // 9;

int pos1 = 140;
int pos2 = 45;
int pos3 = 30; 

int dir = 5;
int countOn = 10;


int receiver = 4; // 6;
//uint32_t Previous;
IRrecv irrecv(receiver);
decode_results result;

void setup() {
pinMode(IN1,OUTPUT);   //left motors forward
pinMode(IN2,OUTPUT);   //left motors reverse
pinMode(IN3,OUTPUT);   //right motors forward
pinMode(IN4,OUTPUT);   //right motors reverse
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
myservo1.attach(7); // 8 
myservo2.attach(8);  
myservo3.attach(9);
myservo1.write(pos1);
myservo2.write(pos2);
myservo3.write(pos3); 
Serial.begin(9600);
irrecv.enableIRIn();

}

void RunWheels(long aValue)
{
     Serial.print("Print in RW: ");
     Serial.println(aValue, HEX);
     
  bool isWheelCode = true;

  if(aValue==Forward){
  digitalWrite(IN3,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(enA,200);
  analogWrite(enB,200);
  }
  
  else if(aValue==Backward){ 
  digitalWrite(IN2,HIGH);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,LOW);
  analogWrite(enA,200);
  analogWrite(enB,200);

  }
  
  else if(aValue==Right){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);  
  digitalWrite(IN4,LOW);
  analogWrite(enA,200);
  }
  
  else if(aValue==Left){
  digitalWrite(IN3,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);  
  digitalWrite(IN4,LOW);
  analogWrite(enB,200);
  }

  if (isWheelCode == true)
  {
     countOn = countOn + 10;
     delay(countOn);
  }
   else
  {
    isWheelCode = false;
    countOn = 10;
  }
}

bool Arm(long aValue){
  
  bool isArmCode = true;

  Serial.println( (String)"Pos1:" + pos1 + " Pos2:" + pos2 + " Pos3:" + pos3); 

  if ((pos1 > 170) || (pos2 > 170) || (pos3 > 170))
    dir = -5;
    
  if ((pos1 < 10 ) || (pos2 < 10) || (pos3 < 10))
    dir = 5;  
    
  if(aValue == SW5){
   pos1 = pos1 + dir;
   myservo1.write(pos1); 
   Serial.println(pos1); 
  }
  
  else if(aValue == SW6){ 
   pos2 = pos2 + dir;   
   myservo2.write(pos2);
   Serial.println(pos2);

  }
  
  else if(aValue == SW8){
   pos3 = pos3 + dir ;
   myservo3.write(pos3);
   Serial.println(pos3);
  }
  
  else if(aValue == SW7){
    if (dir > 0)
      dir = -5;
    else 
      dir = 5;

    delay(1000);
  }
  else
    isArmCode = false;

  return isArmCode;

}
void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&result)){
   Serial.println(result.value,HEX);
   RunWheels(result.value);
   Arm(result.value);
   // delay(800);
   irrecv.resume();
  }
  else
  {
   // Serial.println("General else ");

    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }
}

