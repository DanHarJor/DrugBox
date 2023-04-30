#include <Hstepper.h>
void setup() {
	Serial.begin(9600);
}

Hstepper step;
void loop() {
step.turn(360.0/42.0,0);
	while (true){}
}
