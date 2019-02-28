#include <SD.h>
#include <DHT.h>    // importa la Librerias DHT
#include <DHT_U.h>
#include <EEPROM.h>

// File .txt for micro SD 
File logFile;
boolean saver;
//String file = "datalog.txt";
String file = "datalog";
String ext = ".txt";
const int enable = 10;
const int reboot = 8;
const int address = 100;
int login;

// DHT22 Temperature and humidity
//Internal
int SENSOR_i = 2;
float TEMPERATURA_i;
float HUMEDAD_i;
DHT dhti(SENSOR_i, DHT22);
// Enviroment
int gndDHTe = 4;
int SENSOR_e = 5; 
int powDHTe = 6;
float TEMPERATURA_e;
float HUMEDAD_e;
DHT dhte(SENSOR_e, DHT22);


// Sensor de corriente
// Voltios/Amperio sensor de 30A
float Sensibilidad = 0.066; 
float Iread,Ivalue;
int Ipin = A1;

// Sensor de voltaje de 0-25 V
int Vpin = A2;    
float Vvalue;

void setup(){
  Serial.begin(9600);
  pinMode(enable,INPUT);
  pinMode(reboot,INPUT);
  pinMode(powDHTe,OUTPUT);
  digitalWrite(powDHTe,HIGH);
  pinMode(gndDHTe,OUTPUT);
  digitalWrite(gndDHTe,LOW);
  pinMode(SENSOR_e,INPUT);
  if (digitalRead(reboot)==1){
    rebooting();}
  setupLogging();
}

void setupLogging(){
  login = EEPROM.read(address) + 1;
  EEPROM.write(address,login);
  //Serial.println(login);
  file = file + login + ext;
  Serial.println(file);
  dhti.begin();
  dhte.begin();
  Serial.print(F("Iniciando SD ..."));
  if (!SD.begin(9)){
    Serial.println(F("Error al iniciar"));
    return;
  }
  Serial.println(F("Iniciado correctamente"));
}

void loop(){
  // Getting temperature value INTERNAL
  TEMPERATURA_i = dhti.readTemperature(); 
  // Getting humidity value INTERNAL
  HUMEDAD_i = dhti.readHumidity();   
  // Getting temperature value ENVIROMENT
  TEMPERATURA_e = dhte.readTemperature(); 
  // Getting humidity value ENVIROMENT
  HUMEDAD_e = dhte.readHumidity();   
  //V=l*(Vomax/Vimax)
  Vvalue = analogRead(Vpin)*(0.0244); 
  Iread = analogRead(Ipin)*(5.0 / 1023.0);
  Ivalue=(Iread-2.5)/Sensibilidad;
  delay(200);

  // Uncoment next lines for check SD satatus
  /*Serial.print("SD value ");
  Serial.println(SD.begin(9));*/
  
  // Openning file and enable to write
  logFile = SD.open(file, FILE_WRITE);
  
  if (logFile) {
    printer();
  } 
  else {
    Serial.println("Error al abrir el archivo");
    while (!logFile){
      logFile = SD.open(file, FILE_WRITE);
      if (logFile) { 
        printer();
      }}}}

void printer(){
  if(digitalRead(enable)==0){
    logFile.print(millis());
    Serial.print(millis());
    logFile.print(",");
    Serial.print(",");
    logFile.print(TEMPERATURA_i);
    Serial.print(TEMPERATURA_i);
    logFile.print(",");
    Serial.print(",");
    logFile.print(HUMEDAD_i);
    Serial.print(HUMEDAD_i);
    logFile.print(",");
    Serial.print(",");
    logFile.print(TEMPERATURA_e);
    Serial.print(TEMPERATURA_e);
    logFile.print(",");
    Serial.print(",");
    logFile.print(HUMEDAD_e);
    Serial.print(HUMEDAD_e);
    logFile.print(",");
    Serial.print(",");
    logFile.print(Vvalue);
    Serial.print(Vvalue);
    logFile.print(",");
    Serial.print(",");
    logFile.println(Ivalue);
    Serial.println(Ivalue); 
    logFile.close();
  }else{
    Serial.println("Not saving");
    Serial.print(millis());
    Serial.print(",");
    Serial.print(TEMPERATURA_i);
    Serial.print(",");
    Serial.print(HUMEDAD_i);
    Serial.print(",");
    Serial.print(TEMPERATURA_e);
    Serial.print(",");
    Serial.print(HUMEDAD_e);
    Serial.print(",");
    Serial.print(Vvalue);
    Serial.print(",");
    Serial.println(Ivalue); 
    logFile.close();
    }
  }


void rebooting(){
  Serial.print("Rebooting... ");
  EEPROM.write(address,0);
  for (int i=0; i<10;i++){
    Serial.print(10-i);
    Serial.print(", ");
    delay(1000);
    }
  Serial.println("Rebooting done!");
  }
