      /////////////////////////////////////////////  
     //      Mobile Water Level Tracker         //
    //              via HC-06                  //
   //               (Android)                 //           
  //             by Kutluhan Aktar           // 
 //                                         //
/////////////////////////////////////////////


// Measure the water integrity and level around the area where you want to get data from by using a water level sensor and a Funduino water sensor. 
// View the water integrity and level variables send by a HC-06 Bluetooth Module on your Android phone by downloading the Mobile Water Level Tracker.
//
// Connections
// Arduino Nano :           
//                                 HC-06 Bluetooth Module
// 5V  --------------------------- 5V
// GND --------------------------- GND
// D5  --------------------------- RX
// D4  --------------------------- TX
//                                 Funduino Water Sensor
// 5V  --------------------------- 5V
// A0  --------------------------- S
// GND --------------------------- GND
//                                 Water Level Sensor
// 5V  --------------------------- Leg(1)
// GND + D2 ---------------------- Leg(2)
//                                 Control Led
// D3  --------------------------- 


// Include SoftwareSerial to control HC-06 Bluetooth Module
#include <SoftwareSerial.h>

// Define HC-06 Bluetooth Module RX and TX pins.
#define Water_RX 4
#define Water_TX 5

// Define bluetooth control pin.
#define control 3

// Define the Water Level Sensor digital pin.
#define Level 2

// Define Funduino Water Sensor pins.
#define Water A0

// Data holders.
int WaterLevel, WaterIntegrity;

// Initiate the bluetooth module.
SoftwareSerial WaterModule(Water_RX, Water_TX);

// Change the HC-06 Bluetooth Module default variables.
String Name = "WaterModule";
int Password = 1111;
String Uart = "9600,0,0";

void setup() {
Serial.begin(9600);
WaterModule.begin(9600);

pinMode(control, OUTPUT);

// If you want to change the HC-06 Bluetooth Module default variables, just uncomment this function below.
//Change_BluetoothModule_Defaults();

}

void loop() {
gatherWater();

sendWaterLevel();

}

// Send water level and integrity to Mobile Water Level Tracker App through the HC-06 Bluetooth Module.
void sendWaterLevel(){
  if(WaterModule.isListening()){
    // Turn the control led on.
    digitalWrite(control, HIGH);
  }else{
    // Turn the control led off.
    digitalWrite(control, LOW);
   }
   
    WaterModule.print("Water Level : \n");
    if(WaterLevel == 1){ WaterModule.print("OK \n"); }else if(WaterLevel == 0){ WaterModule.print("FULL \n"); }
    WaterModule.print("Water Integrity : \n");
    WaterModule.print(WaterIntegrity);

    delay(1000);
}


// Gather water level and water integrity from water sensors.
void gatherWater(){
  WaterLevel = digitalRead(Level);

  // Map the water sensor values between 0 and 10 to better measure the water integrity.
  WaterIntegrity = map(analogRead(Water), 0, 1073, 0, 10);
}
  
// Change the default variables embedded in the HC-06 Bluetooth Module.
void Change_BluetoothModule_Defaults(){ 
 
  WaterModule.print("AT+NAME"); // Change the name.
  WaterModule.println(Name); 
  Serial.print("Name is changed: ");
  Serial.println(Name);
  delay(2000);
  WaterModule.print("AT+PSWD"); // Change the password.
  WaterModule.println(Password);
  Serial.print("Password is changed: ");
  Serial.println(Password);
  delay(2000);
  WaterModule.print("AT+UART"); // Change the baud rate. If the bluetooth module is a HC-05, the default value of baud rate is 38400.
  WaterModule.println(Uart);
  Serial.print("Baud rate is set: ");
  Serial.println(Uart);
  delay(2000);
  Serial.println("Task is completed."); // You can see in the terminal whether the task is completed correctly or not.
}
