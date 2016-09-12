#include <EasyTransfer.h>

//#include <SoftEasyTransfer.h>
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(35, 36);

//const int buttonPin = 2;     // the number of the pushbutton pin
const int buttonPin1 = 12; 
const int buttonPin2 = 11; 
const int buttonPin3 = 10; 
const int buttonPin4 = 9; 
const int buttonPin5 = 8; 
const int buttonPin6 = 7; 
const int buttonPin7 = 6; 
const int buttonPin8 = 5;
const int buttonPin9 = 4; 
const int buttonPin10 = 3; 
const int buttonPin11 = 2; 
const int buttonPin12 = 22;
const int buttonPin13 = 23; 
const int buttonPin14 = 24; 

//const int ledPin =  13;      // the number of the LED pin

const int doRolloWzTerAuf =    26;  //Wohnzimmer Terrassentür
const int doRolloWzTerZu =     27;  //Wohnzimmer Terrassentür
const int doRolloWzFsZu =      28;  //Wohnzimmer Fenster Süden
const int doRolloWzFsAuf =     29;  //Wohnzimmer Fenster Süden
const int doRolloBoAuf =       30;  //Buero Osten
const int doRolloBoZu =        31;  //Buero Osten
const int doRolloBnZu =        32;  //Buero Norden
const int doRolloBnAuf =       34;  //Buero Norden
const int doRolloBadZu =       36;
const int doRolloBadAuf =      37;
const int doRolloWzFoAuf =     38;  //Wohnzimmer Fenster Osten
const int doRolloWzFoZu =      39;  //Wohnzimmer Fenster Osten
const int doRolloKuecheAuf =   40;
const int doRolloKuecheZu =    41;

const int doRolloK1Fauf =   42;
const int doRolloK1Fzu =    43;
const int doRolloK1Tauf =   44;
const int doRolloK1Tzu =    45;
const int doRolloK2auf =    46;
const int doRolloK2zu =     47;
const int doRolloK3auf =    48;
const int doRolloK3zu =     49;
const int doRolloBadOGauf = 50;
const int doRolloBadOGzu =  51;

const int doFreigabeRelais = 55;

unsigned long previousMillis = 0;   // will store last time LED was updated
unsigned long ZeitseitStart = 0; 
const long interval = 50;  

struct AUSGANG_STATUS{
  bool doRolloKuecheAuf;
  bool doRolloKuecheZu;
  bool doRolloWzTerAuf;
  bool doRolloWzTerZu;
  bool doRolloWzFsAuf;
  bool doRolloWzFsZu;
  bool doRolloWzFoAuf;
  bool doRolloWzFoZu;
  bool doRolloBoAuf;
  bool doRolloBoZu;
  bool doRolloBnAuf;
  bool doRolloBnZu;
  bool doRolloBadAuf;
  bool doRolloBadZu;
  bool doRolloK1Fauf;
  bool doRolloK1Fzu;
  bool doRolloK1Tauf;
  bool doRolloK1Tzu;
  bool doRolloK2auf;
  bool doRolloK2zu;
  bool doRolloK3auf;
  bool doRolloK3zu;
  bool doRolloBadOGauf;
  bool doRolloBadOGzu;
};

AUSGANG_STATUS doStatus;

// variables will change:
//int buttonState = 0;         // variable for reading the pushbutton status
bool buttonState1 = 0;
bool buttonState2 = 0;
bool buttonState3 = 0;
bool buttonState4 = 0;
bool buttonState5 = 0;
bool buttonState6 = 0;
bool buttonState7 = 0;
bool buttonState8 = 0;
bool buttonState9 = 0;
bool buttonState10 = 0;
bool buttonState11 = 0;
bool buttonState12 = 0;
bool buttonState13 = 0;
bool buttonState14 = 0;

bool FreigabeEin = 0;
const long FreigabeVerz = 5000; 

//create object
//SoftEasyTransfer ET; 
EasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
 int RolloK1F; 
 int RolloK1T; 
 int RolloK2;  
 int RolloK3; 
 int RolloBadOG;  
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

struct MERKER_VARIABLEN{
 int RolloK1F; 
 int RolloK1T; 
 int RolloK2;  
 int RolloK3; 
 int RolloBadOG; 
};

MERKER_VARIABLEN Merker;

