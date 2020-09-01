#include<LiquidCrystal.h>

LiquidCrystal lcd(53,51,49,47,45,43);

//input section- A to B height of tank
const int low=3,full=17;

int va;
bool fu=true, lo=true;
const int t=36,e=A8,buz=7;

byte batteryBody[8] = {
  0b1111,
  0b1111,
  0b1111,
  0b1111,
  0b1111,
  0b1111,
  0b1111,
  0b1111
};

byte batteryEmpty[8] = {
  0b1111,
  0b1111,
  0b0000,
  0b0000,
  0b0000,
  0b0000,
  0b1111,
  0b1111
};

byte batteryHead[8] = {
  0b1100,
  0b1100,
  0b0111,
  0b0111,
  0b0111,
  0b0111,
  0b1100,
  0b1100
};

byte batteryHalf[8] = {
  0b1111,
  0b1111,
  0b1000,
  0b1100,
  0b1110,
  0b1110,
  0b1111,
  0b1111
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b10001,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};


void setup(){
  pinMode(t,OUTPUT);
  pinMode(e,INPUT);
  pinMode(buz,OUTPUT);
  
  lcd.begin(16,2);
  Serial.begin(9600);

  lcd.createChar(1, batteryBody);
  lcd.createChar(2, batteryEmpty);
  lcd.createChar(3, batteryHead);
  lcd.createChar(4, batteryHalf);
  lcd.createChar(5, smiley);
  
  digitalWrite(buz,1);  
  lcd.setCursor(1,0);
  lcd.print("Mahadi Hassan");
  lcd.setCursor(4,1);
  lcd.print("Mithun");
  delay(2000);
  digitalWrite(buz,0);

  lcd.noDisplay();
  delay(500);
  lcd.display();
  
}

void loop(){
  
  va =sonic();
  va = map(va, full, low, 0, 100);
  if(va>100){
    va=100;
  }
  else if(va<0){
    va=0;
  }


  //print with lcd
  lcd.clear();

  if(va>95){
    lcd.setCursor(0,0);
    lcd.print(" Tank: Full ^_^");
  }
  else if(va<10){
    lcd.setCursor(0,0);
    lcd.print(" Tank: Low o_O !");
  }
  else{
    lcd.setCursor(0,0);
    lcd.print(" Tank: Normal ");
    lcd.write(5);
  }

  
  lcd.setCursor(0,1);
  lcd.write(1);
  
  lcd.setCursor(1,1);
  for(int i=0;i<=10;i++){
    lcd.write(2);
  }
  lcd.setCursor(0,1);
  for(int i=0;i<=map(va,0,100,0,10);i++){
    lcd.write(1);
    if(i==map(va,0,100,0,10)){
      lcd.write(4);
    }
  }
  
  lcd.setCursor(11,1);
  lcd.write(3);
  if(va<100){
    lcd.print(" ");
  }
  lcd.print(va);
  lcd.print("%");


  //tank full
  if(va>95 && fu){
    war(7);
    fu=false;
    lo=true;
  }
  else if(va<10 && lo){
    war(7);
    lo=false;
    fu=true;
  }
      
  
  delay(700);


  //print with serial communication
  Serial.print(sonic());
  Serial.print("\t");
  Serial.println (va);

  
  
}

//function define

void war(int d){
  for (int i=0;i<d;i++){
    digitalWrite(buz,1);
    delay(500);
    digitalWrite(buz,0);
    lcd.noDisplay();
    delay(500);
    lcd.display();
  }
}

int sonic(){
  digitalWrite(t,0);
  delay(2);

  digitalWrite(t,1);
  delay(10);
  digitalWrite(t,0);

  int d=pulseIn(e,1);
  int inc=(d*0.0133)/2;
  return inc;
}
