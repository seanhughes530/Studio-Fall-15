#include <SoftwareSerial.h>

SoftwareSerial xbeeSerial(2, 3);  //RX, TX

const int button = 5;  //button
const int redLed = 10;  //red led
const int greenLed = 9;  //green led
const int pot = 0;  //potentiometer

int potVal = 0; //value of the potentiometer
int buttonState = LOW;  //starting value of button

//String friendMessage = " 

String name = "Sean ";
String name1 = "Enayet ";
String name2 = "Marco ";
String name3 = "Juno "; 
String ender = "\n";

//String buffer = "";

void setup() {
   Serial.begin(9600);
   Serial.println("Broadcasting your name. See if others receive it.");
   
   xbeeSerial.begin(9600);
   xbeeSerial.println("Hey, it's Sean!");
   
   pinMode(button, INPUT);
   pinMode(redLed, OUTPUT);
   pinMode(greenLed, OUTPUT);
   
}

void loop(){
  int buttonState = digitalRead(button);

  
  if (buttonState == HIGH) {
    
    potVal = analogRead(pot);
    
    xbeeSerial.println(name1 + potVal + ender);
    xbeeSerial.println(name2 + potVal + ender);
    xbeeSerial.println(name3 + potVal + ender);
   
    digitalWrite(greenLed, HIGH);
    delay(500);
    digitalWrite(greenLed, LOW);
    //delay(1000);

  }
  
  serialCheck();

}

void serialCheck() {
 if (xbeeSerial.available() > 0) {
    String buffer;
    buffer = xbeeSerial.readStringUntil('\n');  //error
    if (buffer.startsWith(name, 0)) {
      Serial.println(buffer);
      int bright = xbeeSerial.parseInt();
      digitalWrite(redLed, bright);
      delay(500);
      digitalWrite(redLed, LOW);
  }
  } 
}


