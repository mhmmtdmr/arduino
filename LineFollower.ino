#include "LineFollower.h" //header file is including some defines.

int main() {
  /*------- Arduino pin outputs -------*/

  /*------- L298P Motor Driver Shield -------*/

  pinMode(rightMotor    , OUTPUT);
  pinMode(rightMotorPWM , OUTPUT);
  pinMode(leftMotor     , OUTPUT);
  pinMode(leftMotorPWM  , OUTPUT);

  Serial.begin( 9600 );
  delay ( 1000 );

  digitalWrite ( rightMotor    , LOW );
  analogWrite  ( rightMotorPWM , 0   );
  digitalWrite ( leftMotor     , LOW );
  analogWrite  ( leftMotorPWM  , 0   );

  while ( true ) {
    /*------- Sensor line position -------*/
    unsigned int position = qtrrc.readLine ( sensorValues );

    /*--- Sensor Error ---*/
    error =  int( ( position - 2500 ) );

    /*------- Calculate PID Motor Speed-------*/
    motorSpeed = calPID ( error );

    rightMotorSpeed   =   BaseSpeed + motorSpeed;
    leftMotorSpeed    =   BaseSpeed - motorSpeed;

    if ( rightMotorSpeed > MaxSpeed ) {
      rightMotorSpeed = MaxSpeed;
    } // prevent the motor from going beyond max speed

    if ( leftMotorSpeed > MaxSpeed ) {
      leftMotorSpeed = MaxSpeed;
    } // prevent the motor from going beyond max speed

    if ( rightMotorSpeed < 0 ) {
      rightMotorSpeed = -MaxSpeed;
    } // keep the motor speed positive

    if ( leftMotorSpeed < 0 ) {
      leftMotorSpeed = -MaxSpeed;
    } // keep the motor speed positive

    digitalWrite(rightMotor, HIGH);
    analogWrite(rightMotorPWM, rightMotorSpeed);
    digitalWrite(leftMotor, HIGH);
    analogWrite(leftMotorPWM, leftMotorSpeed);

  }

  return 0;

}


