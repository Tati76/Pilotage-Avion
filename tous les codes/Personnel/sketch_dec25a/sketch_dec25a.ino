int incomingByte = 0;
bool firstTimeNull = true;
int table[5]={0,0,0,0,0};
int compteur = 0;
int pin[5] = {2,3,4,5,6};

void setup() {
  Serial.begin(250000);
  pinMode(pin[0], OUTPUT);
  pinMode(pin[1], OUTPUT);
  pinMode(pin[2], OUTPUT);
  pinMode(pin[3], OUTPUT);
  pinMode(pin[4], OUTPUT);
}

void loop() {
      compteur = 0;
      while(Serial.available()>0){
        table[compteur]=Serial.peek();
        Serial.print ("I received: ");
        Serial.println(Serial.read(),DEC);
        compteur = compteur +1;
      }
      Serial.println("TABLE");
      Serial.print ("[ ");
      Serial.print(table[0]);
      for(int i=1; i<(sizeof(table)/sizeof(int)); i++)
      {
        Serial.print(", ");
        Serial.print(table[i]);
      }
      Serial.print(" ]");
      Serial.println("Fin");

      writepin(0);
      writepin(1);
      writepin(2);
      writepin(3); 
      writepin(4);
      delay(45);
}


void writepin(int number){
  if(table[number] <=77){
    if(table[number]-32 <= 0)
    {
      table[number] = 0 ;
    }
    analogWrite(pin[number],table[number]+32);
  }
  else{
    if(table[number]+133 >= 255)
    {
      table[number] = 255 ;
    }
    analogWrite(pin[number],table[number]+133);
  }
}

