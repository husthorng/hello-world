
// neural network 4X1y
//backpropagation_4x2y.ipynb
//https://colab.research.google.com/drive/1kzRu2XxZtT6cYhEdR7p2S3UrEU97hfeg?usp=sharing


//https://blynk.cloud/dashboard/61121/global/devices/3361292/organization/61121/devices/2048871/dashboard
//horng.tw  mc327
//#define BLYNK_TEMPLATE_ID "TMPL6u5it5Pr2"
//#define BLYNK_TEMPLATE_NAME "neural network 4X1y"
//#define BLYNK_AUTH_TOKEN "s8S9T6dwbDN_EJTyd59_vQti3lsKn8jH"

#define BLYNK_TEMPLATE_ID "TMPLvSzhWs1e"
#define BLYNK_TEMPLATE_NAME "horng ex1"
#define BLYNK_AUTH_TOKEN "cazwu-xn6t4_dj9Pi2UvpJgE8AJAnC_9"
//https://blynk.cloud/dashboard/180590/global/devices/4542549/organization/180590/devices/798433/dashboard
//hustvsc1@  ma2496


#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const int ledPinD8 =  15; //D8
const int ledPinD7 =  16; //D0

char auth[] = BLYNK_AUTH_TOKEN;

       

float syn0[5][4]={{-4.35491885,  6.33096348, -5.81280878,  0.71073579},
                  {-0.1535507 ,  0.41335711, -0.44124504,  4.97236024},
                  {-5.63332814, -1.44982941,  0.35258915,  0.78357392},
                  { 0.25345681,  5.18569569, -3.70126497,  5.05058305},
                  { 7.07183028, -1.25418903,  2.09417836, -8.71029492}};

float syn1[5][2]={{  2.07935484,  12.46266627},
                  {  8.79461484,  -4.25471526},
                  { -7.12424243,   5.3049791 },
                  {-13.39786643,  -6.82527069},
                  { -1.68811209,  -1.48972636}};


float oup[5]={0,0,0,0,0};
float inp[5]={0,0,1,1,1};
float nnod_1[5]={0,0,0,0,1};


// Your WiFi credentials.
// Set password to "" for open networks.


char ssid[] = "husthung";
char pass[] = "ma2553968";


WidgetLED out1(V0);
WidgetLED out2(V1);
WidgetLED led1(V2);
WidgetLED led2(V3);
WidgetLED led3(V4);
WidgetLED led4(V5);
BlynkTimer timer;


//Serial.println(inp[2]);

// V1 LED Widget is blinking




void blinkLedWidget()
{
  out1.off();
  out2.off();
  if (digitalRead(5)==HIGH){   //led on
    led1.on();
    inp[0]=1;
    }else {
    led1.off();
    inp[0]=0;
  }

  if (digitalRead(4)==HIGH){   //led on
    led2.on();
    inp[1]=1;
    }else {
    led2.off();
    inp[1]=0 ;
  }

  if (digitalRead(0)==HIGH){   //led on
    led3.on();
    inp[2]=1;
    }else {
    led3.off();
    inp[2]=0;
    }
  if (digitalRead(2)==HIGH){   //led on
    led4.on();
    inp[3]=1;
    }else {
    led4.off();
    inp[3]=0;
    }
//    int inp[5]={0,0,1,1,1};

 int i, j, k;
 float oup[5]={0,0,0,0,0};
  for (j=0; j<4; j++){  

    for (i=0; i<5; i++){
      oup[j]+=inp[i]*syn0[i][j];
    }

    oup[j]=1/(1+pow(exp(1),-oup[j]));
  }


    for (j=0; j<4; j++){  
      nnod_1[j]=oup[j];
    }

    float outv[2]={0,0};
  
    for (j=0; j<2; j++){   
      for (i=0; i<5; i++){
          outv[j]+=nnod_1[i]*syn1[i][j];
      }
      outv[j]=1/(1+pow(exp(1),-outv[j]));
    }
  

//  Serial.println(outv[0]);

    if(outv[0] > 0.5) {
//    i=1;
    digitalWrite(ledPinD7, HIGH);
    out1.on();
   } else {
//    i=0;
    digitalWrite(ledPinD7, LOW);
    out1.off();
   }

    if(outv[1] > 0.5) {
//    i=1;
    digitalWrite(ledPinD8, HIGH);
    out2.on();
   } else {
//    i=0;
    digitalWrite(ledPinD8, LOW);
    out2.off();
   }

}

void setup()
{
  pinMode(ledPinD7, OUTPUT);
  pinMode(ledPinD8, OUTPUT);
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
