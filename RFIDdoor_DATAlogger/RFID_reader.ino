#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#define RST_PIN 5
#define SS_PIN 10
#define LED 7
byte readCard[4];
String My_ID = "804FBA26";  
String ID = "";
String data_log_sent;

MFRC522 mfrc522(SS_PIN, RST_PIN);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);
Servo myservo1;
void setup() 
{Serial.begin(9600);
   myservo1.attach(3);
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("Scan Your Card...");
  display.display();
}

void loop() 
{
  while (getID()) 
  {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    digitalWrite(LED, HIGH); 
    data_log_sent = ID;
    Serial.println(data_log_sent);
    delay(400);
     
    if (ID == My_ID) 
    {
      
     display.print("ACCESS GRANTED!");
     delay(200);
  
     myservo1.write(0);  
     delay(1200);
     myservo1.write(90); 
     digitalWrite(LED, LOW); 
    }
    else
    {
      display.print("ACCESS DENIED!");
      delay(700);
           digitalWrite(LED, LOW); 
    }
    
      display.display();
      display.setCursor(0, 10);
      display.print(" ID : ");
      display.print(ID);
      display.display();
      
    delay(2000);

    display.clearDisplay();
    //display.print(" Access Control ");
    display.setCursor(0, 10);
    display.print("Scan Your Card...");
    display.display();
  }
}

boolean getID() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) { 
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { 
  return false;
  }
  ID = "";
  for ( uint8_t i = 0; i < 4; i++) { 
  //readCard[i] = mfrc522.uid.uidByte[i];
  ID.concat(String(mfrc522.uid.uidByte[i], HEX)); 
  }
  ID.toUpperCase();
  mfrc522.PICC_HaltA(); 
  return true;
}
