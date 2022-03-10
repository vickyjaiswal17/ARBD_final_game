byte BodyLeg[] = {
  B00000,
  B00000,
  B00000,
  B00011,
  B11111,
  B10000,
  B00000,
  B00000
};
byte HeadArm[] = {
   B00000,
  B00000,
  B00110,
  B11110,
  B11000,
  B00111,
  B00000,
  B00000
};
byte ObsticleUp[] = {
  B11111,
  B11111,
  B11111,
  B01110,
  B01110,
  B01110,
  B00100,
  B00100
};
byte ObsticleDown[] = {
  B00100,
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B11111,
  B11111
};

#include <LiquidCrystal.h>
#include<TimerOne.h>
int key,n=1,m=1,pos=0,obstNo=1,obstgap,i;
int obstCpos[2]={16,16};
int obstRpos[2]={1,1};
int obstype[2]={3,3};
int buttonPin=A1;
int buzzerPin=6;
int pinR=11;
int pinG=9;
int pinB=10;
long int score=0;
int rs = 4, en = 5, d4 = 0, d5 = 1, d6 = 2, d7 = 3;
LiquidCrystal  lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, BodyLeg);
  lcd.createChar(1,HeadArm);
  lcd.createChar(2,ObsticleUp);
  lcd.createChar(3,ObsticleDown);
  pinMode(buttonPin,INPUT);
  lcd.home();
  lcd.print("Start Game");
  pinMode(buzzerPin,OUTPUT);
  pinMode(pinR,OUTPUT);
  pinMode(pinG,OUTPUT);
  pinMode(pinB,OUTPUT);
  digitalWrite(pinG,HIGH);
  Timer1.initialize(150000);
  Timer1.attachInterrupt(obsticle);
}

void loop() {
   key=analogRead(buttonPin);   //taking analog input
   
    if((key > 600) && (key < 725) && n==1) //condition to check Enter button is pressed?
    {
        digitalWrite(pinG,LOW);
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.write((byte)0);
        lcd.setCursor(2,0);
        lcd.write((byte)1); 
        digitalWrite(pinR,HIGH);
        delay(100);
        digitalWrite(pinR,LOW);
        delay(100);
        digitalWrite(pinG,HIGH);
        delay(100);
        digitalWrite(pinG,LOW);
        delay(100);
        digitalWrite(pinB,HIGH);
        delay(100);
        digitalWrite(pinB,LOW);
        delay(100); 
        n=2;
        i=0;
        
    }

    
     do
    {
      key=analogRead(buttonPin); 
      delay(20); 
    } while((key > 600) && (key < 725) && m==1);
    
    if(n==2)
    {
      m=2;
    }
    
    
     
    if(key < 100 && n==2)  
     {
      lcd.clear();
       for(int i=0;i<obstNo;i++)
      {
      lcd.setCursor(obstCpos[i],obstRpos[i]);
      lcd.write((byte)obstype[i]) ;    
      }
      
      pos=0;
      lcd.setCursor(1,pos);
      lcd.write((byte)0);
      lcd.setCursor(2,pos);
      lcd.write((byte)1);
      
       digitalWrite(pinB,HIGH);
      analogWrite(buzzerPin,125);
      delay(10);
      analogWrite(buzzerPin,0); 
      digitalWrite(pinB,LOW);  
      
     }

   
   if((key > 790) && (key < 850) && n==2)
    { 
      lcd.clear();
      for(int i=0;i<obstNo;i++)
      {
      lcd.setCursor(obstCpos[i],obstRpos[i]);
      lcd.write((byte)obstype[i]) ;
      }
         pos=1;
         lcd.setCursor(1,pos);
         lcd.write((byte)0);
         lcd.setCursor(2,pos);
         lcd.write((byte)1);
         
      digitalWrite(pinB,HIGH);
      analogWrite(buzzerPin,125);
      delay(10);
      analogWrite(buzzerPin,0); 
      digitalWrite(pinB,LOW);    
    }
     
  for(int i=0;i<obstNo;i++)
  {
      if(obstRpos[i]==pos && (obstCpos[i]==1 || obstCpos[i]==2 ))
     {
      n=3;
      obstCpos[i]=16;
      pos=0;
      digitalWrite(pinR,HIGH);
      analogWrite(buzzerPin,125);   
      delay(700);
      analogWrite(buzzerPin,0);
      digitalWrite(pinR,LOW);
      digitalWrite(pinG,HIGH);
      lcd.clear();
      lcd.print("OUT");
      lcd.setCursor(0,1);
      lcd.print("score:");
      lcd.print(score);
      score=0;
     }
  }
    
     if((key > 600) && (key < 725) && n==3)
     { 
       lcd.clear();
       lcd.print("Start Game");
       m=3;
       n=1;
     }

     do
    {
      key=analogRead(buttonPin); 
      delay(20); 
    } while((key > 600) && (key < 725) && m==3);
    
    if(n==1)
    {
      m=1;
    }
    
randomGen();
}
  
void obsticle()
{
  if(n==2)
   {
     analogWrite(buzzerPin,125);
      delay(5);
      analogWrite(buzzerPin,0);   
      lcd.clear();
      lcd.setCursor(1,pos);
      lcd.write((byte)0);
      lcd.setCursor(2,pos);
      lcd.write((byte)1);

      
      for(int i=0;i<obstNo;i++)
      {
      lcd.setCursor(obstCpos[i],obstRpos[i]);
      lcd.write((byte)obstype[i]) ;    
      obstCpos[i]--;
      }
     
      score+=1;
  }
return;
}

void randomGen()
{
  
if(obstCpos[0]==obstgap)
{
  obstNo=2; 
}

if(obstCpos[0]==0)
 {
  obstgap=random(4,12);
 }
if(obstCpos[1]==0)
{
  obstNo=1; 
}
for(int i=0;i<2;i++)
{
 if(obstCpos[i]==0)
 {
  obstCpos[i]=16;
  obstype[i]=random(2,4);
    if(obstype[i]==2)
    {
      obstRpos[i]=0;
    }
    else
    {
    obstRpos[i]=1;
    }
 }
}
}
