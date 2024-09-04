#define redPin 9 //PWM pinovi
#define greenPin 10
#define bluePin 11
#define tasterPin 2 //interrupt pin za taster

volatile bool flag=false; //‘volatile’ jer se njena vrednost menja u vise funkcija

const int brightness=122; //jacina kojom svetle LED
int index=0; //indeks boje koja se trenutno prikazuje na RGB, indeks plave boje je 0, žute je 1, ljubicaste je 2 i tirkizne je 3

void setup() {
pinMode(redPin,OUTPUT); //svi LED pinovi se deklarisu kao izlazni
pinMode(greenPin,OUTPUT);
pinMode(bluePin,OUTPUT);
pinMode(tasterPin,INPUT); //taster pin je deklarisan kao ulazni
attachInterrupt(digitalPinToInterrupt(tasterPin),tasterISR,RISING); //deklarisanje prekida na taster pinu, funkcije koja se poziva pri prekidu kada je prisutna rastuca ivica signala (zbog pull-down otpornika)
}

void loop() {
//svakim pritiskom tastera, indeks se inkrementira, kada stigne do vrednosti 4, vraca se na 0
if(flag) { 
  index++;
  if(index==4)
    index=0;
  flag=false;
}
if(index == 0) 
  applyColor(0,0,brightness);
else if(index == 1)
  applyColor(brightness,brightness,0);
else if(index == 2)
  applyColor(brightness,0,brightness);
else
  applyColor(0,brightness,brightness);
}

void tasterISR() {
  flag=true;
}

void applyColor(int R, int G, int B) { //funkcija za prikaz boje na RGB diodi
  analogWrite(redPin,R);
  analogWrite(greenPin,G);
  analogWrite(bluePin,B);
}
