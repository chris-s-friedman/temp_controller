#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
int heattrig = 6;
int cooltrig = 7;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
  pinMode(heattrig, OUTPUT); 
  pinMode(cooltrig, OUTPUT);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.print("Read DHT11 failed");
    return;
  }

  float tempF = (temperature *9.0)/5.0 + 32.0; //Converts celcius to F
  
  Serial.print("Sample RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  Serial.println("");
  
  Serial.print("Sample OK: ");
  Serial.print((int)tempF); Serial.print(" *F, ");
  Serial.print((int)humidity); Serial.println(" %");

  // Now make the lights do a thing
  if ( tempF > 80) {
    digitalWrite(cooltrig, HIGH);
  }
  if ( tempF < 78) {
    digitalWrite(heattrig, HIGH);
  }
  if ( (tempF > 73) && (tempF < 77) ) {
    digitalWrite(cooltrig, LOW);
    digitalWrite(heattrig, LOW);
  }
  
  // DHT11 sampling rate is 1HZ.
  delay(2000);
}
