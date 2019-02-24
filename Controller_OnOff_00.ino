#include<DHT.h>
#include<DHT_U.h>
// Supply
const int RELE = 3;

// DHT22 Temperature and humidity
int SENSOR = 2;   
float TEMPERATURA;
float HUMEDAD;
DHT dht(SENSOR, DHT22);

//DT
float DT;

//Statistics variables
int n = 10;
int ts = 100;
float Pred;
int aj = 60;

void setup() {
  pinMode(RELE,OUTPUT);
}

void loop() {
  //Pred = 0;
  DT = 0;
  // Muestreo promedio
  for (int i=0; i<n; i++){
    //Getting temperature value
    TEMPERATURA = dht.readTemperature();
    DT = DT + TEMPERATURA;
    delay(ts);
  }
  DT = DT / n ;
  DT = TEMPERATURA - Pred;
  // Getting humidity value
  HUMEDAD = dht.readHumidity();
  Pred = aj*DT + TEMPERATURA;
  if(Pred < 37.5){
    digitalWrite(RELE,HIGH);
  }
  else{digitalWrite(RELE,LOW);}
  Pred = TEMPERATURA;
}
