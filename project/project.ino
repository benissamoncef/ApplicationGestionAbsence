#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <string.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  
  Serial.begin(9600);   // Initiate a serial communication
  lcd.init();
  lcd.backlight();
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop() {

  lcd.clear();

   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  Serial.println(content);
   

  delay(500);
  String response = "";

  if(Serial.available()){
    while (Serial.available()){    
      char c = Serial.read();
      if (c != '\n'){
        response += c;
      }
      else{
       break;
      }
    }
  } 
  lcd.setCursor(0, 0);
  lcd.print(response);
  Serial.flush(); // Clear the serial buffer
  delay(1000);


}