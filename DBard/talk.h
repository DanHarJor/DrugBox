
#ifndef talk_h
#define talk_h
#include "Arduino.h"
#include "RTClib.h"
int chLen(char ch[]);
boolean qck (char c1[], char c2[]);
void listen (char q[], char d[]);
char read();
long intinar (char ar[], int dex1, int dex2);
void conTime (DateTime openT[],char config[]);
int dolla (char ar[], int card);

#endif
