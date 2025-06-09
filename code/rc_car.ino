#include <IRremote.h>

const int controlPin1 = 2;
const int controlPin2 = 3;
const int controlPin3 = 10;
const int controlPin4 = 12;
const int enablePin = 9;
const int enablePin2 = 11;

// IR Receiver pin
const int IR_RECEIVE_PIN = 8;
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start IR reciever

  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(controlPin3, OUTPUT);
  pinMode(controlPin4, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  digitalWrite(enablePin, LOW);
  digitalWrite(enablePin2, LOW);
}

// Movement functions
void forward() {
  digitalWrite(controlPin1, HIGH);
  digitalWrite(controlPin2, LOW);
  digitalWrite(controlPin3, HIGH);
  digitalWrite(controlPin4, LOW);
  Serial.println("Forward");
}

void backward() {
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, HIGH);
  digitalWrite(controlPin3, LOW);
  digitalWrite(controlPin4, HIGH);
  Serial.println("Back");
}

void right() {
  digitalWrite(controlPin1, HIGH);
  digitalWrite(controlPin2, LOW);
  digitalWrite(controlPin3, LOW);
  digitalWrite(controlPin4, LOW);
  Serial.println("Right");
}

void left() {
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);
  digitalWrite(controlPin3, HIGH);
  digitalWrite(controlPin4, LOW);
  Serial.println("Left");
}

void stopMotors() {
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);
  digitalWrite(controlPin3, LOW);
  digitalWrite(controlPin4, LOW);
  Serial.println("Stop");
}

void motorEnable() {
  analogWrite(enablePin, 60);
  analogWrite(enablePin2, 60);
}

void loop() {
  motorEnable();

  if (irrecv.decode(&results)) {
    Serial.print("Received IR code: ");
    Serial.println(results.value, HEX);

    switch (results.value) {
      case 0xFFA25D: //Power button
        stopMotors();
        break;
      case 0xFF629D: //Up
        forward();
        break;
      case 0xFFA857: //Down
        backward();
        break;
      case 0xFF22DD: //Left
        left();
        break;
      case 0xFFC23D: //right
        right();
        break;
      default:
        stopMotors(); // Default fallback
        break;
    }

    irrecv.resume(); //wiat for new signal
  }
}

