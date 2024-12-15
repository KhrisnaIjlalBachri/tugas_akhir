#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD 20x4 dengan alamat I2C (biasanya 0x27 atau 0x3F)
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int BTN_UP = 33;
const int BTN_DOWN = 25;
const int BTN_ENTER = 32;
const int BTN_BACK = 27;

enum ButtonState 
{
  BTN_DEFAULT,
  BTN_UP_STATE,
  BTN_DOWN_STATE,
  BTN_ENTER_STATE,
  BTN_BACK_STATE
};
ButtonState buttonState = BTN_DEFAULT;

//menu
enum WeightState 
{
  WEIGHT_0,
  WEIGHT_500,
  WEIGHT_1000,
  WEIGHT_1500,
  WEIGHT_2000,
  WEIGHT_2500
};
WeightState weightState = WEIGHT_0;

enum ScreenState 
{
  SCREEN_HOME,
  SCREEN_SCAN,
  SCREEN_CONFIRM,
  SCREEN_WEIGHT
};
ScreenState screenState = SCREEN_HOME;

bool isRegistered = false;

void setup() 
{
  Serial.begin(115200);
  lcd.init();       
  lcd.backlight();  

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_ENTER, INPUT_PULLUP);
  pinMode(BTN_BACK, INPUT_PULLUP);
}

void loop() {
  readButton();
  updateScreen();
}

void readButton() {
  if (!digitalRead(BTN_UP)) 
  {
    delay(20);
    while (!digitalRead(BTN_UP)) ;
    buttonState = BTN_UP_STATE;
  } else if (!digitalRead(BTN_DOWN)) 
  {
    delay(20);
    while (!digitalRead(BTN_DOWN)) ;
    buttonState = BTN_DOWN_STATE;
  } else if (!digitalRead(BTN_ENTER)) 
  {
    delay(20);
    while (!digitalRead(BTN_ENTER)) ;
    buttonState = BTN_ENTER_STATE;
  } else if (!digitalRead(BTN_BACK)) 
  {
    delay(20);
    while (!digitalRead(BTN_BACK)) ;
    buttonState = BTN_BACK_STATE;
  } else 
  {
    buttonState = BTN_DEFAULT;
  }
}

void updateScreen() 
{
  switch (screenState) 
  {
    case SCREEN_HOME:
      lcd.setCursor(0, 0);
      lcd.print("Silahkan Tap KTP    ");
      if (buttonState == BTN_ENTER_STATE) 
      {
        screenState = SCREEN_CONFIRM;
        buttonState = BTN_DEFAULT;
      }
      break;

    // case SCREEN_SCAN:
    //   lcd.clear();
    //   lcd.setCursor(0, 0);
    //   lcd.print("KTP: ");
    //   if (isRegistered) 
    //   {
    //     lcd.print("Terdaftar");
    //   } else {
    //     lcd.print("Tidak Terdaftar");
    //   }
    //   if (buttonState == BTN_ENTER_STATE)
    //   {
    //     screenState = SCREEN_CONFIRM;
    //     buttonState = BTN_DEFAULT;
    //   }
    //   break;

    case SCREEN_CONFIRM:
      
      lcd.setCursor(0, 0);
      lcd.print("Ambil beras?        ");
      lcd.setCursor(0, 1);
      lcd.print(weightState == WEIGHT_500 ? "> Iya               " : "  Iya              ");
      lcd.setCursor(0, 2);
      lcd.print(weightState == WEIGHT_1000 ? "> Tidak            " : "  Tidak            ");
      if (buttonState == BTN_UP_STATE || buttonState == BTN_DOWN_STATE) 
      {
        weightState = (weightState == WEIGHT_500) ? WEIGHT_1000 : WEIGHT_500;
        buttonState = BTN_DEFAULT;
      }

      if (buttonState == BTN_ENTER_STATE) 
      {
        screenState = (weightState == WEIGHT_500) ? SCREEN_WEIGHT : SCREEN_HOME;
        buttonState = BTN_DEFAULT;
      }
      break;

    case SCREEN_WEIGHT:
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pilih berat beras:  ");
      lcd.setCursor(0, 1);
      lcd.print(weightState == WEIGHT_500 ? "> 500 gram" : "  500 gram");
      lcd.setCursor(0, 2);
      lcd.print(weightState == WEIGHT_1000 ? "> 1000 gram" : "  1000 gram");
      lcd.setCursor(0, 3);
      lcd.print(weightState == WEIGHT_1500 ? "> 1500 gram" : "  1500 gram");
      
      if (buttonState == BTN_UP_STATE) 
      {
        if (weightState > WEIGHT_500) weightState = (WeightState)(weightState - 1);
        buttonState = BTN_DEFAULT;
      }

      if (buttonState == BTN_DOWN_STATE) 
      {
        if (weightState < WEIGHT_2500) weightState = (WeightState)(weightState + 1);
        buttonState = BTN_DEFAULT;
      }

      if (buttonState == BTN_ENTER_STATE) 
      {
        // lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Berat dipilih:   ");
        lcd.setCursor(0, 2);
        lcd.print((weightState + 1) * 500);
        lcd.print(" gram");
        lcd.clear();
        delay(500);
        screenState = SCREEN_HOME;
        buttonState = BTN_DEFAULT;
      }
      break;
  }
}
