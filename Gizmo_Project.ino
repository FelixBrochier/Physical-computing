// This is going to be my final gizmo code


// Call all the libraries
#include "IRremote.h"
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Stepper.h>


// Define all the constants
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Define the LCD display

int RECV_PIN = 8; // Signal Pin of IR receiver
IRrecv irrecv(RECV_PIN);
decode_results results;
String IRCode[10] = {"FF6897", "FF30CF", "FF18E7", "FF7A85", "FF10EF", "FF38C7", "FF5AA5", "FF42BD", "FF4AB5", "FF52AD"};
int IRDecode[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Define the IR remote

String CodedRFID[40] = {" 2C 3F A0 FE", " BC 44 A0 FE", " FC 44 A0 FE", " 3C 45 A0 FE",
                        " 6C 3F A0 FE", " 7C 45 A0 FE", " EC 3E A0 FE", " AC 3E A0 FE",
                        " 6C 3E A0 FE", " 2C 3E A0 FE", " EC 3D A0 FE", " AC 47 A0 FE",
                        " BC 3B A0 FE", " FC 3B A0 FE", " 3C 3C A0 FE", " 7C 3C A0 FE",
                        " BC 3C A0 FE", " FC 3C A0 FE", " BC 03 A0 FE", " 7C 0D A0 FE",
                        " 4C 0F A0 FE", " 0C 0F A0 FE", " CC 0E A0 FE", " 8C 0E A0 FE",
                        " 6C 47 A0 FE", " 2C 47 A0 FE", " 4C 0E A0 FE", " 0C 0E A0 FE",
                        " CC 0D A0 FE", " 8C 17 A0 FE", " 6C 26 A0 FE", " 2C 26 A0 FE",
                        " EC 25 A0 FE", " AC 2F A0 FE", " 6C 2F A0 FE", " 2C 2F A0 FE",
                        " EC 2E A0 FE", " AC 2E A0 FE", " 6C 2E A0 FE", " 2C 2E A0 FE"
                       };

int DecodedRFID[40] = {10, 10, 10, 10, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9};

int start;
int Card1;
int Card2;
int InputPlayer1 = 10;
int InputPlayer2 = 10;
String CodeInputPlayer1 = "a"; 
String CodeInputPlayer2 = "a";
String codeInputPlayer1 = "a";
String codeInputPlayer2 = "a";
int i;
String Cont1;
String Cont2;
int First;

#define SS_PIN 53
#define RST_PIN 7
MFRC522 mfrc522(SS_PIN, RST_PIN); // Defines the RFID

const int stepsPerRevolution = 200;

Stepper myStepper(stepsPerRevolution, 26, 27, 28, 29);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16, 2);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  myStepper.setSpeed(100);

}

