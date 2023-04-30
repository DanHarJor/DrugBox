

#include "talk.h"
#include "Arduino.h"
#include "RTClib.h"
//A method to output the length of a char array 
int chLen(char ch[]){
  int count = 0;
  while (ch[count] != '\0'){
    count ++;
  }
  return count;
}

//A method to check that 2 char arrays are the same
//outputs true if the same and false if different
bool qck (char c1[], char c2[]){
bool ans = 0;
  int count = 0;
  int mag = chLen(c1);
    for (int i = 0; i < mag; i++){
      if (c1[i] == c2[i]) count++;
    }
    if (count == mag) ans = 1;
  
  return ans;
}

//this method will fill up the char array given to it d[] with 
// an incoming serial transmission, only if the que q[] given
// to this method matches the que in the transmission
//if no serial is available the method will be skipped
//
//trying to include listen into the class recDate, ****not sure how to transfer the classes variables into the method**** maybe its just as if it was typed into the class itself.do tests
//void recDate :: listen (){
//  if (Serial.available() > 0){
//    
//      char qre [3] = {0, 0, '\0'};
//      int t = 0;
//      int f = 0;
//      int i = 0;
//    //check the que is for the right variable
//    for (int j = 0; j < 2; j++){//strlen seems to add an extra one onto the actual length, thus -1
//          while (Serial.available() == 0 && t<500) {delay(1); t++;}
//            if (t < 500){
//              char re = Serial.read();
//              qre[j] = re;
//            }
//    }
//    if (qck(que,qre)){
//        while (f == 0){
//          t=0;
//          char r = read();
//          if (r == '$') {f = 1;}
//          else {data[i] = r; i++;}
//        }
//     }
//  }
//}

char read(){
  int t = 0;
  while (Serial.available() == 0 && t<500) {delay(1); t++;}
  char r = Serial.read();
  return r;
}

//this function will take a char array ar and ouput an integer corosponding to the characters between indexes dex1 and dex2. 
long intinar (char ar[], int dex1, int dex2){
	String out = "";
	for (int i = 0; i < (dex2-dex1); i++){
		out += ar[dex1+i]; 
	}
	return out.toInt();
}

//find i'th $ position in a char array 
int dolla (char ar[], int card){
	for (int i; i<chLen(ar);i++){
		if (ar[i] == '$'){card--;}
		if (card == 0){return i;}
	}
}
