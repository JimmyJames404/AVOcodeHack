#include <DHT.h>//Utilizamos este sensor como manera practica de simular el prototipo 
//aqui se incluira la liberria de los demas sensores, los siguientes serian del ethernet shield:
//#include <SPI.h> 
//#include <Ethernet.h>
// con los anteriores podemos usarlo coo webserver
#include <LiquidCrystal.h>//Este nos permite poder ver la informacion que esta recibiendo el sensor en una pantalla LCD (no incluida en el prototipado ya que la app permitira hacer estas lecturas)
 
#define DHTPIN 8  // De esta manera definimos que pin sera utilizado por nuestro sensor          
 //Inicializamos la comunicacion serial a 9600bps

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // pines necesarios para ver el lcd( no incluidad en el protitipado, ya que podran visualizarle desde la app)
#define DHTTYPE DHT11       
DHT dht(DHTPIN, DHTTYPE);   
//Variabless
char temperature[] = "Temp = 00.0 C  ";
char humidity[]    = "RH   = 00.0 %  ";
// Asignacion de pines
void setup() {
pinMode(A0,OUTPUT);                               //Asignamos el pin A0 como entrada (LED ROJO)-----> Esto despues sera interpretado como que la temperatura se encuentra muy caliente, enviamos corriente a este pin qye mantendra la valvula abierta para el riego
pinMode(A1,OUTPUT);                               //Asignamos el pin A1 como salida (LED AMARILLO)---->El riego incia de manera suave
pinMode(A2,OUTPUT);                               //Asignamos el pin A2 como salida (Led VERDE)-----> Se mantienen en reposo
pinMode(A3,OUTPUT);                               //Asignamos el pin A3 como salida (Led VIOLETA)---> En este paso en caso de ser
pinMode(A4,OUTPUT);                                //Asignamos el pin A4 como salida (Led AZUL)---->Se notificara al usuario con una series de consejos que podria seguir
pinMode(A5,OUTPUT);

pinMode(A6, OUTPUT);// Dependiendo de las condiciones dadas se vera afectados
pinMode(A7, OUTPUT);
pinMode(A8, OUTPUT);
pinMode(A9, OUTPUT);

pinMode(A10, OUTPUT);                             // LDR  permitira que el prototipo pueda tomar decisiones segun la potencia del sol (despues combinada con el sensor de temperatura permitiendonos conocer un estimado de lo que se podria llegar a ver

Serial.begin (9600);                             //Inicializamos la comunicacion serial a 9600bps


  lcd.begin(16, 2);//iniciamos el lcd
  dht.begin();//iniciamos sensores!!!! 
}
 
void loop() {
  delay(1000);           

  
  byte RH = dht.readHumidity();
  byte Temp = dht.readTemperature();
   Serial.println("");
 Serial.println("AVOcadoHack \n");//Claro el nombre no podria faltar
 Serial.println("");
delay(1000);
  
  digitalWrite(A10,HIGH); 
  
  if (isnan(RH) || isnan(Temp)) {//Esto permite visualizar en el lcd, supongo que esto se ilimiria del prototipado final, 
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Error");
    return;
  }
 if(Temp<=17 ){    
    digitalWrite(A0,LOW);                         //MUY FRIO
    digitalWrite(A1,LOW);                       // 
    digitalWrite(A2,LOW); 
    digitalWrite(A3,LOW); 
    digitalWrite(A4,HIGH); 
    Serial.println("Tomar medidas el sembrio se encuentra en frio");
    delay(1000);
 }
if(Temp>= 19){    
    digitalWrite(A0,LOW);                         
    digitalWrite(A1,LOW);                        //SE ESTA ENFRIANDO
    digitalWrite(A2,LOW); 
    digitalWrite(A3,HIGH); 
    digitalWrite(A4,LOW); 
     Serial.println("Se esta enfriando");
     delay(1000);
 }
 if(Temp>= 21){    
    digitalWrite(A0,LOW);                         
    digitalWrite(A1,LOW);                        //PERFECTO
    digitalWrite(A2,HIGH); 
    digitalWrite(A3,LOW); 
    digitalWrite(A4,LOW); 
    Serial.println("Todo excelente Temperatura");
delay(1000);
 }
 if(Temp>= 24){    
    digitalWrite(A0,LOW);                         
    digitalWrite(A1,HIGH);                        //SE ESTA CALENTANDO
    digitalWrite(A2,LOW); 
    digitalWrite(A3,LOW); 
    digitalWrite(A4,LOW); 
    Serial.println("Sistema de riego de baja potencia");
    delay(1000);
 }
 if(Temp>= 26){    
    digitalWrite(A0,HIGH);                         
    digitalWrite(A1,LOW);                        //MUY CALIENTE
    digitalWrite(A2,LOW); 
    digitalWrite(A3,LOW); 
    digitalWrite(A4,LOW); 
    Serial.println("Sistemas de riego activado");
    delay(1000);
 }

// AQUI EMPIEZA LA PARTE DE LA HUMEDAD

if(RH>=0 ){    
    digitalWrite(A5,HIGH);                         //ESTA MUY SECO
    digitalWrite(A6,LOW);                       
    digitalWrite(A7,LOW); 
    digitalWrite(A8,LOW); 
    digitalWrite(A9,LOW); 
     Serial.println("Sistemas de riego activado");
    delay(1000);
    
 }
if(RH>= 40){    
    digitalWrite(A5,LOW);                         
    digitalWrite(A6,HIGH);                        //SE ESTA SECANDO
    digitalWrite(A7,LOW); 
    digitalWrite(A8,LOW); 
    digitalWrite(A9,LOW); 
    Serial.println("Sistema de riego de baja potencia");
    delay(1000);
 }
 if(RH>= 50){    
    digitalWrite(A5,LOW);                         
    digitalWrite(A6,LOW);                        //PERFECTO
    digitalWrite(A7,HIGH); 
    digitalWrite(A8,LOW); 
    digitalWrite(A9,LOW); 
    Serial.println("Todo exclente Humedad");
    delay(1000);
 }
 if(RH>= 60){    
    digitalWrite(A5,LOW);                         
    digitalWrite(A6,LOW);                        //ESTA MUY HUMEDO
    digitalWrite(A7,LOW); 
    digitalWrite(A8,HIGH); 
    digitalWrite(A9,LOW); 
      Serial.println("Se esta acumulando mucha humedad");
    delay(1000);
 }
 if(RH>= 70){    
    digitalWrite(A5,HIGH);                         
    digitalWrite(A6,LOW);                        //MUY MOJADO
    digitalWrite(A7,LOW); 
    digitalWrite(A8,LOW); 
    digitalWrite(A9,HIGH); 
      Serial.println("Existe demasiada humedad , seguir las recomendaciones de la app");
    delay(1000);
 }
//El codigo de abajo permite saber los resultados de los sensores

  temperature[7]     = Temp / 10 + 48;
  temperature[8]     = Temp % 10 + 48;
  temperature[11]    = 223;
  humidity[7]        = RH / 10 + 48;
  humidity[8]        = RH % 10 + 48;
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print(humidity);

  
}
