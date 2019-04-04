#include <SD.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <DHT.h>    // importa la Librerias DHT
#include <DHT_U.h>


// LCD 16x2 (módulo) con A0 para botones
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Sensor de corriente
float Sensibilidad = 0.066; // Voltios/Amperio sensor de 30A
float Iread,Ivalue;
int Ipin = A8;

// Sensor de voltaje de 0-25 V
int Vpin = A9;    
float Vvalue;

// DHT 22
int SENSOR = A10;
float TEMPERATURA,HUMEDAD;
DHT dht(SENSOR, DHT22);

// Timer
long To=0;

// SD file
File logFile;
boolean saver;

void setup(){
  dht.begin();
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);
  Serial.print(F("Iniciando SD ..."));
  if (!SD.begin(9))
  {
    Serial.println(F("Error al iniciar"));
    return;
  }
  Serial.println(F("Iniciado correctamente"));
}

void loop(){
  if(millis() > To + 1000){
    // Reescribir
    lcd.clear();
    lcd.setCursor(0,0);

    // Temperatura (°C)
    TEMPERATURA = dht.readTemperature();
    Serial.print(TEMPERATURA);
    Serial.print(",");
    lcd.print("T:"+String(TEMPERATURA));

    // Humedad relativa (%)
    HUMEDAD = dht.readHumidity();
    Serial.print(HUMEDAD);  
    Serial.print(",");
    lcd.print(" H:"+String(HUMEDAD));

    lcd.setCursor(0,1);

    // Voltaje (V)
    Vvalue = analogRead(Vpin)*(0.0244); //V=l*(Vomax/Vimax)
    Serial.print(Vvalue);
    lcd.print("V:"+String(Vvalue));
    Serial.print(",");

    // Corriente (A)
    Iread = analogRead(A8)*(5.0 / 1023.0);
    Ivalue=(Iread-2.5)/Sensibilidad;
    Serial.println(Ivalue); 
    lcd.print(" I:"+String(Ivalue));

  //Serial.print("SD value ");
  //Serial.println(SD.begin(9));
  
    // Abrir archivo y escribir valor
    logFile = SD.open("datalog.txt", FILE_WRITE);
    
    if (logFile) {
          logFile.print(millis());
          logFile.print(TEMPERATURA);
          logFile.print(HUMEDAD);
          logFile.print(Vvalue);
          logFile.print(Ivalue);
          logFile.close();
    
      } 
    else {
      Serial.println("Error al abrir el archivo");
      while (!logFile){
        logFile = SD.open("datalog.txt", FILE_WRITE);
        if (logFile) {
          logFile.print(millis());
          logFile.print(TEMPERATURA);
          logFile.print(HUMEDAD);
          logFile.print(Vvalue);
          logFile.print(Ivalue);
          logFile.close();
                      }
                  }
         }
     To = millis();
  }
}
