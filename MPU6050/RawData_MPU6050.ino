/*
   Interfacing Triple Axis Accelerometer and Gyro Breakout MPU6050 with Arduino
   Mayoogh Girish, https://mgprojecthub.com
   Article : http://mgprojecthub.com/interfacing-triple-axis-accelerometer-and-gyro-breakout-mpu6050-with-arduino/
   
*/

#include<Wire.h>                                        // Wiew library for I2C communication 
#define MPU6050_register 0x68                           // I2C address of the MPU-6050.

int16_t accelerometerX,accelerometerY,accelerometerZ;   // Variable for acceleometer raw values
int16_t gyroX,gyroY,gyroZ;                              // Variable for gyroscope raw values
int16_t temperature;                                    // Variable for temperature 

void setup(){
  Wire.begin();                                         // Initialize communication
  Wire.beginTransmission(MPU6050_register);             // Begin I2C communication
  Wire.write(0x6B);                                     // PWR_MGMT_1 Register [https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf]
  Wire.write(0);                                        // Place 0 to the 6B register, wakes up the MPU6050
  Wire.endTransmission(true);
  Serial.begin(115200);
}
void loop(){
  Wire.beginTransmission(MPU6050_register);             
  Wire.write(0x3B);                                     // Begin with register 0x3B (ACCEL_XOUT_H) [https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf]
                                                        // MPU-6050 Register Map and Descriptions Revision 4.2 - Page 7
  Wire.endTransmission(false);                          // will send a restart, keeping the connection active.
  Wire.requestFrom(MPU6050_register,14,true);           // Request 14 registers. [7*2=14]. Value for each axis is stored in 2 bytes. 3 Acceleromter + 3 Gyro + 1 Temperature
  
  accelerometerX=Wire.read()<<8|Wire.read();            // Registers 0x3B (ACCEL_XOUT_H) + 0x3C (ACCEL_XOUT_L)
  accelerometerY=Wire.read()<<8|Wire.read();            // Registers 0x3D (ACCEL_YOUT_H) + 0x3E (ACCEL_YOUT_L)
  accelerometerZ=Wire.read()<<8|Wire.read();            // Registers 0x3F (ACCEL_ZOUT_H) + 0x40 (ACCEL_ZOUT_L)
  temperature=Wire.read()<<8|Wire.read();               // Registers 0x41 (TEMP_OUT_H)  + 0x42 (TEMP_OUT_L)
  gyroX=Wire.read()<<8|Wire.read();                     // Registers 0x43 (GYRO_XOUT_H) + 0x44 (GYRO_XOUT_L)
  gyroY=Wire.read()<<8|Wire.read();                     // Registers 0x45 (GYRO_YOUT_H) + 0x46 (GYRO_YOUT_L)
  gyroZ=Wire.read()<<8|Wire.read();                     // Registers: 0x47 (GYRO_ZOUT_H) + 0x48 (GYRO_ZOUT_L)
  
//  Serial.print("AccX = ");
//  Serial.print(accelerometerX);
//  Serial.print(" || AccY = ");
//  Serial.print(accelerometerY);
//  Serial.print(" || AccZ = ");
//  Serial.print(accelerometerZ);
//  Serial.print(" || Temp = ");
//  Serial.print(temperature/340.00+36.53);               // Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 36.53
  Serial.print(" || GyroX = ");
  Serial.print(gyroX);
  Serial.print(" || GyroY = ");
  Serial.print(gyroY);
  Serial.print(" || GyroZ = ");
  Serial.print(gyroZ);
  Serial.println();
  delay(100);
}
