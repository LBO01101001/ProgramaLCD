//INCLUSÃO DE BIBLIOTECA
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//DEFINIÇÃO DOS PINOS DIGITAIS
#define rele1 26
#define rele2 32
#define nivel1 5
#define nivel2 19
#define sensorPin 4

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Defina o endereço do lcd
OneWire ourWire(sensorPin);                                     //CONFIGURA UMA INSTÂNCIA ONEWIRE PARA SE COMUNICAR COM O SENSOR
DallasTemperature sensor(&ourWire);                             //BIBLIOTECA DallasTemperature UTILIZA A OneWire

float tempC[0];               //Variaveis com endereço dos sensores
char letras[] = "SOLARION ";  //Salvando cada letra da palavra com endereço
int a;                        //Contador
bool logico;                  //Nível lógico de acionamento

//Símbolo para apagar
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
//Símbolo da gota
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
//Símbolo da carinha feliz
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
//Símbolo da carinha triste
byte SIMB4[8] = {
  B00000,
  B00000,
  B01010,
  B01010,
  B00000,
  B01110,
  B10001,
  B00000
};

void setup() {
  sensor.begin();  //Inicialdo os sensores

  //CONFIGURAÇÃO DOS PINOS
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(nivel1, INPUT_PULLUP);
  pinMode(nivel2, INPUT_PULLUP);

  // INICIALIZAÇÃO DO lcd
  lcd.begin(16, 2);
  lcd.backlight();

  //Númerando cada símbolo
  lcd.createChar(1, SIMB1);
  lcd.createChar(2, SIMB2);
  lcd.createChar(3, SIMB3);
  lcd.createChar(4, SIMB4);

  lcd.clear();  //limpar o lcd

  //Gif
  for (a = 0; a < 9; a++) {
    lcd.setCursor(4 + a, 0);
    lcd.print(letras[a]);
    if (a % 2 == 0) {
      gif1();
    } else {
      gif2();
    }
    delay(500);
  }
  for (a = 0; a < 9; a++) {
    lcd.setCursor(4 + a, 0);
    lcd.write(1);
    if (a % 2 == 0) {
      gif2();
    } else {
      gif1();
    }
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("AQUECENDO AGUA");
  lcd.setCursor(3, 1);
  lcd.print("PARA VOCE");
  delay(1500);
  if (!digitalRead(nivel2) && digitalRead(nivel1)) sem();
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("PREENCHENDO");
  lcd.setCursor(3, 1);
  lcd.print("O COLETOR");
  delay(1500);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("AGUARDE");
  if (digitalRead(nivel1)) {
    digitalWrite(rele2, 1);
  } else {
    digitalWrite(rele1, 1);
  }
  for (a = 0; a < 10; a++) {
    if (a % 2 == 0) {
      gif1();
    } else {
      gif2();
    }
    delay(500);
  }
  digitalWrite(rele1, 0);
  digitalWrite(rele2, 0);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("PRONTO");
  lcd.setCursor(2, 1);
  lcd.print("PARA AQUECER");
  lcd.setCursor(0, 1);
  lcd.write(3);
  lcd.setCursor(15, 1);
  lcd.write(3);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("COLETOR: ");
  lcd.setCursor(0, 1);
  lcd.print("BOILER : ");
}
void loop() {
  sensor.requestTemperatures();  //SOLICITA QUE A FUNÇÃO INFORME A TEMPERATURA DO SENSOR
  // faz leituras de todos sensores
  for (int i = 0; i < 2; i++) {
    tempC[i + 1] = sensor.getTempCByIndex(i);
  }
  // Mostra a temperatura dos sensores
  lcd.setCursor(9, 0);
  lcd.print(tempC[1]);
  lcd.println("C ");
  lcd.setCursor(9, 1);
  lcd.print(tempC[2]);
  lcd.println("C ");

  //verifica se tem água para aquecer
  if (!digitalRead(nivel2) && digitalRead(nivel1)) sem();

  //verifica o nivel do boiler e ligar os reles, se o nível lógico estive alto
  if (digitalRead(nivel1)) {
    digitalWrite(rele2, logico);
    digitalWrite(rele1, 0);
  } else {
    digitalWrite(rele1, logico);
    digitalWrite(rele2, 0);
  }
  //Verifica a temperatura e aciona os reles
  if (tempC[2] < 45 || digitalRead(nivel1)) {
    if (tempC[1] >= 45) {
      logico = 1;
    } else {
      logico = 0;
    }
  } else if (tempC[1] >= 50 && tempC[2] >= 45) {
    logico = 1;
  } else {
    logico = 0;
  }
  delay(1000);
}

//Mensagem de que esta sem água para aquecer
void sem() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("SEM AGUA");
  lcd.setCursor(2, 1);
  lcd.print("PARA AQUECER");
  lcd.setCursor(0, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  digitalWrite(rele1, 0);
  digitalWrite(rele2, 0);
  while (!digitalRead(nivel2) && digitalRead(nivel1));
  if (a > 9) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("COLETOR: ");
    lcd.setCursor(0, 1);
    lcd.print("BOILER : ");
  }
}
void gif1() {
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(1, 1);
  lcd.write(1);
  lcd.setCursor(14, 1);
  lcd.write(2);
  lcd.setCursor(14, 0);
  lcd.write(1);
}
void gif2() {
  lcd.setCursor(1, 1);
  lcd.write(2);
  lcd.setCursor(1, 0);
  lcd.write(1);
  lcd.setCursor(14, 0);
  lcd.write(2);
  lcd.setCursor(14, 1);
  lcd.write(1);
}