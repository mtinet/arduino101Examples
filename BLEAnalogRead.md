# [앱 인벤터 IoT]
## 레슨 2 : Read Arduino 101's analog pin  
출처 링크 : [http://www.appinventor.tw/ble_analogread](http://www.appinventor.tw/ble_analogread)  
번역 : 영등포고등학교 김주현선생님  

This topic is the third lesson of MIT App Inventor IoT (Internet of Things) tutorials. We are going to introduce how to use your Android phone to continuously read Arduino 101's analog pin(A0) via App Inventor's BluetoothLE (Bluetooth 4.0 Low Energy)component.  

MIT App Inventor will use Arduino 101 as the core dev board of its IoT solutions, you can develop various kinds of interactive project with the kit (planning).  You must import BLE component(.aix) as an extension before using it. A screenshot of the actual app execution is shown below. Enjoy~

 
[![](https://github.com/mtinet/arduino101Examples/blob/master/image/17.png?raw=true)](https://youtu.be/uuapPq8GZYQ)  


Arduino 101 is the latest dev board under cooperation between Arduino.cc and Intel, which is named as Genuino 101 out side USA.

More topics: 

Make: $30 Gets You the Sensor-Packed, Curie-Powered Arduino 101
Arduino/Genuino 101 CurieBLE CallbackLED
Part List

1. Android phone (Must have BLE hardware, but I think it's not a problem for most Android devices today).

2. Arduino 101

3. Potentiometer (or other similar analog input component you have). Take potentiometer for example, please connect the central pin to Arduino 101's A0 analog pin. Other two pins are connected to Arduino 101's 5V and GND pins. Please note that potentiometer is a non-polarity components therefore the difference you connect the right-hand side pin to Arduino 101's 5V or GND pin is that you get the readings increasing/decreasing when you turn the knob CW. 

![](https://github.com/mtinet/arduino101Examples/blob/master/image/18.png?raw=true)

## App Inventor  
This example will continuously reading Arduino'101 analog A0 pin, and update Label and Slider accordingly.


### Designer Page  
This example had used 3 Clock components, and their TimerInterval are found after several tests, you may need to adjust them according to the real situation. Since different protocol, you can not use old BluetoothClient component to talk with Arduino 101.

![](https://github.com/mtinet/arduino101Examples/blob/master/image/19.png?raw=true)  

#### How to play:

For simplicity, this project connect to your Arduino 101 directly, which means the Bluetooth address is assigned in the code. If your app has to connect from several devices, I think pairing with these devices first and pick them by ListPicker component in App Inventor is a better solution.

How to pair your Arduino 101 and Andorid phone: First you must pair the Bluetooth module with your Android phone. After you connect all the hardware, you can see that the Bluetooth module's red LED is flashing, means ready for connecting. Then please open your Android phone's Bluetooth setting page (which should under Settings... , differs on each phone), click the name of your module (something like HC-05). Please enter 1234 (or 0000) when there is a prompt asking the paring key. Done~

There is only BTList which is enabled when you first open the app. Please click BTList, it will show all paired Bluetooth devices on your phone. Please click the name of your module, it should take 1~2 seconds to connect and back the main screen. You can see that the [LED Turn On] button is now clickable and the module's LED is keep lighted up. Just click the button, the LED on Arduino will light up and the button's text will become "LED Turn Off". Click again will turn off the LED and switch back the button text. 

Please click the [Disconnect] button when you don't want to play anymore, this will disconnect the connection of your phone and bluetooth module and the module's LED will flashing again.


### Blocks  
##### 1. 초기화 및 연결  
While initializing(Screen1.Initializing event), BluetoothLE1 component will scan for avalible devices, which means your Arduino 101 should be ready by then. 

When you click the ConnectButton (Button_Connect.Click event),  BluetoothLE1 component will try to connect the specified device, we put our Arduino 101's bluetooth address here (98:4F…), please modify this string according to your Arduino 101's.

![](https://github.com/mtinet/arduino101Examples/blob/master/image/20.png?raw=true)  

##### 2. 연결 확인  
BluetoothLE1.connected event will be called after the connection is established, we show a message on Screen's titlebar. It's quite useful for display some shor messages. 

![](https://github.com/mtinet/arduino101Examples/blob/master/image/21.png?raw=true)  

##### 3. Clock1 (called every 1 second): read data sent back by Arduino 101  
Clock1 component can tell whether it had already connected with an Arduino 101 by disconnect variable value. If it is true, the App Inventor will further check if there was a connection, if connected then cut off connection(BluetoothLE.DisconnectWithAddress), otherwise then start scanning BLE devices (BluetoothLE.StartScanning).

On the other hand, if disconnect variable value is false, then App Inventor will start to combine two variables (data1 and data2) to get real analog pin status. But first you need to enable the Timer event of Clock2 and Clock3.

The reason why combining two variables is because the range of Arduino's analog pin is 0~1023, so it need two integer variables(data2 and data1) to represent. Finally to show this combined value on Label and Slider, done~

![](https://github.com/mtinet/arduino101Examples/blob/master/image/22.png?raw=true)  

##### 4. Clock2 (called every 0.9 second): 

Clock2 will disable the Timer event of itsefl and Clock3's every 0.9 second, then re-activate the timer event according to the value of disconnect .
![](https://github.com/mtinet/arduino101Examples/blob/master/image/23.png?raw=true)  


##### 5. Clock3 (called every 0.005 second): control offset value and combine 2 data into real reading

Clock3 will control how to read a integer from Arduino 101(BluetoothLE.ReadIntValue) according to status variable(0 or 1). Then assign the result of BluetoothLE.IntGattValue to data variable, if the value of data is within 128~256, then minus 128 from it before assigning to data2.

However, if data is less than 128, them assign data to data1, we will combine it in Clock1.Timer event.

service_uuid and characteristic_uuid are also specified in the sketch as “19B10011-E8F2-537E-4F6C-D104768A1214″,  which must be the same with the string you use in App Inventor.  

![](https://github.com/mtinet/arduino101Examples/blob/master/image/24.png?raw=true)  


##### 6. 연결 해제  
When click Button_Disconnect, we will set disconnect varaible to true, which will trigger BluetoothLE.DisconnectWithAddress)in Clock1.Timer event (STEP3).  

![](https://github.com/mtinet/arduino101Examples/blob/master/image/25.png?raw=true)  



## Complete Arduino 101 sketch

Copy the code and paste it onto Arduino 101. Please notice that Arduino 101 has onboard BLE hardware, therefore you don't need to connect other Bluetooth modules such as HC05.

service_uuid and characteristic_uuid are also specified in the sketch as “19B10011-E8F2-537E-4F6C-D104768A1214″,  which must be the same with the string you use in App Inventor.

```
#include <CurieBLE.h>

BLEPeripheral blePeripheral; // BLE Peripheral Device (the board you're programming)
BLEService ARead("19B10010-E8F2-537E-4F6C-D104768A1214"); // BLE AnalogRead Service
// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedIntCharacteristic AnalogData( "19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
BLEUnsignedIntCharacteristic AnalogData2("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
int old_data ;
void setup() {
  Serial.begin(9600);
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
if (old_data != new_data)
{
int data1 = new_data % 128;
int data2 = new_data / 128 + 128;    //divide new_data into 2 value (1 byte is 8 bits)
int send_data = data2 * 256 + data1;  
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
```

## 관련 파일 다운로드  
[BLE_AnalogRead.aia](https://github.com/mtinet/arduino101Examples/blob/master/BLEAnalogRead/BLE_AnalogRead.aia)  
[BLE_AnalogRead.ino](https://github.com/mtinet/arduino101Examples/blob/master/BLEAnalogRead/Ble_AnalogRead.ino)  




