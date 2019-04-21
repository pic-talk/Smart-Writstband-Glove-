#include <SoftwareSerial.h>

#define MOTOR1 4
#define MOTOR2 5
#define MOTOR3 6
#define MOTOR4 7
#define MOTOR5 8
#define MOTOR6 9

SoftwareSerial bt(3,2);

int commacount = 5;
int* numbers = (int*) malloc(commacount * sizeof(int));
String dataSend;

char* subStr (char* str, char *delim, int index) {
  char *act, *sub, *ptr;
  static char copy[100];
  int i;
  strcpy(copy, str);
  for (i = 1, act = copy; i <= index; i++, act = NULL) {
     sub = strtok_r(act, delim, &ptr);
     if (sub == NULL) break;
  }
  return sub;
}

void setup() {
  for(int k = 4; k<10; k++){
    pinMode(k,OUTPUT);  
  }
  Serial.begin(9600);
  bt.begin(9600);
}

void loop() {
  if(bt.available()){
  dataSend = bt.readStringUntil(':');
  char* buf;
  buf = (char *)malloc(dataSend.length()); //buf = (char *)malloc(dataSend.length());
  dataSend.toCharArray(buf,dataSend.length()+1); 
  
  for(int c = 1; c<commacount; c++){ 
      numbers[c] = atoi(subStr(buf,"/",c)); 
      //Serial.println(numbers[c]); 
  }
  Serial.println(numbers[1]);
  analogWrite(MOTOR2,numbers[1]);
  analogWrite(MOTOR3,numbers[2]);
  analogWrite(MOTOR6,numbers[3]);
  delay(100);
  analogWrite(MOTOR2,0);
  analogWrite(MOTOR3,0);
  analogWrite(MOTOR6,0);

  free(buf);
  }
}
