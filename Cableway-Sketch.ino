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

#define STEPPER1_ENABLE A1
#define STEPPER2_ENABLE A2
#define STEPPER3_ENABLE A3

// DOWN MOTORS //

// UP MOTORS //
#define MOTOR4_IN1 48
#define MOTOR4_IN2 49

#define MOTOR5_IN1 50
#define MOTOR5_IN2 51

#define MOTOR6_IN1 52
#define MOTOR6_IN2 53
// UP MOTORS //

void setup() {    
  bluetooth.begin(9600);
  Serial.begin(9600);

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
  
  digitalWrite(MOTOR4_IN1, LOW);
  digitalWrite(MOTOR4_IN2, LOW);
  digitalWrite(MOTOR5_IN1, LOW);
  digitalWrite(MOTOR5_IN2, LOW);
  digitalWrite(MOTOR6_IN1, LOW);
  digitalWrite(MOTOR6_IN2, LOW);
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
                                STEPPER1.move(-DISTANCE);
                                break;
                            }
                            case 2: {
                                STEPPER2.move(-DISTANCE);
                                break;
                            }
                            case 3: {
                                STEPPER3.move(-DISTANCE);
                                break;
                            }
                        }
                    }
                    else {
                        switch(mNumber) {
                            case 1: {
                                STEPPER1.move(DISTANCE);
                                break;
                            }
                            case 2: {
                                STEPPER2.move(DISTANCE);
                                break;
                            }
                            case 3: {
                                STEPPER3.move(DISTANCE);
                                break;
                            }
                        }
                    }
                } else {
                  switch(mNumber) {
                            case 1: {
                                STEPPER1.move(0);
                                break;
                            }
                            case 2: {
                                STEPPER2.move(0);
                                break;
                            }
                            case 3: {
                                STEPPER3.move(0);
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
