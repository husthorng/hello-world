//https://blynk.cloud/dashboard/61121/global/devices/3361292/organization/61121/devices/2048871/dashboard
//horng.tw  mr255
// neural network 4X1y
//「backpropagation_4X1y.ipynb」的副本

#define BLYNK_TEMPLATE_ID "TMPL6u5it5Pr2"
#define BLYNK_TEMPLATE_NAME "neural network 4X1y"
#define BLYNK_AUTH_TOKEN "s8S9T6dwbDN_EJTyd59_vQti3lsKn8jH"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const int ledPin =  15; //D8

char auth[] = BLYNK_AUTH_TOKEN;


float syn0[5][4]={{ 2.43881911, -2.00482047, -3.52309918, -1.78689134},
                  { 1.77106518, -6.7691496 , -4.47574199, -2.05742115},
                  {-1.91476977, -2.33165092,  3.44338743,  1.94485302},
                  {-5.48345287,  5.17576009, -8.03027744,  5.12680574},
                  {-0.52775859,  1.84445603,  1.67602221,  0.26912009}};

float syn1[5][1]={{ 7.66137175},
                  {12.38983421},
                  {-9.2833714 },
                  {-6.48193551},
                  { 0.60008338}};

float oup[5]={0,0,0,0,0};
float inp[5]={0,0,1,1,1};
float nnod_1[5]={0,0,0,0,1};


// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "CHT7947";
char pass[] = "0492553968";


//char ssid[] = "husthung";
//char pass[] = "ma2553968";


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

    float outv=0;
  
  
   for (i=0; i<5; i++){
      outv+=nnod_1[i]*syn1[i][0];
   }

  outv=1/(1+pow(exp(1),-outv));

   if(outv > 0.5) {
    i=1;
    digitalWrite(ledPin, HIGH);
    out1.on();
   } else {
    i=0;
    digitalWrite(ledPin, LOW);
    out1.off();
   }

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
