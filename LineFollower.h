#ifndef LineFollower_h
#define LineFollower_h

#include <QTRSensors.h>

/*------- PID Algorithm for Line Follower Robot using Arduino -------*/

/*------- definning PD Values -------*/

const double Kp {0.09};                  // Proportional Value.
const double Ki {0.01};                  // Integral Value.
const double Kd {1.0};                   // Derivative Value.

const int MaxSpeed {180};               // max speed of the robot
const int BaseSpeed {140};               // normal speed of the robot on the line

/*------- definning sensors properties -------*/

const uint8_t NUM_SENSORS = {6};                    // number of sensors used
uint32_t      TIMEOUT     = {2500};                 // waits for 2500 microseconds for sensor outputs to go low
uint8_t       EMITTER_PIN {QTR_NO_EMITTER_PIN};   // emitter isn't controlled by any pin.

/*------- definning outputs -------*/

constexpr uint8_t leftMotorPWM  {10};                    /* Motor driver ena pin */
constexpr uint8_t rightMotorPWM {11};                    /* Motor driver enb pin */
constexpr uint8_t leftMotor     {12};                    /* Motor driver in1 pin */
constexpr uint8_t rightMotor    {13};                    /* Motor driver in3 pin */

/*------- Sensor Output -------*/

QTRSensorsRC qtrrc( (unsigned char[]) {2, 3, 5, 6, 7, 8}, NUM_SENSORS, EMITTER_PIN, TIMEOUT);

unsigned int sensorValues[NUM_SENSORS];

/*-- we need some var to calculate motor speed using PID algorithm --*/

int error {};

double P {},
       I {},
       D {};

int previousError   {};
int motorSpeed      {},
    rightMotorSpeed {},
    leftMotorSpeed  {};

/*-- This's a func that we need calculate motor speed --*/

int calPID(int values_error) {

  P             =   double ( values_error );
  I            +=   double ( values_error );
  D             =   double ( values_error - previousError );

  motorSpeed    =   int ( ( Kp * P ) + ( Ki * I ) + ( Kd * D ) );
  previousError = values_error;

  return  motorSpeed;

}
 
 
#endif