struct STATUS_VARIABLEN{
 int RolloKueche;
 int RolloWzTer; 
 int RolloWzFs; 
 int RolloWzFo;  
 int RolloBo; 
 int RolloBn;
 int RolloBadEG;
 int RolloK1F; 
 int RolloK1T; 
 int RolloK2;  
 int RolloK3; 
 int RolloBadOG; 
};

STATUS_VARIABLEN Status;


void setup() {
  
  Serial.begin(9600);
  
  Serial3.begin(28800);
  
  //mySerial.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  ET.begin(details(mydata), &Serial3);

// Pins werden bevor sie als Ausgänge definiert werden auf HIGH gesetzt (= Ausgang LOW) damit die Relais bein einschalten der Steuerung nicht kurz einschalten
  digitalWrite(doRolloKuecheAuf,HIGH); 
  digitalWrite(doRolloKuecheZu,HIGH); 
  digitalWrite(doRolloWzTerAuf,HIGH); 
  digitalWrite(doRolloWzTerZu,HIGH); 
  digitalWrite(doRolloWzFsAuf,HIGH); 
  digitalWrite(doRolloWzFsZu,HIGH); 
  digitalWrite(doRolloWzFoAuf,HIGH); 
  digitalWrite(doRolloWzFoZu,HIGH); 
  digitalWrite(doRolloBoAuf,HIGH); 
  digitalWrite(doRolloBoZu,HIGH); 
  digitalWrite(doRolloBnAuf,HIGH); 
  digitalWrite(doRolloBnZu,HIGH); 
  digitalWrite(doRolloBadAuf,HIGH); 
  digitalWrite(doRolloBadZu,HIGH); 
  
  digitalWrite(doRolloK1Fauf,HIGH); 
  digitalWrite(doRolloK1Fzu,HIGH); 
  digitalWrite(doRolloK1Tauf,HIGH); 
  digitalWrite(doRolloK1Tzu,HIGH); 
  digitalWrite(doRolloK2auf,HIGH); 
  digitalWrite(doRolloK2zu,HIGH); 
  digitalWrite(doRolloK3auf,HIGH); 
  digitalWrite(doRolloK3zu,HIGH); 
  digitalWrite(doRolloBadOGauf,HIGH);
  digitalWrite(doRolloBadOGzu,HIGH);

  digitalWrite(doFreigabeRelais,HIGH);
  

  // initialize the LED pin as an output:
  pinMode(doRolloKuecheAuf, OUTPUT);
  pinMode(doRolloKuecheZu, OUTPUT); 
  pinMode(doRolloWzTerAuf, OUTPUT); 
  pinMode(doRolloWzTerZu, OUTPUT); 
  pinMode(doRolloWzFsAuf, OUTPUT); 
  pinMode(doRolloWzFsZu, OUTPUT); 
  pinMode(doRolloWzFoAuf, OUTPUT); 
  pinMode(doRolloWzFoZu, OUTPUT); 
  pinMode(doRolloBoAuf, OUTPUT); 
  pinMode(doRolloBoZu, OUTPUT); 
  pinMode(doRolloBnAuf, OUTPUT); 
  pinMode(doRolloBnZu, OUTPUT); 
  pinMode(doRolloBadAuf, OUTPUT); 
  pinMode(doRolloBadZu, OUTPUT); 
  
  pinMode(doRolloK1Fauf, OUTPUT); 
  pinMode(doRolloK1Fzu, OUTPUT); 
  pinMode(doRolloK1Tauf, OUTPUT); 
  pinMode(doRolloK1Tzu, OUTPUT); 
  pinMode(doRolloK2auf, OUTPUT); 
  pinMode(doRolloK2zu, OUTPUT); 
  pinMode(doRolloK3auf, OUTPUT); 
  pinMode(doRolloK3zu, OUTPUT); 
  pinMode(doRolloBadOGauf, OUTPUT); 
  pinMode(doRolloBadOGzu, OUTPUT); 

  pinMode(doFreigabeRelais, OUTPUT); 
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  pinMode(buttonPin7, INPUT);
  pinMode(buttonPin8, INPUT);
  pinMode(buttonPin9, INPUT);
  pinMode(buttonPin10, INPUT);
  pinMode(buttonPin11, INPUT);
  pinMode(buttonPin12, INPUT);
  pinMode(buttonPin13, INPUT);
  pinMode(buttonPin14, INPUT);
  
  FreigabeEin = 0;

  Merker.RolloK1F = 3;
  Merker.RolloK1T = 3;
  Merker.RolloK2 = 3;
  Merker.RolloK3 = 3;
  Merker.RolloBadOG = 3;

}

