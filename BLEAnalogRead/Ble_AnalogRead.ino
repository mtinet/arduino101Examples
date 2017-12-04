/*
  A Simple example that alows you to turn on/off a light connected to a digital relay (switch)  using a Arduino 101 microcontroller.

  Author Andrew McKinney (mckinney@mit.edu)

*/
#include <CurieBLE.h>

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService ARead("19B10010-E8F2-537E-4F6C-D104768A1214"); // BLE AnalogRead Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedIntCharacteristic AnalogData( "19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
BLEUnsignedIntCharacteristic AnalogData2("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

int old_data ;
void setup() {
  Serial.begin(9600);
  // set Light pin to output mode
  // set advertised local name and service UUID:
  blePeripheral.setLocalName("ARead");
  blePeripheral.setAdvertisedServiceUuid(ARead.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(ARead);
  blePeripheral.addAttribute(AnalogData);
  blePeripheral.addAttribute(AnalogData2);
 
  // begin advertising BLE Light service:
  blePeripheral.begin();

  Serial.println("BLE AnalogRead service.");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();
  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      int new_data = analogRead(A0);
      if(old_data != new_data)
      { 
        int data1 = new_data%128;
        int data2 = new_data/128 + 128;
        int send_data = data2*256 + data1;
        AnalogData.setValue(send_data);
        Serial.println(new_data);
        old_data = new_data;
        delay(50);
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
    }
 }
