#include<Servo.h>
const int noOfServos =4;
Servo myservo[noOfServos];

int touchSensor              [noOfServos] = { 10, 9, 5, 6 };
bool doubleClick             [noOfServos];
bool holdOn                  [noOfServos];
bool firstClick              [noOfServos];
bool forward                 [noOfServos];
int currentPress             [noOfServos];
unsigned long currentMillis  [noOfServos];
unsigned long previousMillis [noOfServos];
int countOn [noOfServos];
int pos [noOfServos];

void setup() {//setup
  for (int i = 0; i < noOfServos ; ++i)
  {
    doubleClick[i] = false; 
    holdOn[i] = false;
    firstClick[i] = false;
    forward[i] = true; 
    currentPress[i] = 0;
    currentMillis[i] = 0;
    previousMillis[i] = 0;
    countOn[i] = 0;
    pos [i] = 0;     
  }
  myservo[0]. attach(3);
  myservo[1]. attach(11);
  myservo[2]. attach(2);
  myservo[3]. attach(4);
  
  Serial.begin(9600); //configures serial port
  pinMode(touchSensor,INPUT); //touchsesor is now an input
}


void loop() 
{
  // put your main code here, to run repeatedly:


  for (int servo = 0; servo < noOfServos ; ++servo)
  {
   	currentPress[servo] = digitalRead(touchSensor[servo]);
		// current press in now equal to the touch Sensor value 
		// (currentPress = pinMode(10,INPUT))

  	if (digitalRead(touchSensor[servo])) //when touched 
  	{
			++countOn[servo];//keep on adding one 
			//until it reaches 2000 milliseconds (2 seconds) 
			if ((countOn[servo] == 13000) && (firstClick[servo]==true) && (doubleClick[servo]==false)) 
			{
				Serial.print("hold ");//when it reaches to 2 seconds print hold
				Serial.println(servo);
				countOn[servo]= 0;
				holdOn[servo] = true;   
			}

		 
				currentMillis[servo] = millis();
				if((currentMillis[servo] - previousMillis[servo]) > 1200 && 
						(holdOn[servo] == false) && (doubleClick[servo] == false))
				{
					//oneclick
					Serial.print   ("single click" );
					Serial.println (servo);
					//Serial.println(currentMillis);
					//Serial.println(previousMillis);
					previousMillis[servo] = currentMillis[servo];
					firstClick[servo] = true;
				}
				else if(((currentMillis[servo] - previousMillis[servo]) < 1500) &&
								 (currentMillis[servo] - previousMillis[servo] > 1000)  && 
								 (firstClick[servo] == true) && (holdOn[servo] == false) && 
									(doubleClick[servo] ==false))
				{
					//DoubleClick
					Serial.print("double click" );
					Serial.println(servo);
					//Serial.println(currentMillis);
					//Serial.println(previousMillis);
					previousMillis[servo] = currentMillis[servo];
					firstClick[servo] = false;
					doubleClick[servo] = true; 
					forward[servo] = !forward[servo]; 
				}
  	}
  	else
    {
    if ((holdOn[servo] == true) && (firstClick[servo] == true) && (doubleClick[servo] == false))
    {
       Serial.print("hold is off");
       Serial.println(servo);
       holdOn[servo]=false; 
       firstClick[servo] = false;
     
    }
    if (doubleClick[servo] == true) 
    {
      doubleClick[servo] = false;
    }


    
  }

   	if ( holdOn[servo] == true)
		{

		 if (forward[servo] == true) 
		 {
				if(pos[servo] < 178)
					++pos[servo];
				else
				{ 
					--pos[servo];
					forward[servo] = false; 
				}
		 }
		 else
		 {
				if(pos[servo] > 2)
				--pos[servo];
				else
				{ 
					++pos[servo];
					forward[servo] = true; 
				}
		 }
			
			myservo[servo].write(pos[servo]);
			delay (15);
		}
  }

}
 