bool F_Trig_1(bool input){
  IF input = HIGH AND inputAlt = LOW THEN
    return F_Trig_1 = 1
    
}

void R_Trig(){
  
}

void T_ON(){
  
}

void T_OFF(){
  
}

void loop(){
  
  unsigned long currentMillis = millis();
 
//EG
  doStatus.doRolloKuecheAuf =  digitalRead(doRolloKuecheAuf);
  doStatus.doRolloKuecheZu =   digitalRead(doRolloKuecheZu);
  doStatus.doRolloWzTerAuf =   digitalRead(doRolloWzTerAuf);
  doStatus.doRolloWzTerZu =    digitalRead(doRolloWzTerZu);
  doStatus.doRolloWzFsAuf =    digitalRead(doRolloWzFsAuf);
  doStatus.doRolloWzFsZu =     digitalRead(doRolloWzFsZu);
  doStatus.doRolloWzFoAuf =    digitalRead(doRolloWzFoAuf);
  doStatus.doRolloWzFoZu =     digitalRead(doRolloWzFoZu);
  doStatus.doRolloBoAuf =      digitalRead(doRolloBoAuf);
  doStatus.doRolloBoZu =       digitalRead(doRolloBoZu);
  doStatus.doRolloBnAuf =      digitalRead(doRolloBnAuf);
  doStatus.doRolloBnZu =       digitalRead(doRolloBnZu);
  doStatus.doRolloBadAuf =     digitalRead(doRolloBadAuf);
  doStatus.doRolloBadZu =      digitalRead(doRolloBadZu);
  
//OG
  doStatus.doRolloK1Fzu =     digitalRead(doRolloK1Fzu);
  doStatus.doRolloK1Fauf =    digitalRead(doRolloK1Fauf);
  doStatus.doRolloK1Tzu =     digitalRead(doRolloK1Tzu);
  doStatus.doRolloK1Tauf =    digitalRead(doRolloK1Tauf);
  doStatus.doRolloK2zu =      digitalRead(doRolloK2zu);
  doStatus.doRolloK2auf =     digitalRead(doRolloK2auf);
  doStatus.doRolloK3zu =      digitalRead(doRolloK3zu);
  doStatus.doRolloK3auf =     digitalRead(doRolloK3auf);
  doStatus.doRolloBadOGzu =   digitalRead(doRolloBadOGzu);
  doStatus.doRolloBadOGauf =  digitalRead(doRolloBadOGauf);
  
  if (doStatus.doRolloKuecheAuf ==  LOW && doStatus.doRolloKuecheZu == LOW){Status.RolloKueche = 2;}else{Status.RolloKueche = 1;}
  if (doStatus.doRolloWzTerAuf ==   LOW && doStatus.doRolloWzTerZu ==  LOW){Status.RolloWzTer = 2;} else{Status.RolloWzTer = 1;}
  if (doStatus.doRolloWzFsAuf ==    LOW && doStatus.doRolloWzFsZu ==   LOW){Status.RolloWzFs = 2;}  else{Status.RolloWzFs = 1;}
  if (doStatus.doRolloWzFoAuf ==    LOW && doStatus.doRolloWzFoZu ==   LOW){Status.RolloWzFo = 2;}  else{Status.RolloWzFo = 1;}
  if (doStatus.doRolloBoAuf ==      LOW && doStatus.doRolloBoZu ==     LOW){Status.RolloBo = 2;}    else{Status.RolloBo = 1;}
  if (doStatus.doRolloBnAuf ==      LOW && doStatus.doRolloBnZu ==     LOW){Status.RolloBn = 2;}    else{Status.RolloBn = 1;}
  if (doStatus.doRolloBadAuf ==     LOW && doStatus.doRolloBadZu ==    LOW){Status.RolloBadEG = 2;} else{Status.RolloBadEG = 1;}
  if (doStatus.doRolloK1Fzu ==      LOW && doStatus.doRolloK1Fauf ==   LOW){Status.RolloK1F = 2;}   else{Status.RolloK1F = 1;}
  if (doStatus.doRolloK1Tzu ==      LOW && doStatus.doRolloK1Tauf ==   LOW){Status.RolloK1T = 2;}   else{Status.RolloK1T = 1;}
  if (doStatus.doRolloK2zu ==       LOW && doStatus.doRolloK2auf ==    LOW){Status.RolloK2 = 2;}    else{Status.RolloK2 = 1;}  
  if (doStatus.doRolloK3zu ==       LOW && doStatus.doRolloK3auf ==    LOW){Status.RolloK3 = 2;}    else{Status.RolloK3 = 1;}
  if (doStatus.doRolloBadOGzu ==    LOW && doStatus.doRolloBadOGauf == LOW){Status.RolloBadOG = 2;} else{Status.RolloBadOG = 1;}
  
//Ausgangsstatus prüfen
  if ((Status.RolloKueche + Status.RolloWzTer + Status.RolloWzFs + Status.RolloWzFo + Status.RolloBo + Status.RolloBn + Status.RolloBadEG + Status.RolloK1F + Status.RolloK1T + Status.RolloK2 + Status.RolloK3 + Status.RolloBadOG) > 12){
    FreigabeEin = 0;
  }
  else{
    FreigabeEin = 1;
  }
  
  if (FreigabeEin == 1 && currentMillis >= FreigabeVerz){
    digitalWrite(doFreigabeRelais, LOW);
  }
  else{
    digitalWrite(doFreigabeRelais, HIGH);
  }
    
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  if(ET.receiveData()){
    Serial.println("Rec");
    
    if (mydata.RolloK1F == 1){
      digitalWrite(doRolloK1Fauf, LOW);
      digitalWrite(doRolloK1Fzu,  HIGH);
    }
    else if (mydata.RolloK1F == 2){
      digitalWrite(doRolloK1Fauf, HIGH);
      digitalWrite(doRolloK1Fzu,  LOW);
    }
    else{
      digitalWrite(doRolloK1Fauf, HIGH);
      digitalWrite(doRolloK1Fzu,  HIGH);
    }
    
    if (mydata.RolloK1T == 1){
      digitalWrite(doRolloK1Tauf, LOW);
      digitalWrite(doRolloK1Tzu,  HIGH);
    }
    else if (mydata.RolloK1T == 2){
      digitalWrite(doRolloK1Tauf, HIGH);
      digitalWrite(doRolloK1Tzu,  LOW);
    }
    else{
      digitalWrite(doRolloK1Tauf, HIGH);
      digitalWrite(doRolloK1Tzu,  HIGH);
    }
    
    if (mydata.RolloK2 == 1){
      digitalWrite(doRolloK2auf, LOW);
      digitalWrite(doRolloK2zu,  HIGH);
    }
    else if (mydata.RolloK2 == 2){
      digitalWrite(doRolloK2auf, HIGH);
      digitalWrite(doRolloK2zu,  LOW);
    }
    else{
      digitalWrite(doRolloK2auf, HIGH);
      digitalWrite(doRolloK2zu,  HIGH);
    }
    
    if (mydata.RolloK3 == 1){
      digitalWrite(doRolloK3auf, LOW);
      digitalWrite(doRolloK3zu,  HIGH);
    }
    else if (mydata.RolloK3 == 2){
      digitalWrite(doRolloK3auf, HIGH);
      digitalWrite(doRolloK3zu,  LOW);
    }
    else{
      digitalWrite(doRolloK3auf, HIGH);
      digitalWrite(doRolloK3zu,  HIGH);
    }
    
     if (mydata.RolloBadOG == 1){
       Serial.println("Bad auf");
       digitalWrite(doRolloBadOGauf, LOW);
       digitalWrite(doRolloBadOGzu,  HIGH);
     }
     else if (mydata.RolloBadOG == 2){
       Serial.println("Bad zu");
       digitalWrite(doRolloBadOGauf, HIGH);
       digitalWrite(doRolloBadOGzu,  LOW);
     }
     else{
       digitalWrite(doRolloBadOGauf, HIGH);
       digitalWrite(doRolloBadOGzu,  HIGH);
     }
  
    
  }
//  else{
//    digitalWrite(doRolloK1Fauf,     HIGH);
//    digitalWrite(doRolloK1Fzu,      HIGH);
//    digitalWrite(doRolloK1Tauf,     HIGH);
//    digitalWrite(doRolloK1Tzu,      HIGH);
//    digitalWrite(doRolloK2auf,      HIGH);
//    digitalWrite(doRolloK2zu,       HIGH);
//    digitalWrite(doRolloK3auf,      HIGH);
//    digitalWrite(doRolloK3zu,       HIGH);
//    digitalWrite(doRolloBadOGauf,   HIGH);
//    digitalWrite(doRolloBadOGzu,    HIGH);
//  }
  

  }

  
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  buttonState7 = digitalRead(buttonPin7);
  buttonState8 = digitalRead(buttonPin8);
  buttonState9 = digitalRead(buttonPin9);
  buttonState10 = digitalRead(buttonPin10);
  buttonState11 = digitalRead(buttonPin11);
  buttonState12 = digitalRead(buttonPin12);
  buttonState13 = digitalRead(buttonPin13);
  buttonState14 = digitalRead(buttonPin14);
  
