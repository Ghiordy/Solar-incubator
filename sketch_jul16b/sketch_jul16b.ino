//https://www.luisllamas.es/tarjeta-micro-sd-arduino/
#include <SD.h>
 
File logFile;
boolean saver;
 
void setup()
{
  Serial.begin(9600);
  Serial.print(F("Iniciando SD ..."));
  if (!SD.begin(9))
  {
    Serial.println(F("Error al iniciar"));
    return;
  }
  Serial.println(F("Iniciado correctamente"));
}
 
 
// Funcion que simula la lectura de un sensor
//int readSensor()
//{
//  delay(1000);
//   return analogRead(A0);
//}
 
void loop()
{
  Serial.print("SD value ");
  Serial.println(SD.begin(9));
  // Abrir archivo y escribir valor
  logFile = SD.open("datalog.txt", FILE_WRITE);
  
  if (logFile) { 
        int value = analogRead(A0);
        logFile.print("Time(ms)=");
        logFile.print(millis());
        logFile.print(", value=");
        logFile.println(value);
        Serial.println(value);
        logFile.close();
  
  } 
  else {
    Serial.println("Error al abrir el archivo");
    while (!logFile){
      logFile = SD.open("datalog.txt", FILE_WRITE);
      if (logFile) { 
        int value = analogRead(A0);
        logFile.print("Time(ms)=");
        logFile.print(millis());
        logFile.print(", value=");
        logFile.println(value);
        Serial.println(value);
        logFile.close();
  
  }
      }
  }
  
  delay(1000);
}
