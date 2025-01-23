#include <IRremote.h>
#define Forward 0x962814CA
#define Backward 0x5990708A
#define Right 0xB012615A
#define Left 0xB2CC429A
int IN1 = 8;
int IN2 = 11;
int IN3 = 12;
int IN4 = 13;
int enA = 5; // 6; // 10;
int enB = 3; // 11; // 9;

int receiver = 6; // 7;
uint32_t Previous;
IRrecv irrecv(receiver);
decode_results result;

void setup() {
pinMode(IN1,OUTPUT);   //left motors forward
pinMode(IN2,OUTPUT);   //left motors reverse
pinMode(IN3,OUTPUT);   //right motors forward
pinMode(IN4,OUTPUT);   //right motors reverse
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
Serial.begin(9600);
irrecv.enableIRIn();

}

void RunWheels(long aValue)
{
     Serial.print("Print in RW: ");
     Serial.println( aValue, HEX);
     

    if(aValue==Forward){
  digitalWrite(IN3,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN4,HIGH);
  analogWrite(enB,200);
  analogWrite(enA,200);
  }
  
  else if(aValue==Backward){ 
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN3,HIGH);
  analogWrite(enB,200);
  analogWrite(enA,200);

  }
  
  else if(aValue==Right){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);  
  digitalWrite(IN4,LOW);
  analogWrite(enA,200);
  }
  
  else if(aValue==Left){
  digitalWrite(IN3,LOW);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);  
  digitalWrite(IN4,HIGH);
  analogWrite(enB,200);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&result)){
   
   Serial.println(result.value,HEX);

   RunWheels(result.value);
   delay(800);
   irrecv.resume();
  }
  else
  {
    Serial.println("General else ");

    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }
}


