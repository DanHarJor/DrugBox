

void A (int d){
	PORTD = PORTD | 0b01000000;
	delay(d);
	PORTD = PORTD & ~0b01000000;

}
void B (int d){
	PORTD = PORTD | 0b10000000;
	delay(d);
	PORTD = PORTD & ~0b10000000;

}
void C (int d){
	PORTB = PORTB | 0b00000001;
	delay(d);
	PORTB = PORTB & ~0b00000001;
}
void D (int d){
	PORTB = PORTB | 0b00000010;
	delay(d);
	PORTB = PORTB & ~0b00000010;
}
void setupStepper() {
	DDRD = DDRD | 0b11000000;//sets pins 6 and 7 as outputs, ignoring others.
	DDRB = DDRB | 0b00000011;//sets pins 8 and 9 and outputs, ignoring the others.
	PORTD = PORTD & ~0b11000000;//sets pins 6 and 7 LOW, ignoring othrs
	PORTB = PORTB & ~0b00000011;//sets pins 8 and 9 LOW ignoring others. 	
      	// put your setup code here, to run once:
	Serial.begin(9600);
}


int d = 4;//delay between steps, changes motor speed
// delay is needed for inner motor to have time to turn towards newly magnetised parts.

void turn (double degW, bool dir){

//find the multiple of 0.46875 closest to degW, new angle guarenteed to be within 0.5 deg of origional
//int NdegW = round(degW/0.46875)*0.46875;
// 2048 steps in the motor for full turn
//42 teeth in the worm drive
// to move the gear 1 tooth along takes a 360 turn of the motor
// 360 degM = 2048 step = 1 tooth = 360/42 degW
//(2048*42)/360 step = (42/360) tooth = 1degW 
// 1 step = (360/42)/2048 degW
// 42 teeth = 360 degW

double stp = degW * ((2048.0*42.0)/360.0);//number of steps to achieve angle of rotation
//stp is an integer if degW is a multiple of 0.46875
  while(stp>=1){
    //One run of either A,B,C or D is one step
    //There are 2048 steps in total around the motor(I think)
    if(stp>=1){
      //dir = 1 means CWSE clock wise shaft end. With shaft pointing towards you.
      if (dir == 1) A(d); 
      if (dir == 0) D(d);
      stp--;
    }
    
     if(stp>=1){
      if (dir == 1) B(d);
      if (dir == 0) C(d);
      stp--;
     }
     
    
    if(stp>=1){
      if (dir == 1) C(d);
      if (dir == 0) B(d);
      stp--;
    }
     
    if(stp>=1){
      if (dir == 1) D(d);
      if (dir == 0) A(d);
      stp--;
    }
  }
}


