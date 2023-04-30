//the clock testing file


#include <RTClib.h>

RTC_DS1307 rtc;

void setup () {
  Serial.begin(57600);
 if (! rtc.begin()) {
   Serial.println("Couldn't find RTC");
   Serial.flush();
   abort();
 }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // the following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void printd(DateTime p){

    Serial.print(p.year(), DEC);
    Serial.print('/');
    Serial.print(p.month(), DEC);
    Serial.print('/');
    Serial.print(p.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[p.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(p.hour(), DEC);
    Serial.print(':');
    Serial.print(p.minute(), DEC);
    Serial.print(':');
    Serial.print(p.second(),DEC);
    Serial.println();

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(p.unixtime());
    Serial.print("s = ");
    Serial.print(p.unixtime() / 86400L);
    Serial.println("d");
}
void loop () {
	DateTime now = rtc.now();
	DateTime tom (now + TimeSpan(1,0,0,0)); 
	printd(tom);
	if (tom > now){Serial.println("yes");}

	delay(2000);
} 
