/* FILE: esp32-gy521.ino
 * DESC: Interfaces ESP32 with GY521 and displays data to serial monitor.
 * AUTH: Reece Chimento
 * DATE: 01/24/2020
 *
 * REVISION HISTORY
 */

#define LED 23

/* void setup()
 * Initializes and verfies the accelerometer control registers.
 * Configures the ESP32 pins for input and output. 
 */
void setup()
{
   pinMode(LED, OUTPUT); // Verify ESP32 works with arduino code. Configure pin 23 to output.
}


void loop()
{
   // Verify ESP32 works with arduino code. Blink an LED every half second.
   delay(500);
   digitalWrite(LED, HIGH);
   delay(500);
   digitalWrite(LED, LOW);
}
