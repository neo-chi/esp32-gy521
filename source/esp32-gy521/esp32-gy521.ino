/* FILE: esp32-gy521.ino
 * DESC: Interfaces ESP32 with GY521 and displays data to serial monitor.
 * AUTH: Reece Chimento
 * DATE: 01/25/2020
 *
 * REVISION HISTORY
 */
#include <Wire.h>

#define MPU6050   0x68 // MPU6050 slave address for I2C communication
#define PWR_MAN_1 ((unsigned char) 0x6B)
#define WAKE_UP   ((unsigned char) 0x00)

// X Acceleration memory location 
#define ACCEL_X_H (unsigned char) 0x3B
#define ACCEL_X_L (unsigned char) 0x3C

// Y Acceleration memory location
#define ACCEL_Y_H ((unsigned char) 0x3D)
#define ACCEL_Y_L ((unsigned char) 0x3E)

// Z Acceleration memory location
#define ACCEL_Z_H (unsigned char) 0x3F
#define ACCEL_Z_L (unsigned char) 0x40

// Function Prototypes
bool initialize_accelerometer();
void read_accelerometer();

int16_t acceleration = 1337;


void setup()
{
   Serial.begin(115200);
   initialize_accelerometer();
}


void loop()
{
   Serial.print("Y Acceleration: ");
   read_accelerometer();
   Serial.println(acceleration);
   delay(1000);
}

bool initialize_accelerometer()
{
   Wire.begin();                    // Join I2C bus as master.
   Wire.beginTransmission(MPU6050); // Begin a communication with MPU6050.
   Wire.write(PWR_MAN_1);           // Prepare to write to MPU6050 Power Management 1 Register.
   Wire.write(WAKE_UP);             // Write binary 0 to the power management register to wake up the MPU6050.
   Wire.endTransmission();          // Send the message and release the I2C bus.

   return true;
}

void read_accelerometer()
{
   // Move the MPU6050 stack pointer to the Y Acceleration Output Register.
   Wire.beginTransmission(MPU6050); // Begin a communication with MPU6050.
   Wire.write(ACCEL_Y_H);           // Move the MPU6050 pointer to the Y Acceleration Out High Register.
   Wire.endTransmission();          // Send the message and release the I2C bus.

   // Read 2 Bytes from the MPU6050. These two bytes will result in the Y Acceleration Output.
   Wire.beginTransmission(MPU6050); // Begin a communication with MPU6050.
   Wire.requestFrom(MPU6050, 2);    // Request 2 bits from the MPU6050.

   // Shift the first byte (high byte) left 8 bits, then read in the last byte.
   acceleration = Wire.read()<<8|(Wire.read());
}
