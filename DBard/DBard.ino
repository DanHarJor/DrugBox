#include "Hstepper.h"
#include "RTClib.h"
#include "talk.h"
DateTime DTnul (2160,1,1,0,0,0);
bool configcorrect;
bool full = false;//full = false in real thing
byte p13 = 0b00100000;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

RTC_DS1307 rtc;
void setup() {
	rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // put your setup code here, to run once:
	DDRB = DDRB | p13; //makes pin 13 output
	PORTB = PORTB & ~p13; //sets pin 13 to low
	Serial.begin(57600);
	HstepSetup();
	 if (! rtc.begin()) {
	   Serial.println("Couldn't find RTC");
	   Serial.flush();
	 }
	 if (! rtc.isrunning()) {
  	  Serial.println("RTC is NOT running, let's set the time!");
    	  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  	 }
	 assignQues();
	 configcorrect = false;
}
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

void blink(int t){
	int i = 0;
	while(i < t){
		PORTB = PORTB | p13; //sets pin 13 to high
		delay(200);
		PORTB = PORTB && ~p13; //sets pin 13 to low
		delay(200);
		i = i+1;
	}
}



class recData {
	public:
		//need to try and use this to fill data, see nots in talk.cpp
		void listen ();//function declaration
//a que insuring recieved data matches the data listened for
		char que;
		char data[20];// a char array of recieved charecters
		DateTime datetime = DTnul;//the DateTime recieved 
		bool qheard = false;//0 if q not recieved, 1 if q recieved
		bool heard = false;//0 if data not recieved, 1 if data recieved
		String dataS;
		long dataL;
		bool turned = false;
		void mt(){
			memset(data, 0, sizeof(data));
			datetime = DTnul;
			qheard = false;
			heard = false;
			dataS = "";
			dataL = 0;
			turned = false;
		}		
		void lival(){
		//listen and vilidate data
			if (qheard==false){
			  listen();//sets qheard true if q's match
        		  convert();//convert data string to datetime
			  if (qheard==true){
			    Serial.print(dataS); Serial.print("$");
			//send the string back for confirmation
			  }
			}
		}
		void convert(){//convert long to datetime
			dataL = dataS.toInt();//convert string to long
			datetime = DateTime(dataL);
			//recieved
		}
};
		recData start; 
		recData Now; 
		recData Done; 
		recData Dtwo; 
		recData Dthree; 
		recData Dfour; 
		recData Dfive; 
		recData Dsix; 
		recData correct;
		recData sigh20;//signal for heard to be set to 0 
		recData refill;
		recData test;
void assignQues() {
		Now.que = 'n';
		start.que ='s';
		Done.que = 'a';
		Dtwo.que = 'b';
		Dthree.que = 'c';
		Dfour.que = 'd';
		Dfive.que = 'e';
		Dsix.que = 'f';
		sigh20.que = 'i';
		correct.que = 't';
		refill.que = 'r';
}

void lisigh20(){//set qheard to 0 for config data
	sigh20.mt();
	sigh20.listen();
	if (sigh20.dataS == "reset"){

	Now.mt();start.mt();Done.mt();Dtwo.mt();
	Dthree.mt();Dfour.mt();Dfive.mt();Dsix.mt();

	correct.mt();
	
	configcorrect = false;
	}
sigh20.mt();
}

void lival(){
   if(Serial.available()>0){
	//listen and validate needed data
	Now.lival();
	start.lival();
	Done.lival();
	Dtwo.lival();
	Dthree.lival();
	Dfour.lival();
	Dfive.lival();
	Dsix.lival();//listens and sends back data if q's match
	correct.listen();//just listens, doesnt send back data for validation. 
	if (correct.dataS == "correct"){
		configcorrect = true;
		rtc.adjust(Now.datetime);
	}
   }
}

void dispense() {
  while (configcorrect == true && alltur() == false && full == true){	
	disrefi();	

	if (rtc.now() > start.datetime && start.turned == false)
  		{turn(2,1);start.turned = true;}
  	if (rtc.now() > Done.datetime && Done.turned == false)
  		{turn(2,1);Done.turned = true;}
  	if (rtc.now() > Dtwo.datetime && Dtwo.turned == false)
  		{turn(2,1);Dtwo.turned = true;}
  	if (rtc.now() > Dthree.datetime && Dthree.turned == false)
  		{turn(2,1);Dthree.turned = true;}
  	if (rtc.now() > Dfour.datetime && Dfour.turned == false)
  		{turn(2,1);Dfour.turned = true;}
  	if (rtc.now() > Dfive.datetime && Dfive.turned == false)
  		{turn(2,1);Dfive.turned = true;}
  	if (rtc.now() > Dsix.datetime && Dsix.turned == false)
  		{turn(2,1);Dsix.turned = true; full = false;}
  }
}
//method for if refill button is pushed while dispensing
void disrefi(){
  refill.mt();
  refill.listen();

  if (refill.dataS == "refill"){
	Serial.print("noem$");
  }
}
void refi() {
  refill.mt();
  refill.listen();
  if (refill.dataS == "refill"){
     	if (full == true){Serial.print("noem$");}
  	else if (full == false){
  		Serial.print("em$");
  		turn(2,1);
  		refill.mt();
  		while (refill.dataS!="done"){
  		 while(refill.qheard == false){refill.listen();}
		 
  		 if (refill.dataS == "next"){turn(2,1);refill.mt();}
		 else if(refill.dataS == "back")
			{turn(2,0);refill.mt();} 
  		}
		full = true;
  	}
  }
}
void loop() {
lisigh20();//listen for the reset signal. Sent when configure drig box button is pushed. 
lival();//listen for the data and validate with relay. 

dispense();//turn the motor at the times previously listened for.

refi();

//after the last datetime has passed, press button refill procedure
}

void recData :: listen (){
  if (Serial.available() > 0){
      char qre  = '0';
      int t = 0;
      int f = 0;
      int i = 0;
    //check the que is for the right variable
    while (Serial.available() == 0 && t<500) {delay(1); t++;}
      if (t < 500){
        qre = Serial.peek();
      }
    if (que == qre){
	Serial.read();//takes the q out of the serial
        qheard=true;//variable to show the data was heard
        while (f == 0){
          t=0;
          char r = read();
          if (r == '$') {f = 1;}
          else {data[i] = r; i++;}
        }
	dataS = String(data);//convert char array to string
     }
  }
}

boolean alltur(){
	boolean at = start.turned * Done.turned * Dtwo.turned * Dthree.turned * Dfour.turned * Dfive.turned * Dsix.turned;
	return at;		
}


void serMT(){
	while (Serial.available() > 0){Serial.read();}
}
