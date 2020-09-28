#include <Servo.h>
#include <Key.h>
#include <Keypad.h>

//函数声明
void door_open();
void get_input_passwd();
int passwd_compare();
void start_beep();
void click_beep();
void confirm_beep();
void error_beep();

//密码
const char PASSWD[] = "875626BB·";

//矩阵键盘参数
const byte ROWS = 4; //矩阵键盘行数
const byte COLS = 4; //矩阵键盘列数

char Keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad MyKeypad = Keypad(makeKeymap(Keys),rowPins,colPins,ROWS,COLS);


//键入密码相关参数
const byte PW_MAX=10;
char INPUT_PASSWD[10];

//舵机相关参数

Servo MyServo;
int POS = 0;

//蜂鸣器相关参数
#define BUZZER 11
int VOICE;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MyServo.attach(10);
  MyServo.write(0);
  pinMode(BUZZER,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    get_input_passwd();
    if(passwd_compare()){
      confirm_beep();
      door_open();
      INPUT_PASSWD[0]=0;
    }
    else{
      error_beep();
    }
}


void get_input_passwd(){
  char key;
  key = MyKeypad.waitForKey();
  if(key == '#'){
    start_beep();
    for(int i =0;i<PW_MAX;i++){
      key = MyKeypad.waitForKey();
      click_beep();
      if(key == 'D'){
        INPUT_PASSWD[i]=0;
        break;
      }
      else{
        INPUT_PASSWD[i] = key;
      }
   }
  }
}

int passwd_compare(){
    return(!strcmp(PASSWD,INPUT_PASSWD));
}

void door_open(){
    for(POS = 0;POS < 108;POS +=1){
      MyServo.write(POS);
      delay(5);
    }
    delay(2000);

    for(POS = 108;POS >= 1;POS -=1){
      MyServo.write(POS);
      delay(10);
    }
    delay(1000);
    }

void start_beep(){
    for(int count=0;count<30;count++){
      tone(BUZZER,800);
      delay(5);
     }
      noTone(BUZZER);
}

void click_beep(){
    for(int count=0;count<10;count++){
      tone(BUZZER,800);
      delay(5);
    }
    noTone(BUZZER);
}

void confirm_beep(){
    for(int count=0;count<10;count++){
      tone(BUZZER,900);
      delay(5);
    }
    delay(100);
    for(int count=0;count<10;count++){
      tone(BUZZER,900);
      delay(5);
    }
    noTone(BUZZER);
}

void error_beep(){
    for(int count=0;count<30;count++){
      tone(BUZZER,1500);
      delay(5);
    }
    noTone(BUZZER);
}
