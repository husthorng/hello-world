#include <Wire.h>
#include "IRremote.hpp"


#define BLYNK_TEMPLATE_ID "TMPLuCNU_F1h"
#define BLYNK_TEMPLATE_NAME "1 Button  LED"
#define BLYNK_AUTH_TOKEN "2PldsJDctqONEx_OTJDcE7b4guWwZJoO"
//https://blynk.cloud/dashboard/219843/global/devices/1/organization/219843/devices/2040484/dashboard

//hustblynk@gmail.com    mb2496

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
#include "DHT.h"

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "husthung";
char pass[] = "ma2553968";

BlynkTimer timer;

#define LED_PIN 15      //D8
#define BUTTON_PIN 13   //D7
#define buzzer 12       //D6
const int irReceiverPin = D5;
unsigned long lastSignalTime = 0;
unsigned long signalIgnoreInterval = 500; // 100 milliseconds


byte lastButtonState = LOW;
byte ledState = LOW;
int buttonState = 0;



WidgetLED led1(V11);


void buzzer1(int delayTime)
{
  int i;
  for(i=0;i<50;i++)
    { 
     digitalWrite(buzzer,HIGH);
     delay(delayTime);
     digitalWrite(buzzer,LOW);
     delay(delayTime);
    } 
  
} 


BLYNK_WRITE(11) // At global scope (not inside of the function)
{
    int i=param.asInt();
    if (i==1) 
    {
    digitalWrite(BUTTON_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(buzzer,HIGH);
  //  buzzer1(1);    
    }
    else 
    {
    digitalWrite(BUTTON_PIN, LOW);
    digitalWrite(LED_PIN, LOW);  
    digitalWrite(buzzer,LOW);
    }
}



void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(LED_PIN, OUTPUT);
  pinMode(buzzer,OUTPUT);  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  IrReceiver.begin(irReceiverPin , ENABLE_LED_FEEDBACK);  
  delay(100);
}

void loop()
{
    if (IrReceiver.decode()) {

        unsigned long int decCode = IrReceiver.decodedIRData.command;
    //    Serial.println(decCode, HEX);
          Serial.println(decCode);

      unsigned long currentTime = millis();
        if (currentTime - lastSignalTime > signalIgnoreInterval) {

          if (decCode == 16) {
 //           byte buttonState = digitalRead(BUTTON_PIN);


              digitalWrite(LED_PIN, !digitalRead(LED_PIN));
               Blynk.virtualWrite(V11,digitalRead(LED_PIN));
//              ledState=digitalRead(LED_PIN);
//              buttonState = digitalRead(LED_PIN);
//              lastSignalTime = currentTime;
              delay(1000);
           }

           IrReceiver.resume();
        }

      }



  byte buttonState = digitalRead(BUTTON_PIN);
  //Serial.print(buttonState);
  //Serial.print("\n");
   if (buttonState != lastButtonState) {
      lastButtonState = buttonState;
      if (buttonState == LOW) {   
        ledState = (ledState == HIGH) ? LOW: HIGH;
        Serial.print("button is on data=100.0\n");
        digitalWrite(LED_PIN, ledState);
        Blynk.virtualWrite(V11,ledState);
if (ledState == HIGH){
    digitalWrite(buzzer,HIGH);
  }
  else {
    digitalWrite(buzzer,LOW);
  }              
//        led1.on();
        delay(1000);
//        ledState=LOW;
//        digitalWrite(LED_PIN, ledState); 
//        Blynk.virtualWrite(V11,LOW);
//        led1.off();
      }
   }

  Blynk.run();

}
