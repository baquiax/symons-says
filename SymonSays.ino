/* PINES DE ENTRADA
 * [2-6] pines de entrada (push-button), 2 = start
 * [23] potenciometro (Velocidad).
 * [24-27] pines de salidas para LEDs
 * Pin 40 Salida Analoga para bocina 
 */
 
const int potentiometerPin = 23;
const int buzzerPin = 40; 

const int startPin = 2;
const int firstLed = 24;
const int secondLed = 25;
const int thirdLed = 26;
const int fourthLed = 27;

const int sequencesByLevel = 5;

boolean started;
boolean waitingForUser = false;
int sequences[sequencesByLevel][10];
int currentLevel = 1;
int currentSequenceElement = 0;

void setup(){
  //Preparando pines de entrada. Push buttons
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  
  //Preparando pines de salida, LEDs
  pinMode(firstLed, OUTPUT);
  pinMode(secondLed, OUTPUT);
  pinMode(thirdLed, OUTPUT);
  pinMode(fourthLed, OUTPUT);
 
  Serial.begin(9600);
 randomSeed(4);   
}

void nextSequence() {
  //La secuencia se crea en base a el nivel
  for (int i = 0 ; i < sequencesByLevel ; i++) {
    int nS = 2 + ((currentLevel > 2) ? (currentLevel + 3) : currentLevel);
    for (int j = 0; j < nS ; j++) {
        sequences[i][j] = random(1,5);
    }
  }
}

void showCurrentSequence() {
    for (int i = 0; i < 10 ; i++) {
      int value = sequences[currentLevel - 1][i];
      if (value == 0)
        return;
      
      int pin;
      switch (value) {
        case 1:
          pin = firstLed;
          break;
        case 2:
          pin = secondLed;
          break;
        case 3:
          pin = thirdLed;
          break;
        case 4:
          pin = fourthLed;
          break;          
      }
      digitalWrite(pin, HIGH);
      Serial.println(value);
      delay(220);
      digitalWrite(pin, LOW);
      delay(100);
    }
}

void verifyInput(){
  
}

void loop(){
  Serial.println("LOOP");
  if (started) {
    if (!waitingForUser) {
      Serial.println("Encender Leds");
      showCurrentSequence();
    } else {
      verifyInput();
    }
  } else {
    if (digitalRead(startPin) == LOW) {
      Serial.println("Started");
      started = true;
      nextSequence();
    }
  }
}
