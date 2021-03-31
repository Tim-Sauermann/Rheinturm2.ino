//Variablen
int i = 0;
int zustandSchalter1 = 0;
int zustandSchalter3 = 0;
int sekunden = 0;
int minuten = 0;
int stunden = 0;
int tag = 11;
int monat = 1;
int datum[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
int jahr = 2021;
unsigned long startZeit;
unsigned long diff;


//LED und Schalter
int se[9];
int sz[5];
int me[9];
int mz[5];
int he[9];
int hz[2];
int schalter1 = 14;
int schalter2 = 15;
int schalter3 = 16;

//Funktionsdeklaration
void allHigh();
void allLow();
void blinken(bool std, bool mint, bool sek, int interval, char ausgabe);
void datumAusgabe();
void datumModus();
void uhr();
void uhrAusgabe();
void uhrModus();
void uhrStellen(bool vor, int stellwert);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 9; i = i + 1) {
    se[i] = 2 + i;                          //Zuweisen der Einersekunden zu den Ausgängen
    pinMode(se[i], OUTPUT);                 //Setzen der Einersekunden auf OUTPUT
  }

  for (int i = 0; i < 5; i = i + 1) {
    sz[i] = 22 + i;                         //Zuweisen der Zehnersekunden zu den Ausgängen
    pinMode(sz[i], OUTPUT);                 //Setzen der Zehnersekunden auf OUTPUT
  }

  for (int i = 0; i < 9; i = i + 1) {
    me[i] = 27 + i;                         //Zuweisen der Einerminuten zu den Ausgängen
    pinMode(me[i], OUTPUT);                 //Setzen der Einerminuten auf OUTPUT
  }

  for (int i = 0; i < 5; i = i + 1) {
    mz[i] = 36 + i;                         //Zuweisen der Zehnerminuten zu den Ausgängen
    pinMode(mz[i], OUTPUT);                 //Setzen der Zehnerminuten auf OUTPUT
  }

  for (int i = 0; i < 9; i = i + 1) {
    he[i] = 41 + i;                         //Zuweisen der Einerstunden zu den Ausgängen
    pinMode(he[i], OUTPUT);                 //Setzen der Einerstunden auf OUTPUT
  }

  for (int i = 0; i < 2; i = i + 1) {
    hz[i] = 50 + i;                         //Zuweisen der Zehnerstunden zu den Ausgängen
    pinMode(hz[i], OUTPUT);                 //Setzen der Zehnerstunden auf OUTPUT
  }
  
  pinMode(schalter1, INPUT_PULLUP);
  pinMode(schalter2, INPUT_PULLUP);
  pinMode(schalter3, INPUT_PULLUP);

  startZeit = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(schalter3) == LOW){
    zustandSchalter3++;
    zustandSchalter3 = zustandSchalter3 % 2;
    delay(500);
  }

  if(zustandSchalter3 == 0) uhrModus();                           //Definition Zeile
  else if(zustandSchalter3 == 1) datumModus();                    //Definition Zeile

  uhr();
}


//Funktionsdefinition

void allHigh(){
  for (int i = 0; i < 2; i = i + 1) {
    digitalWrite(hz[i], HIGH);
  }
  for (int i = 0; i < 9; i = i + 1) {
    digitalWrite(me[i], HIGH);
    digitalWrite(se[i], HIGH);
    digitalWrite(he[i], HIGH);
  }
  for (int i = 0; i < 5; i = i + 1) {
    digitalWrite(sz[i], HIGH);
    digitalWrite(mz[i], HIGH);
  }
}


void allLow() {
  for (int i = 0; i < 2; i = i + 1) {
    digitalWrite(hz[i], LOW);
  }
  for (int i = 0; i < 9; i = i + 1) {
    digitalWrite(me[i], LOW);
    digitalWrite(se[i], LOW);
    digitalWrite(he[i], LOW);
  }
  for (int i = 0; i < 5; i = i + 1) {
    digitalWrite(sz[i], LOW);
    digitalWrite(mz[i], LOW);
  }
}


