#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(38,16,2);

char k[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};

byte rpins[4]={2,3,4,5};
byte cpins[4]={6,7,8,9};
char myk;
Keypad mypad (makeKeymap(k),rpins,cpins,4,4);
char pass[6]={'1','3','4','5','6','7'}; // تغيير حجم المتغير إلى 6
char upass[6]={0}; // تغيير حجم المتغير إلى 6
char newpass[6]={0}; // تغيير حجم المتغير إلى 6
byte counter=0,i=0;
bool reset=false;

void reslcd(){
 lcd.clear();
 lcd.print("Enter pass");
 lcd.setCursor(0,1);
}

void setup() {
  Serial.begin(9600);
  pinMode(10,OUTPUT);
 lcd.init();
 lcd.backlight();
 reslcd();

}
void loop() {
  myk=mypad.getKey();
  while(!myk)myk=mypad.getKey();
  lcd.print("*");
  if(myk=='D'){
    lcd.clear();  
    for(i=0;i<sizeof(upass);i++) if(upass[i]!=pass[i])break;
    if((i==sizeof(upass))&&(counter==0))
      right_pass();
    else 
      wrong_pass();
  
  }
  else if(myk=='A'){
    reset=true;
    lcd.clear();
    lcd.print("Enter new pass");
    lcd.setCursor(0,1);
  }
  else if(reset){
    *(newpass+counter)=myk;
    counter=(counter++>=5)?0:counter; // تغيير الشرط إلى counter==5
    if(counter==5){ // تغيير الشرط إلى counter==5
      change_pass();
      
    }
  }
  else
    *(upass+counter)=myk;
  
 counter=(counter++>=5)?0:counter; // تغيير الشرط إلى counter==5
}





void right_pass(){
  counter=-1;
  lcd.clear();
  lcd.print("right password");
  digitalWrite(10,1);
  delay(3000);
  digitalWrite(10,0);
  reslcd();
}

void wrong_pass(){
  counter=-1;
  lcd.clear();
  lcd.print("Wrong password");
  delay(2000);
  reslcd();
}

void change_pass(){
  for(i=0;i<sizeof(pass);i++){
    pass[i]=newpass[i];
    newpass[i]=0;
  }
  reset=false;
  lcd.clear();
  lcd.print("Password changed");
  delay(2000);
  reslcd();
}
