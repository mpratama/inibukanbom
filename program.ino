/*
repo https://github.com/mpratama/inibukanbom
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

const int pB = 2; //trigger menu kepuasan pelayanan
const int pBy = 7;// tombol ya
const int pBn = 4;// tombol tidak
const int pCk = 8;// tombol pengecekan
int pt;

uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t check[8] = {0x0, 0x1 ,0x3, 0x16, 0x1c, 0x8, 0x0};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
uint8_t retarrow[8] = {  0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{
  pinMode(pB, INPUT);
  digitalWrite(pB, HIGH);
  digitalWrite(pBy, HIGH);
  digitalWrite(pBn, HIGH);
  digitalWrite(pCk, HIGH);
  lcd.begin();
  lcd.backlight();

  lcd.createChar(0, bell);
  lcd.createChar(1, note);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);
  lcd.home();
}

void loop()
{
  int puas = EEPROM.get(0, pt);
  int puas_1 = puas + 1;
  int tidak_puas = EEPROM.get(1, pt);
  int tidak_puas_1 = tidak_puas + 1;
  int marker = 0;
  int state = 0;
  int state2 = 0;
  lcd.cursor();

  while (1) {
    if (marker == 0) {
      lcd.clear();
      lcd.write(3);
      lcd.print("Selamat Datang");
      //lcd.write(3);
      lcd.setCursor(0, 1);
      lcd.print("Di Aptk Tayando");
      lcd.blink();
      delay(2000);
      marker += 1;
    } else if (marker == 1) {
      lcd.clear();
      lcd.write(4);
      lcd.print(" Simpan Resep ");
      //lcd.write(4);
      lcd.setCursor(0, 1);
      lcd.write(7);
      lcd.print(" Disini");
      lcd.blink();
      delay(2000);
      marker += 1;
    } else if(marker == 2) {
      lcd.clear();
      lcd.write(2);
      lcd.print(" Mohon Tunggu ");
      lcd.write(2);
      lcd.setCursor(0, 1);
      lcd.print("Terima Kasih");
      lcd.blink();
      delay(2000);
      marker = 0;
      }

      if (state == 1){
        lcd.clear();
        lcd.print("Pelayanan Oke?");
        lcd.setCursor(0,1);
        lcd.print("Biru=YA ");
        lcd.print("Mrh=TDK");
        if(digitalRead(pBy) == LOW){
          state = 1 - state;
          tone(11, 850, 500);
          EEPROM.put(0, puas_1);
          }
          else if(digitalRead(pBn) == LOW){
            state = 1 - state;
            tone(11, 800, 500);
            EEPROM.put(1, tidak_puas_1);
            }
        }

      if (state2 == 1){
        lcd.clear();
        lcd.print("Puas: ");
        lcd.print(puas);
        lcd.setCursor(0,1);
        lcd.print("Krg puas: ");
        lcd.print(tidak_puas);
        }

      if (digitalRead(pB) == LOW){
        state = 1 - state;
        tone(11, 890, 500);
        }

      if (digitalRead(pCk) == LOW){
        state2 = 1 - state2;
        tone(11, 820, 500);
        }
    delay(1000);
  }
}