void blinken(bool std, bool mint, bool sek, int interval, char ausgabe){
  if(std == true){
    for (int i = 0; i < 2; i = i + 1) {
      digitalWrite(hz[i], LOW);
    }
    for (int i = 0; i < 9; i = i + 1) {
      digitalWrite(he[i], LOW);
    }
  }
  if(mint == true){
    for (int i = 0; i < 5; i = i + 1) {
      digitalWrite(mz[i], LOW);
    }
    for (int i = 0; i < 9; i = i + 1) {
      digitalWrite(me[i], LOW);
    }
  }
  if(sek == true){
    for (int i = 0; i < 5; i = i + 1) {
      digitalWrite(sz[i], LOW);
    }
    for (int i = 0; i < 9; i = i + 1) {
      digitalWrite(se[i], LOW);
    }
  }
  delay(interval);
  if(ausgabe == 'u') uhrAusgabe();
  else if(ausgabe == 'd') datumAusgabe();
  else if(ausgabe == 'j') jahrAusgabe(jahr);
  delay(interval);
}


void datumAusgabe(){
  allLow();
  int u;
  //Sekunden
  u = tag % 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(se[u], HIGH);
  }
  u = tag / 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(sz[u], HIGH);
  }
  //Minuten
  u = monat % 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(me[u], HIGH);
  }
  if(monat / 10 == 1)  digitalWrite(mz[0], HIGH);
}


void datumModus(){
  if(digitalRead(schalter1) == LOW){
    zustandSchalter1++;
    zustandSchalter1 = zustandSchalter1 % 4;
    delay(500);
  }
  if(zustandSchalter1 == 0){
    datumAusgabe();
  }
  while(zustandSchalter1 > 0){
    if(zustandSchalter1 == 1){
      blinken(true, true, true, 50, 'j');
      blinken(true, true, true, 50, 'j');
      if(digitalRead(schalter2) == LOW){
        uhrStellen(true, 5);
      }
      else if(digitalRead(schalter3) == LOW){
      uhrStellen(false, 5);
      }
      jahrAusgabe(jahr);
    }
    else if(zustandSchalter1 == 2){
      blinken(false, true, false, 50, 'd');
      blinken(false, true, false, 50, 'd');
      if(digitalRead(schalter2) == LOW){
        uhrStellen(true, 4);
      }
      else if(digitalRead(schalter3) == LOW){
        uhrStellen(false, 4);
      }
      datumAusgabe();
    }
    else if(zustandSchalter1 == 3){
      blinken(false, false, true, 50, 'd');
      blinken(false, false, true, 50, 'd');
      if(digitalRead(schalter2) == LOW){
        uhrStellen(true, 3);
      }
      else if(digitalRead(schalter3) == LOW){
        uhrStellen(false, 3);
      }
      datumAusgabe();
    }
    delay(300);
    if(digitalRead(schalter1) == LOW){
      zustandSchalter1++;
      zustandSchalter1 = zustandSchalter1 % 4;
      delay(500);
    }
    uhr();
  }
  
}


void jahrAusgabe(int jahrKopie){
  allLow();
  int u;
  //Einer
  u = jahrKopie % 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(se[u], HIGH);
  }
  jahrKopie = jahrKopie /10;
  //Zehner
  u = jahrKopie % 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(me[u], HIGH);
  }
  jahrKopie = jahrKopie /10;
  //Hunderter
  u = jahrKopie % 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(he[u], HIGH);
  }
  jahrKopie = jahrKopie /10;
  //
  u = jahrKopie % 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(hz[u], HIGH);
  }
}


void uhr(){
  if(millis() < startZeit){
    unsigned long zwischenDiff = 4294967296-startZeit;
    diff = zwischenDiff + millis();
  }
  else{
    diff = millis() - startZeit;
  }
  if(diff >= 1000){
    uhrStellen(true, 0);
    unsigned long diffreal = diff - 1000;
    if(diffreal < 1000){
      startZeit = millis() - diffreal;
    }
    else {
      startZeit = millis();
    }
  }
}


