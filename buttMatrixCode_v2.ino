#include <Adafruit_NeoPixel.h>

//

Adafruit_NeoPixel strip = Adafruit_NeoPixel(18, 5, NEO_GRB + NEO_KHZ800);

char columnPins[] = {10, 16, 15, 14, 21, 7, 6, 8, 9};
char rowPins[] = {4, 18};

char topRow[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
char bottomRow[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

//funcs
void startupAnimation();
int updateButts();
void randomDisplay();

void setup() {
  //start serial communication & LEDS
  Serial.begin(9600);
  strip.begin();
  strip.show();
  
  //startupAnimation();
  
  //pin definitons
  for(int i = 0; i < 9; i++){
    pinMode(columnPins[i], OUTPUT);
  }
  pinMode(4, INPUT);
  pinMode(18, INPUT);
}


void loop() {
  //fill arrays with butt states, shows user input is recognized
  updateButts();
  illuminatePressed();
  
  
  if(topRow[4] && bottomRow[3] && bottomRow[5]){
    randomDisplay();
  }
  
  //DEBUGGING ESCAPE LOOP
  while(topRow[0] && topRow[8] && topRow[4] && bottomRow[0] && bottomRow[8] && bottomRow[4]){
    //escape loop for debugging
  }
}

void randomDisplay(){
  //fill random pixel array
  randomSeed(analogRead(20));
  int rgb[100][4];
  for(int i = 0; i <= 100; i++){
    rgb[i][0] = random(0, 18);
    for(int j = 1; j < 4; j++){
      rgb[i][j] = random(0, 200);
    }
  }
  
  for(int i = 0; i <= 100; i++){
    strip.setPixelColor(rgb[i][0], rgb[i][1], rgb[i][2], rgb[i][3]);
    strip.show();
    delay(200);
    updateButts();
    if(topRow[4] && bottomRow[3] && bottomRow[5]){
      delay(500);
      break;
    }
  }
}

int updateButts(){
  int pressed = 0;
  for(int j = 0; j < 9; j++){
    for(int i = 0; i < 9; i++){
      if(i != j){
        digitalWrite(columnPins[i], LOW);
      }
      else
        digitalWrite(columnPins[i], HIGH);
    }
    
    if(digitalRead(4)){
      topRow[j] = 1;
      pressed = 1;
    }
    else topRow[j] = 0;
    
    if(digitalRead(18)){
      bottomRow[j] = 1;
      pressed = 1;
    }
    else bottomRow[j] = 0;
  }

  return pressed;
}

void illuminatePressed(){
  for(int i = 0; i < 9; i++){
    if(topRow[i]){
      Serial.print("Button pressed at top column, row: ");
      Serial.println(i);
      strip.setPixelColor(8-i, 100, 0, 240);
    }
    else{strip.setPixelColor(8-i, 5, 5, 5);}
    
    if(bottomRow[i]){
      Serial.print("Button pressed at bottom column, row: ");
      Serial.println(i);  
      strip.setPixelColor(9+i, 100, 0, 240);
    }
    else{strip.setPixelColor(9+i, 5, 5, 5);}
    
    strip.show();
  }
}

void startupAnimation(){
  for(int j = 0; j < 70; j++){
    for(int i = 0; i < 18; i++){
      strip.setPixelColor(i, j, 0, 0);
    }
    strip.show();
    delay(20);
  }
  
  for(int j = 0; j < 70; j++){
    for(int i = 0; i < 18; i++){
      strip.setPixelColor(i, 0, j, 0);
    }
    strip.show();
    delay(20);
  }
  
  for(int j = 0; j < 70; j++){
    for(int i = 0; i < 18; i++){
      strip.setPixelColor(i, 0, 0, j);
    }
    strip.show();
    delay(20);
  }
  
  for(int j = 0; j < 160; j++){
    for(int i = 0; i < 18; i++){
      strip.setPixelColor(i, j, j, j);
    }
    strip.show();
    delay(20);
  }
}

