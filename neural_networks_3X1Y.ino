
// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud

//neural network.py
//https://github.com/husthorng/hello-world/raw/refs/heads/neural/neural%20network.py


// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL6u5it5Pr2"
#define BLYNK_TEMPLATE_NAME "neural network"
#define BLYNK_AUTH_TOKEN "y7JkJvU3Sc3wglQ4wAmf23M4aMXZNdMh"
//https://blynk.cloud/dashboard/61121/global/devices/1/organization/61121/devices/538136/dashboard
//horng.tw  mc327

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const int ledPin =  15; //D8

char auth[] = BLYNK_AUTH_TOKEN;
// float syn0[3][3]=  {-3.257387665,-0.206060687,-0.13212917,6.43315093,-1.732541429,-2.528397437,-10.3957316,-0.410807107,0.846853671};
float syn0[3][3]= {
  {-3.257387665,-0.206060687,-0.13212917},
  {6.43315093,-1.732541429,-2.528397437},
  {-10.3957316,-0.410807107,0.846853671}
  };
float syn1[3]={-2.8713582,5.718576267,-6.653749231};
float oup[3]={0,0,0};
float inp[3]={1,0,1};
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "husthung";
char pass[] = "ma2553968";
WidgetLED led1(V2);
WidgetLED led2(V3);
WidgetLED led3(V4);
WidgetLED led4(V0);
BlynkTimer timer;

//Serial.println(inp[2]);

// V1 LED Widget is blinking




void blinkLedWidget()
{
if (digitalRead(4)==HIGH){   //led on
  led2.on();
  inp[1]=1;
  }else {
  led2.off();
  inp[1]=0;
}

if (digitalRead(5)==HIGH){   //led on
  led1.on();
  inp[0]=1;
  }else {
  led1.off();
  inp[0]=0 ;
}

if (digitalRead(0)==HIGH){   //led on
  led3.on();
  inp[2]=1;
  }else {
  led3.off();
  inp[2]=0;
}
//Serial.println(inp[0]);
//Serial.println(inp[1]);
//Serial.println(inp[2]);
 int i, j, k;
  j=1;
  for (j=0; j<3; j++){  
    for (i=0; i<3; i++){
      oup[j]+=inp[i]*syn0[j][i];
    }
    oup[j]=1/(1+pow(exp(1),-oup[j]));
//    Serial.println(oup[j]);  
  }
  float outv=0;
   for (i=0; i<3; i++){
       outv+=oup[i]*syn1[i];
   }
   outv=1/(1+pow(exp(1),-outv));
   if(outv > 0.5) {
    i=1;
    digitalWrite(ledPin, HIGH);
    led4.on();
   } else {
    i=0;
    digitalWrite(ledPin, LOW);
    led4.off();
   }
  Serial.println(outv);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  timer.setInterval(1000L, blinkLedWidget);
//  Serial.println(pow(exp(1),2));

 
}

void loop()
{
  
  Blynk.run();
  timer.run();
}
