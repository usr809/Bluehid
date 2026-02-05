#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <BleKeyboard.h>
#include <string.h>

#define BTN1 12
#define BTN2 18

int screen = 0;
int menuIndex = 0;
int subIndex  = 0;

Adafruit_SSD1306 disp(128, 64, &Wire, -1);
BleKeyboard bluehid("BUDDY", "Espressif", 100);

void setup()
{
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);

  Wire.begin();
  disp.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  disp.setTextColor(SSD1306_WHITE);
  disp.clearDisplay();
  disp.display();

  Serial.begin(115200);
  bluehid.begin();
}

void logo()
{
  disp.clearDisplay();
  disp.setTextSize(2);
  disp.setCursor(15, 5);
  disp.println("BLUEHID");
  disp.setTextSize(1);
  disp.setCursor(1, 30);
  disp.println("FOR WINDOWS & ANDROID");
  disp.println("Developed by USR");
  disp.setCursor(110, 56);
  disp.print("V1");
  disp.display();
}

void note()
{
  disp.clearDisplay();
  disp.setTextSize(2);
  disp.setCursor(20, 5);
  disp.print("NOTE");
  disp.setTextSize(1);
  disp.setCursor(1, 30);
  disp.print("Educational purpose\nOnly for learning");
  disp.display();
}

void connection()
{
  disp.clearDisplay();
  disp.setTextSize(2);
  disp.setCursor(20, 5);
  disp.print("CONNECT");
  disp.setTextSize(1);
  disp.setCursor(1, 30);
  disp.print("Waiting for BLE...\n\nDevice : BUDDY");
  disp.display();
}

void menu()
{
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setCursor(0, 0);
  disp.print("OPTIONS");

  disp.setCursor(10, 20);
  disp.print(menuIndex == 0 ? "> WINDOWS" : "  WINDOWS");

  disp.setCursor(10, 32);
  disp.print(menuIndex == 1 ? "> ANDROID" : "  ANDROID");

  disp.display();
}

void payloads(const char* title)
{
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setCursor(0, 0);
  disp.print(title);

  disp.setCursor(10, 20);
  disp.print(subIndex == 0 ? "> PAYLOAD1" : "  PAYLOAD1");

  disp.setCursor(10, 32);
  disp.print(subIndex == 1 ? "> PAYLOAD2" : "  PAYLOAD2");

  disp.setCursor(10, 44);
  disp.print(subIndex == 2 ? "> Back" : "  Back");

  disp.display();
}

void win_payload1()
{
  disp.clearDisplay();
  disp.setCursor(10, 30);
  disp.print("WIN PAYLOAD 1");
  disp.display();

  if (bluehid.isConnected())
  {
    bluehid.press(KEY_LEFT_GUI);
    bluehid.press('r');
    delay(100);
    bluehid.releaseAll();
    delay(1000);

    bluehid.print("notepad");
    bluehid.press(KEY_RETURN);
    bluehid.releaseAll();
    delay(1000);

    const char* txt = "HELLO THIS IS A BLUEHID ATTACK PERFORM BY THE ESP32 WHICH IS DEVELOPED BY USR :)";
    for (int i = 0; i < strlen(txt); i++)
    {
      bluehid.print(txt[i]);
      delay(40);
    }
  }
  delay(1000);
  screen = 3;
}

void win_payload2()
{
  disp.clearDisplay();
  disp.setCursor(10, 30);
  disp.print("WIN PAYLOAD 2");
  disp.display();

  if (bluehid.isConnected())
  {
    bluehid.press(KEY_LEFT_GUI);
bluehid.press('r');
delay(100);
bluehid.releaseAll();
delay(1000);
    const char* cmd = "https://www.youtube.com/watch?v=P_c0Aojg0KY&list=RDP_c0Aojg0KY&start_radio=1";
    for (int i = 0; i < strlen(cmd); i++)
    {
      bluehid.print(cmd[i]);
      delay(15);
    }
    bluehid.press(KEY_RETURN);
    bluehid.releaseAll();
  }
  delay(1000);
  screen = 3;
}

