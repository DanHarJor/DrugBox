#include <RTClib.h>
#include <Wire.h>

DS1307 rtc;

char buf[20];

void setup (){
	Serial.begin(9600);
#ifndef AVR
	Wire.begin();
#endif
	rtc.begin();

	if (! rtc.isrunning()) {
    		Serial.println("RTC is NOT running, let's set the time!");    
		rtc.adjust(DateTime((__DATE__), (__TIME__)));
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
 	}
}

void prinTime (DateTime time){

    Serial.print(time.year(), DEC);
    Serial.print('/');
    Serial.print(time.month(), DEC);
    Serial.print('/');
    Serial.print(time.day(), DEC);
    Serial.print(" (");
    Serial.print(time.dayOfTheWeek());
    Serial.print(") ");
    Serial.print(time.hour(), DEC);
    Serial.print(':');
    Serial.print(time.minute(), DEC);
    Serial.print(':');
    Serial.print(time.second(), DEC);
    Serial.println();

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(time.unixtime());
}

void loop(){
    DateTime time = rtc.now();
    Serial.println(time.tostr(buf));

    DateTime tom (time + TimeDelta(1 * 86400L + 30));
	    prinTime(tom);
	
	    while(true){}
}


