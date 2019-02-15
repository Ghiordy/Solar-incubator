#include <SD.h>
#include <DHT.h>    // importa la Librerias DHT
#include <DHT_U.h>

File logFile;
boolean saver;

int SENSOR = 2;     // pin DATA de DHT22 a pin digital 2
int TEMPERATURA;
int HUMEDAD;

DHT dht(SENSOR, DHT22);


// Sensor de corriente
float Sensibilidad = 0.066; // Voltios/Amperio sensor de 30A
float Iread,Ivalue;
//int Ipin = A8;

// Sensor de voltaje de 0-25 V
//int Vpin = A9;    
float Vvalue;

void setup(){
  dht.begin();
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
  TEMPERATURA = dht.readTemperature();  // obtencion de valor de temperatura
  HUMEDAD = dht.readHumidity();   // obtencion de valor de humedad
  /*Serial.print("T: ");  // escritura en monitor serial de los valores
  Serial.print(TEMPERATURA);
  Serial.print("H: ");
  Serial.println(HUMEDAD);
  delay(500);*/
  delay(5000);
  Serial.print("SD value ");
  Serial.println(SD.begin(9));
  // Abrir archivo y escribir valor
  logFile = SD.open("datalog.txt", FILE_WRITE);
  
  if (logFile) { 
        int temp = TEMPERATURA;
        int rh = HUMEDAD;
        //logFile.print("Time(ms)=");
        //logFile.print(millis());
        //logFile.print(", value=");
        logFile.print(TEMPERATURA);
        Serial.print(TEMPERATURA);
        logFile.print(",");
        Serial.print(",");
        logFile.println(HUMEDAD);
        Serial.println(HUMEDAD);
        logFile.close();
  
  } 
  else {
    Serial.println("Error al abrir el archivo");
    while (!logFile){
      logFile = SD.open("datalog.txt", FILE_WRITE);
      if (logFile) { 
        int temp = TEMPERATURA;
        int rh = HUMEDAD;
        //logFile.print("Time(ms)=");
        //logFile.print(millis());
        //logFile.print(", value=");
        logFile.print(TEMPERATURA);
        Serial.print(TEMPERATURA);
        logFile.print(",");
        Serial.print(",");
        logFile.println(HUMEDAD);
        Serial.println(HUMEDAD);
        logFile.close();
      }}}}
