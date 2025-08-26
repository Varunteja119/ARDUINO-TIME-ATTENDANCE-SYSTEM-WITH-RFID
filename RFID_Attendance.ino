#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

byte card_ID[4]; 
byte Name1[4] = {0xDB, 0x6E, 0xF6, 0x03}; 
byte Name2[4] = {0x4E, 0x4B, 0xCB, 0x01}; 

int const RedLed   = 6;
int const GreenLed = 5;
int const Buzzer   = 8;

String Name = ""; 
String entryTime[3] = {"", "", ""}; 
String exitTime[3]  = {"", "", ""}; 

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("CLEARSHEET");
  Serial.println("LABEL,Date,Time,Name,Entry Time,Exit Time");
  Serial.println("Serial Communication Started");

  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  digitalWrite(RedLed, LOW);
  digitalWrite(GreenLed, LOW);
  digitalWrite(Buzzer, LOW);
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Scanned UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  for (byte i = 0; i < 4; i++) {
    card_ID[i] = mfrc522.uid.uidByte[i];
  }

  int cardIndex = -1;
  if (memcmp(card_ID, Name1, 4) == 0) {
    Name = "22BDS0415 - VARUN TEJA MADDIRALA";
    cardIndex = 0;
  } else if (memcmp(card_ID, Name2, 4) == 0) {
    Name = "22BCE3798 - MANASH KUMAR NEPAL";
    cardIndex = 1;
  } 

  if (cardIndex != -1) {
    String currentTime = "TIME";

    if (entryTime[cardIndex] == "") {
      entryTime[cardIndex] = currentTime;
      exitTime[cardIndex]  = "";
      Serial.print("DATA,DATE,TIME,");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(entryTime[cardIndex]);
      Serial.println(",");
    } 
    else if (exitTime[cardIndex] == "") {
      exitTime[cardIndex] = currentTime;
      Serial.print("DATA,DATE,TIME,");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(entryTime[cardIndex]);
      Serial.print(",");
      Serial.println(exitTime[cardIndex]);
    } 
    else {
      entryTime[cardIndex] = currentTime;
      exitTime[cardIndex]  = "";
      Serial.print("DATA,DATE,TIME,");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(entryTime[cardIndex]);
      Serial.println(",");
    }

    digitalWrite(GreenLed, HIGH);
    digitalWrite(RedLed, LOW);
    digitalWrite(Buzzer, LOW);
    delay(1000);
  } 
  else {
    Serial.println("DATA,DATE,TIME,Unknown Card,,");
    digitalWrite(GreenLed, LOW);
    digitalWrite(RedLed, HIGH);
    digitalWrite(Buzzer, HIGH);
    delay(1000);
    digitalWrite(Buzzer, LOW);
  }

  digitalWrite(GreenLed, LOW);
  digitalWrite(RedLed, LOW);

  delay(2000);
}
