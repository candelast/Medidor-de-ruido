//se declaran las variables
int microPin = A0;

unsigned long lastTime2 = 0;
unsigned long interval2 = 10;

const int buttonPin = 1;
const int buttonPin2 = 2;

int PinR = 4;
int PinG = 3;

int state = HIGH;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int modo = HIGH;
int buttonState2;
int lastButtonState2 = LOW;
unsigned long lastDebounceTime2 = 0;
unsigned long debounceDelay2 = 50;

int datos = 0;
int suma = 0;
int media = 0;

int umbral1 = 5;
int umbral2 = 8;
int umbral3 = 12;
int umbral4 = 17;
int umbral5 = 22;
int umbral6 = 25;
int umbral7 = 30;

int pinLed1 = 6;
int pinLed2 = 7;
int pinLed3 = 8;
int pinLed4 = 9;
int pinLed5 = 10;
int pinLed6 = 11;
int pinLed7 = 12;
int pinLed8 = 13;

const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int val = 0;

void setup()
{
  for (int i = 6; i < 14; i++) {
    pinMode (i, OUTPUT);
  }
  Serial.begin(9600);
  pinMode(PinG, OUTPUT);
  pinMode(PinR, OUTPUT);
  pinMode(buttonPin, INPUT);
  analogReference(EXTERNAL);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop()
{
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        state = !state;
      }
    }
  }
  if (state == LOW) {
   apagado();
   Serial.println ("state LOW");
  }
  if (state == HIGH) {
    Serial.println("state HIGH");
    //PULSADOR MODO
    pulsador();
    //SMOOTHING
    smoothing();
    //MEDIA
    unsigned long currentTime2 = millis();
    if (currentTime2 - lastTime2 >= interval2) {
      lastTime2 = currentTime2;
      Serial.print(val); //se imprimn los valores instantáneos
      Serial.print("\t"); //se añade un tabulador para crear dos gráficas
      Serial.println(media); //se imprime la media
      suma = val + suma;
      datos++;
      //MEDIA LARGA
      if (datos >= 100) {
        media = suma / datos;
        datos = 0;
        suma = 0;
        encenderleds();
      }
    }
  }
  lastButtonState = reading;
}

void pulsador() {
  int reading2 = digitalRead(buttonPin2);
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();
  }
  if ((millis() - lastDebounceTime2) > debounceDelay2) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == HIGH) {
        modo = !modo;
      }
    }
  }
  if (modo == LOW) {
    umbral1 = 1;
    umbral2 = 3;
    umbral3 = 5;
    umbral4 = 8;
    umbral5 = 12;
    umbral6 = 15;
    umbral7 = 18;
    Serial.println("modo LOW");
    digitalWrite(PinR, HIGH);
    digitalWrite(PinG, LOW);
  }
  if (modo == HIGH) {
    umbral1 = 5;
    umbral2 = 8;
    umbral3 = 12;
    umbral4 = 17;
    umbral5 = 22;
    umbral6 = 25;
    umbral7 = 30;
    Serial.println("modo HIGH");
    digitalWrite(PinR, LOW);
    digitalWrite(PinG, HIGH);
  }
  lastButtonState2 = reading2;
}

void smoothing() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(microPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  val = total / numReadings;
  delay(1);        // delay in between reads for stability
}

void encenderleds() {
  if (media < umbral1) {
    Serial.println("Nivel 1");
    digitalWrite (pinLed1, HIGH);
    digitalWrite (pinLed2, LOW);
    digitalWrite (pinLed3, LOW);
    digitalWrite (pinLed4, LOW);
    digitalWrite (pinLed5, LOW);
    digitalWrite (pinLed6, LOW);
    digitalWrite (pinLed7, LOW);
    digitalWrite (pinLed8, LOW);
  }
  else if (media < umbral2) {
    Serial.println("Nivel 2");
    digitalWrite (pinLed1, HIGH);
    digitalWrite (pinLed2, HIGH);
    digitalWrite (pinLed3, LOW);
    digitalWrite (pinLed4, LOW);
    digitalWrite (pinLed5, LOW);
    digitalWrite (pinLed6, LOW);
    digitalWrite (pinLed7, LOW);
    digitalWrite (pinLed8, LOW);
  }
  else if (media < umbral3) {
    Serial.println("Nivel 3");
    digitalWrite (pinLed1, HIGH);
    digitalWrite (pinLed2, HIGH);
    digitalWrite (pinLed3, HIGH);
    digitalWrite (pinLed4, LOW);
    digitalWrite (pinLed5, LOW);
    digitalWrite (pinLed6, LOW);
    digitalWrite (pinLed7, LOW);
    digitalWrite (pinLed8, LOW);
  }
  else if (media < umbral4) {
    Serial.println("Nivel 4");
    digitalWrite (pinLed1, HIGH);
    digitalWrite (pinLed2, HIGH);
    digitalWrite (pinLed3, HIGH);
    digitalWrite (pinLed4, HIGH);
    digitalWrite (pinLed5, LOW);
    digitalWrite (pinLed6, LOW);
    digitalWrite (pinLed7, LOW);
    digitalWrite (pinLed8, LOW);
  }
  else if (media < umbral5) {
    Serial.println("Nivel 5");
    digitalWrite (pinLed1, HIGH);
    digitalWrite (pinLed2, HIGH);
    digitalWrite (pinLed3, HIGH);
    digitalWrite (pinLed4, HIGH);
    digitalWrite (pinLed5, HIGH);
    digitalWrite (pinLed6, LOW);
    digitalWrite (pinLed7, LOW);
    digitalWrite (pinLed8, LOW);
  }
  else if (media < umbral6) {
    Serial.println("Nivel 6");
    digitalWrite (pinLed1, HIGH);
    digitalWrite (pinLed2, HIGH);
    digitalWrite (pinLed3, HIGH);
    digitalWrite (pinLed4, HIGH);
    digitalWrite (pinLed5, HIGH);
    digitalWrite (pinLed6, HIGH);
    digitalWrite (pinLed7, LOW);
    digitalWrite (pinLed8, LOW);
  }
  else if (media < umbral7) {
    Serial.println("Nivel 7");
    digitalWrite (pinLed1, HIGH);
    digitalWrite (pinLed2, HIGH);
    digitalWrite (pinLed3, HIGH);
    digitalWrite (pinLed4, HIGH);
    digitalWrite (pinLed5, HIGH);
    digitalWrite (pinLed6, HIGH);
    digitalWrite (pinLed7, HIGH);
    digitalWrite (pinLed8, LOW);
  }
  else {
    Serial.println("Nivel 8");
    digitalWrite (pinLed1, HIGH);
    digitalWrite (pinLed2, HIGH);
    digitalWrite (pinLed3, HIGH);
    digitalWrite (pinLed4, HIGH);
    digitalWrite (pinLed5, HIGH);
    digitalWrite (pinLed6, HIGH);
    digitalWrite (pinLed7, HIGH);
    digitalWrite (pinLed8, HIGH);
  }
}

void apagado() {
  digitalWrite (PinR, LOW);
  digitalWrite (PinG, LOW);
  digitalWrite (pinLed1, LOW);
  digitalWrite (pinLed2, LOW);
  digitalWrite (pinLed3, LOW);
  digitalWrite (pinLed4, LOW);
  digitalWrite (pinLed5, LOW);
  digitalWrite (pinLed6, LOW);
  digitalWrite (pinLed7, LOW);
  digitalWrite (pinLed8, LOW);
}
