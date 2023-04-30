#include "RTClib.h"
RTC_DS1307 rtc;
void setup(){
	Serial.begin(57600);
//	rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}
long nowish = 1598372194;
void loop(){
	Serial.println("hello t");
	DateTime now = rtc.now();
	DateTime tomorrow = now + TimeSpan(1);
	tomorrow = DateTime(nowish);
	delay(1000);

}
