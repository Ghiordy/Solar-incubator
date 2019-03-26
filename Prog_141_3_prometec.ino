/*  ----------------------------------------------------------------
    http://www.prometec.net/data-logger-shield
    Prog_146_1
    
    Ejemplo de data loggin con reloj y SD card
--------------------------------------------------------------------  */
//#include <DHT11.h>
#include <SD.h>
#include <Wire.h>
#include <SPI.h>     // Necesario para la SD card
#include "RTClib.h"

//DHT11 dht11(6);     // Definimos el sensor de temperatura
RTC_DS1307 RTC;     // Definimos el reloj
File logfile;       // Fichero a escribir en la SD
const int chipSelect = 10;  // SD card pin select
const bool eco = true ;
int count = 0 ;       // Controla cada cuanto tiemepo se vuelcan los datos a la SD

void setup() 
{
    Serial.begin(9600);
    pinMode(5, OUTPUT)  ;       // DHT11 GMD
    pinMode(7, OUTPUT) ;        // DHT11 Vcc
    pinMode(6, INPUT_PULLUP) ;  // DHT11 pin de lectura
    pinMode(chipSelect, OUTPUT);        // SD card pin select

    digitalWrite(7, HIGH) ;   // Damos tension al DHT11
    digitalWrite(5, LOW) ;

    if (!SD.begin(chipSelect)) 
          error("No hay tarjeta SD.");
    else
          Serial.println("Tarjeta SD inicializada.");

  // Creamos el fichero de registro
  char filename[] = "LOGGER00.CSV";
  //char filename[] = "LOGGER00.txt"; doesn't work
  for (uint8_t i = 0; i < 100; i++) 
     {  
        filename[6] = i/10 + '0';
        filename[7] = i%10 + '0';
        if (! SD.exists(filename))      // Si no existe el fichero, lo creamos
            { 
              logfile = SD.open(filename, FILE_WRITE); 
              break;  // leave the loop!
            }
     }
  if (! logfile) 
      error("No s epudo crear el fichero de registro");
    
  Serial.print("Registrando en: ");   Serial.println(filename);

  // connect to RTC
  Wire.begin();  
  if (!RTC.begin()) 
      logfile.println("No hay RTC.");   
  else
      Serial.println("RTC correcto. Iniciando captura de datos");   

  logfile.print("Fecha/Hora") ; 
  logfile.print(", ");
  //logfile.print(" ID ") ; 
  //logfile.print(", ");  
  logfile.print("Temp") ; 
  logfile.println("Humedad") ; 
}

void loop() 
{      DateTime now;
       int err  ;
       float temp, hum;
       
       //if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
       if(1)    // Si devuelve 0 es que ha leido bien
          {  now = RTC.now();
                   
             logfile.print(now.unixtime()); // seconds since 1/1/1970
             logfile.print(", ");
             //logfile.print(count);
             //logfile.print(", ");
             logfile.print("temperatura");
             logfile.print(", ");
             logfile.println("humedad");
             if ( count++ > 64 ) 
                {   logfile.flush(); // Para forzar la escritura en la SD
                    count = 0 ;       // Cada 64 lecturas
                }
             if (eco)
              {
                 Serial.print(now.unixtime()); // seconds since 1/1/1970
                 Serial.print(", ");
                 Serial.print(count);
                 Serial.print(", ");
                 Serial.print(temp);
                 Serial.print(", ");
                 Serial.println(hum);
              }
          }
       else
          {
             Serial.println();
             Serial.print("Error Num :");
             Serial.print(err);
             Serial.println();
          }
       delay(1000);            //Recordad que solo lee una vez por segundo
}

void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);
  
  while(1);
}
