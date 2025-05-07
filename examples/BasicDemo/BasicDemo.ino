#include <Motor.h>

Motor motor(8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("BasicDemo Motor Library");
  motor.setVelocity(15);
  motor.setAceleration(0.5);
  motor.setDirection(1);
  motor.moveSteps(400);
}

void loop() {
  if (!motor.check()) {
    static bool dir = false;
    delay(1000);
    dir = !dir;
    motor.setDirection(dir);
    Serial.print("Moviendo 400 pasos hacia ");
    Serial.println(dir ? "derecha" : "izquierda");
    motor.moveSteps(400);
  }
}