//  IF Merker.Schalter_1 <> Schalter_1 AND Schalter_1 = HIGH THEN
//    Schalter_1_Rtrig = HIGH;
//    Schalter_1_Ftrig = LOW;
//    Merker.Schalter_1 = HIGH;
//  ELSIF Merker.Schalter_1 <> Schalter_1 AND Schalter_1 = LOW THEN
//    Schalter_1_Rtrig = LOW;
//    Schalter_1_Ftrig = HIGH;
//    Merker.Schalter_1 = LOW;
//  ELSE
//    Schalter_1_Rtrig = LOW;
//    Schalter_1_Ftrig = LOW;
//  END_IF
    



  // Rollo Wohnzimmer Terasse
  if (buttonState1 == HIGH && doStatus.doRolloWzTerZu == HIGH) {digitalWrite(doRolloWzTerAuf, LOW);} else {digitalWrite(doRolloWzTerAuf, HIGH); }
  if (buttonState2 == HIGH && doStatus.doRolloWzTerAuf == HIGH) {digitalWrite(doRolloWzTerZu, LOW);} else {digitalWrite(doRolloWzTerZu, HIGH); }
  
  // Rollo Wohnzimmer Fenster Süd
  if (buttonState3 == HIGH && doStatus.doRolloWzFsAuf == HIGH) {digitalWrite(doRolloWzFsZu, LOW);} else {digitalWrite(doRolloWzFsZu, HIGH); }
  if (buttonState4 == HIGH && doStatus.doRolloWzFsZu == HIGH) {digitalWrite(doRolloWzFsAuf, LOW);} else {digitalWrite(doRolloWzFsAuf, HIGH); }
  
  // Rollo Büro Ost
  if (buttonState5 == HIGH && doStatus.doRolloBoZu == HIGH) {digitalWrite(doRolloBoAuf, LOW);} else {digitalWrite(doRolloBoAuf, HIGH); }
  if (buttonState6 == HIGH && doStatus.doRolloBoAuf == HIGH) {digitalWrite(doRolloBoZu, LOW);} else {digitalWrite(doRolloBoZu, HIGH); }
  
  // Rollo Büro Nord
  if (buttonState7 == HIGH && doStatus.doRolloBnZu == HIGH) {digitalWrite(doRolloBnAuf, LOW);} else {digitalWrite(doRolloBnAuf, HIGH); } //
  if (buttonState8 == HIGH && doStatus.doRolloBnAuf == HIGH) {digitalWrite(doRolloBnZu, LOW);} else {digitalWrite(doRolloBnZu, HIGH); } //
  
  // Rollo Bad
  if (buttonState9 == HIGH && doStatus.doRolloBadAuf == HIGH) {digitalWrite(doRolloBadZu, LOW);} else {digitalWrite(doRolloBadZu, HIGH); }
  if (buttonState10 == HIGH && doStatus.doRolloBadZu == HIGH) {digitalWrite(doRolloBadAuf, LOW);} else {digitalWrite(doRolloBadAuf, HIGH); }
  
  // Rollo Wohnzimmer Fenster Ost
  if (buttonState11 == HIGH && doStatus.doRolloWzFoZu == HIGH) {digitalWrite(doRolloWzFoAuf, LOW);} else {digitalWrite(doRolloWzFoAuf, HIGH); }
  if (buttonState12 == HIGH && doStatus.doRolloWzFoAuf == HIGH) {digitalWrite(doRolloWzFoZu, LOW);} else {digitalWrite(doRolloWzFoZu, HIGH); }
  
  // Rollo Küche
  if (buttonState13 == HIGH && doStatus.doRolloKuecheZu == HIGH) {digitalWrite(doRolloKuecheAuf, LOW);} else {digitalWrite(doRolloKuecheAuf, HIGH); }
  if (buttonState14 == HIGH && doStatus.doRolloKuecheAuf == HIGH) {digitalWrite(doRolloKuecheZu, LOW);} else {digitalWrite(doRolloKuecheZu, HIGH); }
}
