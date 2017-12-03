/*
  A Simple example that alows you to turn on/off a light connected to a digital relay (switch)  using a Arduino 101 microcontroller.

  Author Andrew McKinney (mckinney@mit.edu)

*/
#include <CurieBLE.h>

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService lightService("19B10010-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedIntCharacteristic switchCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);


const int lightPin = 9; // pin to use for the Light

void setup() {
  Serial.begin(9600);

  // set Light pin to output mode
  pinMode(lightPin, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("Light Service");
  blePeripheral.setAdvertisedServiceUuid(lightService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(lightService);
  blePeripheral.addAttribute(switchCharacteristic);

  // set the initial value for the characeristic:
  switchCharacteristic.setValue(0);

  // begin advertising BLE Light service:
  blePeripheral.begin();

  Serial.println("BLE Light service.");
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
      // if the remote device wrote to the characteristic,
      // use the value to control the Light:
      if (switchCharacteristic.written()) {
          Serial.println(switchCharacteristic.value());
          int light = map(switchCharacteristic.value(),10,49,0,255);
          analogWrite(lightPin,light);
          Serial.println(light);
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
