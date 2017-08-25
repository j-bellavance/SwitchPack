#include <SwitchPack.h>
Debounce debounce;

void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  byte status = debounce.pin(2);
  digitalWrite(13, !status);
}
