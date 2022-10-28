#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char letras[] = "SOLARION ";
int i = 0;
int contador;

byte SIMB1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte SIMB2[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000
};
byte SIMB3[8] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000
};

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();

  lcd.createChar(1, SIMB1);
  lcd.createChar(2, SIMB2);
  lcd.createChar(3, SIMB3);
  lcd.clear();

  for (contador = 0; contador < 9; contador++) {
    lcd.setCursor(4 + i, 0);
    lcd.print(letras[i]);
    if (contador % 2 == 0) {
      lcd.setCursor(1, 0);
      lcd.write(2);
      lcd.setCursor(1, 1);
      lcd.write(1);
      lcd.setCursor(14, 1);
      lcd.write(2);
      lcd.setCursor(14, 0);
      lcd.write(1);
    }
    else {
      lcd.setCursor(1, 1);
      lcd.write(2);
      lcd.setCursor(1, 0);
      lcd.write(1);
      lcd.setCursor(14, 0);
      lcd.write(2);
      lcd.setCursor(14, 1);
      lcd.write(1);
    }
    i++;
    delay(500);
  }
  i = 0;
  for (contador = 0; contador < 9; contador++) {
    lcd.setCursor(4 + i, 0);
    lcd.write(1);
    if (contador % 2 == 0) {
      lcd.setCursor(1, 1);
      lcd.write(2);
      lcd.setCursor(1, 0);
      lcd.write(1);
      lcd.setCursor(14, 0);
      lcd.write(2);
      lcd.setCursor(14, 1);
      lcd.write(1);
    }
    else {
      lcd.setCursor(1, 0);
      lcd.write(2);
      lcd.setCursor(1, 1);
      lcd.write(1);
      lcd.setCursor(14, 1);
      lcd.write(2);
      lcd.setCursor(14, 0);
      lcd.write(1);
    }
    i++;
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("AQUECENDO AGUA");
  lcd.setCursor(3, 1);
  lcd.print("PARA VOCE");
  delay(1500);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("PREENCHENDO");
  lcd.setCursor(3, 1);
  lcd.print("O COLETOR");
  delay(1500);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("AGUARDE");
  //  digitalWrite(motor,1)
  for (contador = 0; contador < 10; contador++) {
    if (contador % 2 == 0) {
      lcd.setCursor(1, 0);
      lcd.write(2);
      lcd.setCursor(1, 1);
      lcd.write(1);
      lcd.setCursor(14, 1);
      lcd.write(2);
      lcd.setCursor(14, 0);
      lcd.write(1);
    }
    else {
      lcd.setCursor(1, 1);
      lcd.write(2);
      lcd.setCursor(1, 0);
      lcd.write(1);
      lcd.setCursor(14, 0);
      lcd.write(2);
      lcd.setCursor(14, 1);
      lcd.write(1);
    }
    delay(500);
  }
  // digitalWrite(motor,0);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("PRONTO");
  lcd.setCursor(2, 1);
  lcd.print("PARA AQUECER");
  lcd.setCursor(15, 1);
  lcd.write(3);
  delay(1500);
  lcd.clear();
}

void loop() {
  delay(10);
}