void uhrAusgabe(){
  allLow();
  int u;
  //Sekunden
  u = sekunden % 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(se[u], HIGH);
  }
  u = sekunden / 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(sz[u], HIGH);
  }
  //Minuten
  u = minuten % 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(me[u], HIGH);
  }
  u = minuten / 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(mz[u], HIGH);
  }
  //Stunden
  u = stunden % 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(he[u], HIGH);
  }
  u = stunden / 10;
  u--;
  for(u; u >= 0; u--){
    digitalWrite(hz[u], HIGH);
  }
}


void uhrModus(){
  if(digitalRead(schalter1) == LOW){
    zustandSchalter1++;
    zustandSchalter1 = zustandSchalter1 % 4;
    delay(500);
  }
  if(zustandSchalter1 == 0) uhrAusgabe();
  while(zustandSchalter1 > 0){
    if(zustandSchalter1 == 1){
      blinken(true, false, false, 50, 'u');
      blinken(true, false, false, 50, 'u');
      if(digitalRead(schalter2) == LOW){
        uhrStellen(true, 2);
      }
      else if(digitalRead(schalter3) == LOW){
        uhrStellen(false, 2);
      }
    }
    else if(zustandSchalter1 == 2){
      blinken(false, true, false, 50, 'u');
      blinken(false, true, false, 50, 'u');
      if(digitalRead(schalter2) == LOW){
        uhrStellen(true, 1);
      }
      else if(digitalRead(schalter3) == LOW){
        uhrStellen(false, 1);
      }
    }
    else if(zustandSchalter1 == 3){
      blinken(false, false, true, 50, 'u');
      blinken(false, false, true, 50, 'u');
      if(digitalRead(schalter2) == LOW){
        uhrStellen(true, 0);
      }
      else if(digitalRead(schalter3) == LOW){
        uhrStellen(false, 0);
      }
    }
    delay(300);
    uhrAusgabe();
    if(digitalRead(schalter1) == LOW){
      zustandSchalter1++;
      zustandSchalter1 = zustandSchalter1 % 4;
      delay(500);
    }
  }
}


void uhrStellen(bool vor, int stellwert){
  if(vor == true){
    if(stellwert == 0) sekunden++;
    else if(stellwert == 1) minuten++;
    else if(stellwert == 2) stunden++;
    else if(stellwert == 3) tag++;
    else if(stellwert == 4) monat++;
    else if(stellwert == 5) jahr++;
    if(sekunden > 59){
      sekunden = 0;
      minuten++;
    }
    if(minuten > 59){
      minuten = 0;
      stunden++;
    }
    if(stunden > 23) {
      stunden = 0;
      tag++;
    }
    if(monat == 2 && jahr % 4 == 0 && tag == 29);   //Schaltjahr
    else if(datum[monat-1] < tag){
      tag = 1;
      monat++;
    }
    if(monat > 12){
      monat = 1;
      jahr++;
    }
  }
  else{
    if(stellwert == 0) sekunden--;
    else if(stellwert == 1) minuten--;
    else if(stellwert == 2) stunden--;
    else if(stellwert == 3) tag--;
    else if(stellwert == 4) monat--;
    else if(stellwert == 5) jahr--;
    if(sekunden < 0){
      sekunden = 59;
      minuten--;
    }
    if(minuten < 0){
      minuten = 59;
      stunden--;
    }
    if(stunden < 0) {
      stunden = 23;
      tag--;
    }
    if(monat == 3 && jahr % 4 == 0 && tag < 1){   //Schaltjahr
      tag = 29;
      monat--;
    }
    else if(tag < 1){
      monat--;
      if(monat < 1){
        monat = 12;
        jahr--;
      }
      tag = datum[monat-1];
    }
    if(monat < 1){
      monat = 12;
      jahr--;
    }
  }
}
