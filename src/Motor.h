#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  private:
    int steps         = 1;
    int direction     = 1;
    int velocity      = 0;
    float aceleration = 0.1;
    bool status       = 0;

    uint8_t pinA, pinB, pinC, pinD;
    static const int STEPS_PER_REV = 512;
    int stepsToDo        = 0;
    int executedSteps    = 0;
    int rampSteps        = 0;
    int currentStepIndex = 0;
    unsigned long lastStepTime = 0;
    float stepInterval       = 0;

    static const int SEQ_SIZE = 4;
    const uint8_t seq[SEQ_SIZE][4] = {
      {1,0,1,0},
      {0,1,1,0},
      {0,1,0,1},
      {1,0,0,1}
    };

  public:
    Motor(uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD);
    void setVelocity(int vel);
    int  getVelocity() const;
    void setDirection(int dir);
    int  getDirection() const;
    void setAceleration(float a);
    float getAceleration() const;
    void moveSteps(int steps);
    void moveContinous();
    void stop();
    bool check();
};

#endif  // MOTOR_H