void and_payload1()
{
  disp.clearDisplay();
  disp.setCursor(10, 30);
  disp.print("ANDROID PAYLOAD 1");
  disp.display();

  if (bluehid.isConnected())
  {
      bluehid.press(KEY_ESC);
  bluehid.releaseAll();
  delay(100);
  bluehid.press(KEY_LEFT_GUI);
  bluehid.press('d');
  bluehid.releaseAll();
  delay(200);
  bluehid.press(KEY_LEFT_ALT);
  bluehid.press(KEY_ESC);
  bluehid.releaseAll();
  delay(200);
  bluehid.press(KEY_LEFT_GUI);
  bluehid.press('b');
  bluehid.releaseAll();
  delay(700);
  bluehid.press(KEY_LEFT_CTRL);
  bluehid.press(KEY_LEFT_SHIFT);
  bluehid.press('n');
  bluehid.releaseAll();
  delay(700);
  bluehid.press(KEY_LEFT_CTRL);
  bluehid.press('l');
  bluehid.releaseAll();
  delay(300);
  bluehid.print("https://www.youtube.com/watch?v=P_c0Aojg0KY&list=RDP_c0Aojg0KY&start_radio=1");
  delay(300);
  bluehid.press(KEY_RETURN);
  bluehid.releaseAll();
  delay(300);
  }

  delay(1000);
  screen = 3;
}

void and_payload2()
{
  disp.clearDisplay();
  disp.setCursor(10, 30);
  disp.print("ANDROID PAYLOAD 2");
  disp.display();
  if (bluehid.isConnected())
    bluehid.print("HELLO THIS IS A BLUEHID ATTACK PERFORM BY THE ESP32 WHICH IS DEVELOPED BY USR :)");
  delay(1000);
  screen = 3;
}

void waitRelease()
{
  while (digitalRead(BTN1) == LOW || digitalRead(BTN2) == LOW)
    delay(10);
}

void loop()
{
  if (screen == 0)
  {
    logo();
    if (digitalRead(BTN1) == LOW || digitalRead(BTN2) == LOW)
    {
      screen = 1;
      waitRelease();
    }
  }
  else if (screen == 1)
  {
    note();
    if (digitalRead(BTN1) == LOW || digitalRead(BTN2) == LOW)
    {
      screen = 2;
      waitRelease();
    }
  }
  else if (screen == 2)
  {
    connection();
    if (bluehid.isConnected())
    {
      screen = 3;
      delay(300);
    }
  }
  else if (screen == 3)
  {
    menu();
    if (digitalRead(BTN1) == LOW)
    {
      menuIndex = (menuIndex + 1) % 2;
      waitRelease();
    }
    if (digitalRead(BTN2) == LOW)
    {
      subIndex = 0;
      screen = (menuIndex == 0) ? 4 : 5;
      waitRelease();
    }
  }
  else if (screen == 4)
  {
    payloads("WINDOWS");
    if (digitalRead(BTN1) == LOW)
    {
      subIndex = (subIndex + 1) % 3;
      waitRelease();
    }
    if (digitalRead(BTN2) == LOW)
    {
      if (subIndex == 0) win_payload1(); 
      else if (subIndex == 1) win_payload2();
      else screen = 3;
      waitRelease();
    }
  }
  else if (screen == 5)
  {
    payloads("ANDROID");
    if (digitalRead(BTN1) == LOW)
    {
      subIndex = (subIndex + 1) % 3;
      waitRelease();
    }
    if (digitalRead(BTN2) == LOW)
    {
      if (subIndex == 0) and_payload1();  
      else if (subIndex == 1) and_payload2();
      else screen = 3;
      waitRelease();
    }
  }
}
