#include<DHT.h>
#include<DHT_U.h>
#include <LiquidCrystal.h>
// Supply
const int RELE = 23;

// DHT22 Temperature and humidity
int SENSOR = 22;   
float TEMPERATURA;
float HUMEDAD;
DHT dht(SENSOR, DHT22);

// Parameters
float fixed = 37.5;
float uncertain = 0.01;

//DT
float DT;

//Statistics variables
int n = 10;
int ts = 100;
float Pred;
int aj = 30;

// LCD 16x2 (módulo) con A0 para botones
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  dht.begin();
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);
  pinMode(RELE,OUTPUT);
  digitalWrite(RELE,LOW);
  Pred = dht.readTemperature();
}

void loop() {
  // Reescribir
  //Serial.println(Pred);
  //lcd.clear();
  lcd.setCursor(0,0);
  //Pred = 0;
  DT = 0;
  // Muestreo promedio
  for (int i=0; i<n; i++){
    //Getting temperature value
    TEMPERATURA = dht.readTemperature();
    DT = DT + TEMPERATURA;
    delay(ts);
  }
  TEMPERATURA = DT / n ;
  Serial.print(TEMPERATURA);
  Serial.print(",");
  lcd.print("T:"+String(TEMPERATURA));
  DT = TEMPERATURA - Pred;
  // Getting humidity value
  HUMEDAD = dht.readHumidity();
  Serial.print(HUMEDAD);  
  Serial.print(",");
  lcd.print(" H:"+String(HUMEDAD));
  Pred = aj*DT + TEMPERATURA;
  lcd.setCursor(0,1);
  Serial.print(DT);
  Serial.print(",");
  lcd.print("DT:"+String(DT));
  Serial.println(Pred);
  //Serial.print(",");
  lcd.print(" P:"+String(Pred));
  if(Pred < fixed*(1-uncertain) & DT<0){
    digitalWrite(RELE,LOW);
  }
  if(Pred > fixed*(1+uncertain) & DT>0){
    digitalWrite(RELE,HIGH);
    }
  Pred = TEMPERATURA;
}
