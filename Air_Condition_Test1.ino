//www.elegoo.com
//2016.12.9

#include <SimpleDHT.h>
#include <ESP8266WiFi.h>

//SSID of your network
char ssid[] = "AndroidAP"; //SSID of your Wi-Fi router
char pass[] = "ahmed2014"; //Password of your Wi-Fi router
IPAddress ip;
int LED = 1;



void setup()
{

  Serial.begin(115200);
  delay(10);

  pinMode(LED, OUTPUT); // initialize digital pin LED_BUILTIN as an output.

  // Connect to Wi-Fi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to... ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected successfully");
  ip = WiFi.localIP();
  Serial.print("IP Address: "); Serial.println(ip);
}


// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DAT A: 2
int pinTemp1 = 5;
SimpleDHT11 Temp1;

int pinTemp2 = 4;
SimpleDHT11 Temp2;




void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample Temp1...");
  
  // read with raw sample data.
  byte temperature_1 = 0;
  byte humidity_1 = 0;
  byte data_1[40] = {0};
  if (Temp1.read(pinTemp1, &temperature_1, &humidity_1, data_1)) {
    Serial.print("Read Temp1 failed");
    Serial.println();
   
  }
  
  Serial.print("Sample Temp1 RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data_1[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  Serial.println("");
  
  Serial.print("Sample Temp1 Reading: ");
  Serial.print((int)temperature_1); Serial.print(" *C, ");
  Serial.print((int)humidity_1); Serial.println(" %");
  
  // Temp1 sampling rate is 1HZ.
  delay(1500);


// Temp2

  Serial.println("Sample Temp2...");
  byte temperature_2 = 0;
  byte humidity_2 = 0;
  byte data_2[40] = {0};

if (Temp2.read(pinTemp2, &temperature_2, &humidity_2, data_2)) {
    Serial.print("Read Temp2 failed");
    return;
  }
  
  Serial.print("Sample Temp2 RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data_2[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  Serial.println("");
  
  Serial.print("Sample Temp2 Reading: ");
  Serial.print((int)temperature_2); Serial.print(" *C, ");
  Serial.print((int)humidity_2); Serial.println(" %");
  
  // Temp2 sampling rate is 1HZ.
  delay(1500);

if ((int)temperature_1 >= (int)temperature_2  ||  (int)temperature_2 <= (int)temperature_1 ) 
{
 
  int results;
  results =  (int)temperature_1 - (int)temperature_2;

  if (results >= 2 || results <= -2)
   {
      Serial.println("Air conditioning is Activated!");
      digitalWrite(LED, HIGH); 
    //turn on light
   
   }
    else 
    {
     Serial.println("Air conditioning is De-activated");
     digitalWrite(LED, LOW);

     //turn off light 
     }

   
   }

   
}




