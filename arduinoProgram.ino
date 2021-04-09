//LCD16x2 sterowany przez I2C Arduino

#include <Wire.h>              // standardowa biblioteka Arduino
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

//LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_I2C lcd(0x3f, 16, 2);

char receivedChar[1];
boolean newData = false;
int cursorX = 0;
int cursorY = 0;
char firstLine[16];
char secondLine[16];
char abc[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int actLetter = 0;
int firstLineHelper[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char haslo[] = "HACK SILBERSPACE";
void setup()
{
    lcd.init();
    lcd.begin(16, 2); // Inicjalizacja LCD 2x16
    Serial.begin(9600);
    lcd.backlight(); // zalaczenie podwietlenia
}
void loop()
{
    bool serialTrue = false;
    if (Serial.available() > 0)
    {
        cursorX = 0;
        char actChar;
        do
        {
            if (Serial.available() > 0)
            {
                lcd.setCursor(cursorX, 0);
                actChar = char(Serial.read());
                lcd.print(actChar);
                lcd.setCursor(0, 1);
                lcd.print("Access denied");
                if (actChar == haslo[cursorX])
                {
                    firstLine[cursorX] = haslo[cursorX];
                    cursorX++;
                    if (cursorX == 16)
                    {
                        lcd.setCursor(0, 1);
                        lcd.print("Access permitted");
                        delay(10000);
                    };
                };
                //if (strcmp(firstLine, haslo) == 0)
                //{
                //    lcd.setCursor(0, 1);
                //    lcd.clear();
                //    lcd.print("Access permitted");
                //    delay(10000);
                //}
            }
        } while (true);
    };
    lcd.setCursor(cursorX, cursorY);
    if (kierunekJoy() == 2)
    {
        cursorX++;
        if (cursorX == 16)
        {
            cursorX = 0;
        }
        actLetter = firstLineHelper[cursorX];
    }

    if (kierunekJoy() == 4)
    {
        cursorX--;
        if (cursorX == -1)
        {
            cursorX = 15;
        }
        actLetter = firstLineHelper[cursorX];
    }

    if (kierunekJoy() == 3)
    {
        actLetter--;
        if (actLetter == -1)
        {
            actLetter = 26;
        }
        firstLineHelper[cursorX] = actLetter;
    }

    if (kierunekJoy() == 1)
    {
        actLetter++;
        if (actLetter == strlen(abc))
        {
            actLetter = 0;
        }
        firstLineHelper[cursorX] = actLetter;
    }
    for (int i = 0; i < 16; i++)
    {
        firstLine[i] = abc[firstLineHelper[i]];
    }
    lcd.setCursor(cursorX, 0);
    lcd.print("_");
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print(firstLine);
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    delay(100);
    if (strcmp(firstLine, haslo) == 0)
    {
        lcd.setCursor(0, 1);
        lcd.print("Access permitted");
        delay(10000);
    }
    //recvOneChar();
    //showNewData();
}

/*
    char abc[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char haslo[] = "KOCHAM CIE OLU";
    for (int j = 0; j < strlen(haslo); j++) {
    byte i = 0;
    do{
      lcd.setCursor(j, 0);
      lcd.print(abc[i]);
      delay(100);
      i++;
    }while(abc[i-1]!=haslo[j]);

    }
    delay(5000);
    lcd.clear();
    delay(5000);
  */

int kierunekJoy()
{
    int kierunek = 0;
    if (analogRead(A2) > 600)
    {
        kierunek = 4;
    }
    if (analogRead(A2) < 400)
    {
        kierunek = 2;
    }
    if (analogRead(A3) > 600)
    {
        kierunek = 3;
    }
    if (analogRead(A3) < 400)
    {
        kierunek = 1;
    }
    return kierunek;
}
void recvOneChar()
{
    if (Serial.available() > 0)
    {
        receivedChar[0] = Serial.read();
        newData = true;
    }
}

void showNewData()
{
    if (newData == true)
    {
        Serial.print("This just in ... ");
        lcd.setCursor(0, 0);
        if (receivedChar[0] == 'T')
        {
            lcd.print("Ziobro ty KURWO");
            lcd.setCursor(0, 1);
            lcd.print("JEBANA");
        }

        delay(5000);
        newData = false;
    }
}