#include "Motor.h"
#include <Arduino.h>

Motor::Motor(uint8_t pA, uint8_t pB, uint8_t pC, uint8_t pD)
  : pinA(pA), pinB(pB), pinC(pC), pinD(pD)
{
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
}

void Motor::setVelocity(int vel) { velocity = vel; }
int Motor::getVelocity() const    { return velocity; }

void Motor::setDirection(int dir) { direction = dir ? 1 : 0; }
int Motor::getDirection() const   { return direction; }

void Motor::setAceleration(float a) { aceleration = a; }
float Motor::getAceleration() const  { return aceleration; }

void Motor::moveSteps(int s) {
  stepsToDo     = s;
  executedSteps = 0;
  float v_sps   = velocity * STEPS_PER_REV / 60.0;
  float acc_p   = 0.5 * v_sps * aceleration;
  rampSteps     = int(acc_p + 0.5);
  if (rampSteps * 2 > stepsToDo) rampSteps = stepsToDo / 2;
  currentStepIndex = 0;
  lastStepTime     = micros();
  status           = true;
}

void Motor::moveContinous() {
  stepsToDo     = -1;
  executedSteps = 0;
  float v_sps   = velocity * STEPS_PER_REV / 60.0;
  float acc_p   = 0.5 * v_sps * aceleration;
  rampSteps     = int(acc_p + 0.5);
  currentStepIndex = 0;
  lastStepTime     = micros();
  status           = true;
}

void Motor::stop() {
  if (status && stepsToDo < 0) {
    stepsToDo = executedSteps + rampSteps;
  }
}

bool Motor::check() {
  if (!status) return false;
  unsigned long now = micros();
  float v_sps     = velocity * STEPS_PER_REV / 60.0;
  float periodMin = 1000000.0 / v_sps;

  if (stepsToDo >= 0) {
    if (executedSteps < rampSteps) {
      stepInterval = periodMin * (1.0 + float(rampSteps - executedSteps) / rampSteps);
    }
    else if (executedSteps >= stepsToDo - rampSteps) {
      int decelStep = executedSteps - (stepsToDo - rampSteps);
      stepInterval  = periodMin * (1.0 + float(decelStep) / rampSteps);
    }
    else {
      stepInterval = periodMin;
    }
  } else {
    if (executedSteps < rampSteps) {
      stepInterval = periodMin * (1.0 + float(rampSteps - executedSteps) / rampSteps);
    } else {
      stepInterval = periodMin;
    }
  }

  if (now - lastStepTime >= stepInterval) {
    lastStepTime = now;
    digitalWrite(pinA, seq[currentStepIndex][0]);
    digitalWrite(pinB, seq[currentStepIndex][1]);
    digitalWrite(pinC, seq[currentStepIndex][2]);
    digitalWrite(pinD, seq[currentStepIndex][3]);
    if (direction == 1) {
      currentStepIndex = (currentStepIndex + 1) % SEQ_SIZE;
    } else {
      currentStepIndex = (currentStepIndex + SEQ_SIZE - 1) % SEQ_SIZE;
    }
    executedSteps++;
    if (stepsToDo >= 0 && executedSteps >= stepsToDo) {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      status = false;
      return false;
    }
  }
  return true;
}
