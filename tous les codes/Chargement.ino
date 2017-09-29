
int table[5]={0,0,0,0,0};
int compteur = 0;
int pin[5] = {2,3,4,5,6};
int generalDelay = 200;

void setup() {
  Serial.begin(9600);
  pinMode(pin[0], OUTPUT);
  pinMode(pin[1], OUTPUT);
  pinMode(pin[2], OUTPUT);
  pinMode(pin[3], OUTPUT);
  pinMode(pin[4], OUTPUT);
}

void serialEvent(){ 
  compteur = compteur + 1;
}

void loop(){
  
  if (compteur%3 == 0){
    explosion();
  }
  else if (compteur%3 == 1){
    poursuite();
  }
  else if (compteur%3 == 2){
    rebond();
  }
  
}

void explosion(){
  state0();
  delay(generalDelay);
  state21();
  delay(generalDelay);
  state22();
  delay(generalDelay);
  state5();
  delay(generalDelay);
  state23();
  delay(generalDelay);
  state24();
  delay(generalDelay);
}

void poursuite(){
  state0();
  delay(generalDelay);
  state1();
  delay(generalDelay);
  state2();
  delay(generalDelay);
  state3();
  delay(generalDelay);
  state4();
  delay(generalDelay);
  state5();
  delay(generalDelay);
  state16();
  delay(generalDelay);
  state17();
  delay(generalDelay);
  state18();
  delay(generalDelay);
  state19();
  delay(generalDelay);
}

void rebond() {
  
  state0();
  delay(generalDelay);
  state1();
  delay(generalDelay);
  state2();
  delay(generalDelay);
  state3();
  delay(generalDelay);
  state4();
  delay(generalDelay);
  state5();
  delay(generalDelay);
  state6();
  delay(generalDelay);
  state7();
  delay(generalDelay);
  state8();
  delay(generalDelay);
  state9();
  delay(generalDelay);
}

void state0(){
  digitalWrite(pin[0],LOW);
  digitalWrite(pin[1],LOW);
  digitalWrite(pin[2],LOW);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],LOW);
}

void state1(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],LOW);
  digitalWrite(pin[2],LOW);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],LOW);
}

void state2(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],LOW);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],LOW);
}

void state3(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],HIGH);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],LOW);
}

void state4(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],HIGH);
  digitalWrite(pin[3],HIGH);
  digitalWrite(pin[4],LOW);
}

void state5(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],HIGH);
  digitalWrite(pin[3],HIGH);
  digitalWrite(pin[4],HIGH);
}

void state6(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],HIGH);
  digitalWrite(pin[3],HIGH);
  digitalWrite(pin[4],LOW);
}

void state7(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],HIGH);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],LOW);
}

void state8(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],LOW);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],LOW);
}

void state9(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],LOW);
  digitalWrite(pin[2],LOW);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],LOW);
}

void state16(){
  digitalWrite(pin[0],LOW);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],HIGH);
  digitalWrite(pin[3],HIGH);
  digitalWrite(pin[4],HIGH);
}

void state17(){
  digitalWrite(pin[0],LOW);
  digitalWrite(pin[1],LOW);
  digitalWrite(pin[2],HIGH);
  digitalWrite(pin[3],HIGH);
  digitalWrite(pin[4],HIGH);
}

void state18(){
  digitalWrite(pin[0],LOW);
  digitalWrite(pin[1],LOW);
  digitalWrite(pin[2],LOW);
  digitalWrite(pin[3],HIGH);
  digitalWrite(pin[4],HIGH);
}

void state19(){
  digitalWrite(pin[0],LOW);
  digitalWrite(pin[1],LOW);
  digitalWrite(pin[2],LOW);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],HIGH);
}

void state21(){
  digitalWrite(pin[0],LOW);
  digitalWrite(pin[1],LOW);
  digitalWrite(pin[2],HIGH);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],LOW);
}

void state22(){
  digitalWrite(pin[0],LOW);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],HIGH);
  digitalWrite(pin[3],HIGH);
  digitalWrite(pin[4],LOW);
}

void state23(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],HIGH);
  digitalWrite(pin[2],LOW);
  digitalWrite(pin[3],HIGH);
  digitalWrite(pin[4],HIGH);
}

void state24(){
  digitalWrite(pin[0],HIGH);
  digitalWrite(pin[1],LOW);
  digitalWrite(pin[2],LOW);
  digitalWrite(pin[3],LOW);
  digitalWrite(pin[4],HIGH);
}


