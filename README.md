# Motor Library

Motor es una librería Arduino para controlar el motor paso a paso 28BYJ-48 junto con el módulo ULN2003, soportando aceleración y deceleración suaves.

## Instalación

1. Descarga o clona este repositorio.
2. Copia la carpeta `Motor` en tu directorio de librerías de Arduino (usualmente `~/Arduino/libraries`).
3. Reinicia el IDE de Arduino.
4. Incluye la librería en tu sketch con `#include <Motor.h>`.

## Uso

- Crea una instancia:
  ```cpp
  Motor motor(8, 9, 10, 11);
  ```
- Configura velocidad y aceleración:
  ```cpp
  motor.setVelocity(15);      // rpm
  motor.setAceleration(0.5);  // segundos
  ```
- Mueve un número de pasos:
  ```cpp
  motor.moveSteps(400);
  ```
- En tu `loop()` llama:
  ```cpp
  if (!motor.check()) {
    // movimiento terminado
  }
  ```

Consulta el ejemplo en `examples/BasicDemo/BasicDemo.ino`.