void loop() {
  start = 0;
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print(" Press Play to");
  lcd.setCursor(0, 1);
  lcd.print("     Start");
  while ( start == 0)
  {
    if (irrecv.decode(&results))
    {
      //      Serial.println(results.value);
      switch (results.value)
      {
        case 0xFF02FD:
          //          Serial.println("Start");
          start = 1;
          break;

      }

    }
  }

  irrecv.resume();

  

  //Explanation of the game to users'
  
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Find the other's");
  lcd.setCursor(0, 1);
  lcd.print("  card to win  ");

  delay(2000);

  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place your bets");
  lcd.setCursor(0, 1);
  lcd.print("   in the safe   ");

  delay(10000);

  //RFID scan here
  //
  //  // Look for new cards
  Serial.println("This line of code is being executed");
  while ( ! mfrc522.PICC_IsNewCardPresent())
  {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Player 1    ");
    lcd.setCursor(0, 1);
    lcd.print("Take your card");
  }

  Serial.println("This line of code is being executed as well");

  // Select one of the cards
  while ( ! mfrc522.PICC_ReadCardSerial())
  {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Player 1    ");
    lcd.setCursor(0, 1);
    lcd.print("Take your card");
  }


  Serial.println("This line of code is being executed too");

  //Show UID on serial monitor
  String content1 = "";
  byte letter1;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    //     Serial.println(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //     Serial.println(mfrc522.uid.uidByte[i], HEX);
    content1.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content1.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Cont1 = String(content1);
  Cont1.toUpperCase();
  Serial.println(Cont1);

  for (i = 0; i < 40; i++)
  {
    if (Cont1 == CodedRFID[i])
    {
      Card1 = DecodedRFID[i];
      Serial.println("It worked");
    }
  }

  Serial.println(Card1);

  //  lcd.setCursor(0,0);
  //  lcd.clear();
  //  lcd.setCursor(0,1);
  //  lcd.clear();
  //  lcd.setCursor(0,0);
  //  lcd.print("    Player 2    ");
  //  lcd.setCursor(0,1);
  //  lcd.print("Take your card");
  //
  //  delay(2000);

  delay(3000);

  while ( ! mfrc522.PICC_IsNewCardPresent())
  {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Player 2    ");
    lcd.setCursor(0, 1);
    lcd.print("Take your card");
  }

  // Select one of the cards
  while ( ! mfrc522.PICC_ReadCardSerial())
  {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Player 2    ");
    lcd.setCursor(0, 1);
    lcd.print("Take your card");
  }

  Serial.println("HAHA");
  //Show UID on serial monitor
  String content2 = "";
  byte letter2;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    //     Serial.println(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //     Serial.println(mfrc522.uid.uidByte[i], HEX);
    content2.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content2.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Cont2 = String(content2);
  Cont2.toUpperCase();
  Serial.println(Cont2);

  for (i = 0; i < 40; i++)
  {
    if (Cont2 == CodedRFID[i])
    {
      Card2 = DecodedRFID[i];
      Serial.println("It worked");
    }
  }

  Serial.println(Card2);

  delay(2000);

  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("First Player is:");

  delay(3000);

  First = random(1, 2);
  Serial.print("The first player to go is player");
  Serial.println(First);

  delay(1000);

  if (First == 1)
  {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Player 1");
    delay(1000);
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Player 2");
    delay(1000);
  }


  while (Card1 != InputPlayer2 && Card2 != InputPlayer1) // Repeat until one fo the players finds the other's card
  {
    CodeInputPlayer1 = "a";
    CodeInputPlayer2 = "a";


    while (CodeInputPlayer1 == "a")
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Input the other");
      lcd.setCursor(0, 1);
      lcd.print(" player's card! ");
      if (irrecv.decode(&results))
      {
        CodeInputPlayer1 = String(results.value, HEX);
        delay(1000);
      }
    }

    irrecv.resume();

    CodeInputPlayer1.toUpperCase();
    codeInputPlayer1 = String(CodeInputPlayer1);
    Serial.println(codeInputPlayer1);

    for (i = 0; i < 11; i ++)
    {
      if (codeInputPlayer1 == IRCode[i])
      {
        InputPlayer1 = IRDecode[i];
      }
    }

    Serial.println();
    Serial.println(InputPlayer1);
    delay(1000);

    if (InputPlayer1 == Card2)
    {
      Serial.println("This player has won the game");
      break;
    }
    else if ( Card2 > InputPlayer1)
    {
      Serial.println("The guy has not won the game yet part1");
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  The card is:  ");
      lcd.setCursor(0, 1);
      lcd.print("     HIGHER     ");
      delay(2000);
    }
    else
    {
      Serial.println("The guy has not won the game yet part2");
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  The card is:  ");
      lcd.setCursor(0, 1);
      lcd.print("     LOWER     ");
      delay(2000);
    }

    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Turn is now to ");
    lcd.setCursor(0, 1);
    delay(2000);

    if (First == 1)
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Player 2");
      delay(1000);
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Player 1");
      delay(1000);
    }
    Serial.println();
    Serial.println();
    Serial.println(CodeInputPlayer2);

    while (CodeInputPlayer2 == "a")
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Input the other");
      lcd.setCursor(0, 1);
      lcd.print(" player's card! ");
      if (irrecv.decode(&results))
      {
        CodeInputPlayer2 = String(results.value, HEX);
        delay(1000);
      }
    }


    irrecv.resume();

    CodeInputPlayer2.toUpperCase();
    codeInputPlayer2 = String(CodeInputPlayer2);
    Serial.println(codeInputPlayer2);

    for (i = 0; i < 11; i ++)
    {
      if (codeInputPlayer2 == IRCode[i])
      {
        InputPlayer2 = IRDecode[i];
      }
    }

    Serial.println();
    Serial.println(InputPlayer2);
    delay(1000);

    if (InputPlayer2 == Card1)
    {
      Serial.println("This player has won the game");
      break;
    }
    else if ( Card1 > InputPlayer2)
    {
      Serial.println("The guy has not won the game yet part1");
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  The card is:  ");
      lcd.setCursor(0, 1);
      lcd.print("     HIGHER     ");
      delay(2000);
    }
    else
    {
      Serial.println("The guy has not won the game yet part2");
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  The card is:  ");
      lcd.setCursor(0, 1);
      lcd.print("     LOWER     ");
      delay(2000);
    }

    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Turn is now to ");
    lcd.setCursor(0, 1);
    delay(2000);

    if (First == 1)
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Player 1");
      delay(1000);
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Player 2");
      delay(1000);
    }

    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Guess the other");
    lcd.setCursor(0, 1);
    lcd.print(" player's card! ");
    delay(2000);

    Serial.println();
    Serial.println("We're getting there :)))))))))))) ");


  }


  Serial.println("YOU ARE THE BIG WINNER");

  if (Card1 == InputPlayer2)
  {
    if (First == 1)
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Player 2");
      lcd.setCursor(0, 1);
      lcd.print("     WINS!!     ");
      delay(2000);

    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Player 1");
      lcd.setCursor(0, 1);
      lcd.print("     WINS!!     ");
      delay(2000);
    }

      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The card was:");
      lcd.setCursor(0,1);
      lcd.print(Card1);
      delay(2000);
    
  }
  else
  {
    if (First == 1)
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Player 1");
      lcd.setCursor(0, 1);
      lcd.print("     WINS!!     ");
      delay(2000);
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Player 2");
      lcd.setCursor(0, 1);
      lcd.print("     WINS!!     ");
      delay(2000);
    }

      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The card was:");
      lcd.setCursor(0,1);
      lcd.print(Card2);
      delay(2000);
  }

  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The password is:");
  lcd.setCursor(0,1);
  lcd.print("     0317 :)");
  delay(4000);

  

  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.clear();











}
