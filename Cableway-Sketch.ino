#include <SoftwareSerial.h>
#include <AccelStepper.h>

SoftwareSerial bluetooth(11, 10);

#define COMMAND_MIN_LENGTH 3
#define MOTOR_DIRECTION 0
#define MOTOR_NUMBER 1
#define MOTOR_SPEED 2

#define DISTANCE 12000 
#define STEPPER_MAX_SPEED 1000
#define STEPPER_ACCELERATION 2000

// DOWN MOTORS //

AccelStepper STEPPER1(1, 2, 3); // (Driver, Step, Direction)
AccelStepper STEPPER2(1, 4, 5);
AccelStepper STEPPER3(1, 6, 7);

#define STEPPER1_ENABLE A0
#define STEPPER2_ENABLE A1
#define STEPPER3_ENABLE A2

// DOWN MOTORS //

// UP MOTORS //
#define MOTOR4_IN1 34
#define MOTOR4_IN2 35

#define MOTOR5_IN1 36
#define MOTOR5_IN2 37

#define MOTOR6_IN1 38
#define MOTOR6_IN2 39
// UP MOTORS //

void beep(int ton, int time)
{
  tone(46, ton, time);
  delay(time + 20);
}

void play()
{
const int speakerPin = 46;

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
  
    noTone(speakerPin);
    beep(a, 500);
    beep(a, 500);
    beep(a, 500);
    beep(f, 350);
    beep(cH, 150);
    beep(a, 500);
    beep(f, 350);
    beep(cH, 150);
    beep(a, 650);

    delay(150);


    beep(eH, 500);
    beep(eH, 500);
    beep(eH, 500);
    beep(fH, 350);
    beep(cH, 150);
    beep(gS, 500);
    beep(f, 350);
    beep(cH, 150);
    beep(a, 650);

    noTone(speakerPin);  // Отключаем спикер
    delay(10); // Задержка в мс после которой цикл повторится по новой
}

void setup() {    
  bluetooth.begin(9600);
  Serial.begin(9600);

  play();

  STEPPER1.setMaxSpeed(STEPPER_MAX_SPEED);
  STEPPER1.setAcceleration(STEPPER_ACCELERATION);

  STEPPER2.setMaxSpeed(STEPPER_MAX_SPEED);
  STEPPER2.setAcceleration(STEPPER_ACCELERATION);
  
  STEPPER3.setMaxSpeed(STEPPER_MAX_SPEED);
  STEPPER3.setAcceleration(STEPPER_ACCELERATION);
  
  pinMode(MOTOR4_IN1, OUTPUT);
  pinMode(MOTOR4_IN2, OUTPUT);
  pinMode(MOTOR5_IN1, OUTPUT);
  pinMode(MOTOR5_IN2, OUTPUT);
  pinMode(MOTOR6_IN1, OUTPUT);
  pinMode(MOTOR6_IN2, OUTPUT);
  
  pinMode(STEPPER1_ENABLE, OUTPUT);
  pinMode(STEPPER2_ENABLE, OUTPUT);
  pinMode(STEPPER3_ENABLE, OUTPUT);
  
  digitalWrite(MOTOR4_IN1, LOW);
  digitalWrite(MOTOR4_IN2, LOW);
  digitalWrite(MOTOR5_IN1, LOW);
  digitalWrite(MOTOR5_IN2, LOW);
  digitalWrite(MOTOR6_IN1, LOW);
  digitalWrite(MOTOR6_IN2, LOW);

  digitalWrite(STEPPER1_ENABLE, HIGH);
  digitalWrite(STEPPER2_ENABLE, HIGH);
  digitalWrite(STEPPER3_ENABLE, HIGH);
}

void loop() {
    String command = ""; 
    //  +-: Direction
    //  1: Number Motor
    //  2: Speed (It does not matter how much symbols)
    
    if (bluetooth.available()) {
        while (bluetooth.available()) {
          //Read Command
          command += (char) bluetooth.read();
          
          Serial.println("Input: " + command[command.length()-1]);
          Serial.println("Command: " + command);
      
          command.trim();
        }

        if (command.length() >= COMMAND_MIN_LENGTH) {
            int mNumber = command[MOTOR_NUMBER] - '0';
            char direct = command[MOTOR_DIRECTION];
            int mSpeed = (command.substring(MOTOR_SPEED, command.length())).toInt();
            
            if (mNumber > 0 && mNumber <= 3) {
                if (mSpeed != 0) {
                    if (direct == '-') {
                        switch(mNumber) {
                            case 1: {
                                digitalWrite(STEPPER1_ENABLE, LOW);
                                STEPPER1.move(-DISTANCE);
                                break;
                            }
                            case 2: {
                                digitalWrite(STEPPER2_ENABLE, LOW);
                                STEPPER2.move(-DISTANCE);
                                break;
                            }
                            case 3: {
                                digitalWrite(STEPPER3_ENABLE, LOW);
                                STEPPER3.move(-DISTANCE);
                                break;
                            }
                        }
                    }
                    else {
                        switch(mNumber) {
                            case 1: {
                                digitalWrite(STEPPER1_ENABLE, LOW);
                                STEPPER1.move(DISTANCE);
                                break;
                            }
                            case 2: {
                                digitalWrite(STEPPER2_ENABLE, LOW);
                                STEPPER2.move(DISTANCE);
                                break;
                            }
                            case 3: {
                                digitalWrite(STEPPER3_ENABLE, LOW);
                                STEPPER3.move(DISTANCE);
                                break;
                            }
                        }
                    }
                } else {
                  switch(mNumber) {
                            case 1: {
                                digitalWrite(STEPPER1_ENABLE, HIGH);
                                break;
                            }
                            case 2: {
                                digitalWrite(STEPPER3_ENABLE, HIGH);
                                break;
                            }
                            case 3: {
                                digitalWrite(STEPPER3_ENABLE, HIGH);
                                break;
                            }
                        }
                }
                Serial.println("Speed");
                Serial.println(mSpeed);
                Serial.println("Motor");
                Serial.println(mNumber);
            } else if (mNumber > 3) {
              if (mSpeed != 0) {
                    if (direct == '-') {
                        digitalWrite(MOTOR4_IN1, LOW);
                        digitalWrite(MOTOR4_IN2, HIGH);
                        digitalWrite(MOTOR5_IN1, LOW);
                        digitalWrite(MOTOR5_IN2, HIGH);
                        digitalWrite(MOTOR6_IN1, LOW);
                        digitalWrite(MOTOR6_IN2, HIGH);
                    } else {
                        digitalWrite(MOTOR4_IN1, HIGH);
                        digitalWrite(MOTOR4_IN2, LOW);
                        digitalWrite(MOTOR5_IN1, HIGH);
                        digitalWrite(MOTOR5_IN2, LOW);
                        digitalWrite(MOTOR6_IN1, HIGH);
                        digitalWrite(MOTOR6_IN2, LOW);
                    }
              } else {
                  digitalWrite(MOTOR4_IN1, LOW);
                  digitalWrite(MOTOR4_IN2, LOW);
                  digitalWrite(MOTOR5_IN1, LOW);
                  digitalWrite(MOTOR5_IN2, LOW);
                  digitalWrite(MOTOR6_IN1, LOW);
                  digitalWrite(MOTOR6_IN2, LOW);
              }
              
            }
            Serial.println("Speed");
            Serial.println(mSpeed);
            Serial.println("Motor");
            Serial.println(mNumber);
        } else {
            Serial.println("TOO SHORT COMMAND!");
        }
    }
    STEPPER1.run();
    STEPPER2.run();
    STEPPER3.run();
}
