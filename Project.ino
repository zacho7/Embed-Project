#include <Mouse.h>

const int trigPin = 9;
const int echoPin = 10;
const int trigPin2 = 5;
const int echoPin2 = 6;

// defines variables
long duration;
int distance;
int D1;
int D2;

void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  Mouse.begin();
}
void loop() 
{
  SonarSensor(trigPin, echoPin);           
  D1 = distance;                     
  SonarSensor(trigPin2,echoPin2);              
  D2 = distance; 
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(D1);
  Serial.print("Distance2: ");
  Serial.println(D2);

  MouseControl();
}

//Code reference for sonar sensor function: https://www.youtube.com/watch?v=Lxh7hh_gl8Q
void SonarSensor(int trigPinSensor,int echoPinSensor)//it takes the trigPIN and the echoPIN 
{
  digitalWrite(trigPinSensor, LOW);// put trigpin LOW 
  delayMicroseconds(2);// wait 2 microseconds
  digitalWrite(trigPinSensor, HIGH);// switch trigpin HIGH
  delayMicroseconds(10); // wait 10 microseconds
  digitalWrite(trigPinSensor, LOW);// turn it LOW again
  
  duration = pulseIn(echoPinSensor, HIGH);
  distance= (duration/2) / 29.1; 
}

void MouseControl()
{
  if(D1 <20)
  {
      Mouse.move (D1 - 7,0,0);
  }

  if(D2 < 20)
  {
      Mouse.move(0,D2 - 7,0);
  }

  if(D2 > 2000 && D1 < 2000)
  {
      Mouse.press();
  }

  if(D2 < 20)
  {
      Mouse.release();
  }

  if(D1 > 2000 && D2 < 2000)
  {
      Mouse.press(MOUSE_RIGHT);
  }

   if(D1 < 20)
  {
      Mouse.release(MOUSE_RIGHT);
  }
}
