# [앱 인벤터 IoT]
## 레슨 2 : Read Arduino 101's analog pin  
출처 링크 : [http://www.appinventor.tw/ble_analogread](http://www.appinventor.tw/ble_analogread)  
번역 : 영등포고등학교 김주현선생님  

이 토픽은 MIT App Inventor IoT(Internet of Things) 튜토리얼의 세번째 레슨입니다. 여기서는 앱인벤터의 BluetoothLE(Bluetooth 4.0 Low Energy)콤포넌트를 이용해 여러분의 안드로이드폰으로 아두이노101의 아날로그핀(A0)의 값을 연속적으로 읽어들이는 방법에 대해 안내하려고 합니다.  

MIT 앱인벤터는 IoT 솔루션의 핵심 장치 보드로 아두이노101을 사용할 것입니다. 여러분은 이 키트(계획중)로 다양한 종류의 상호작용 프로젝트를 개발할 수 있습니다. 단, 여러분이 이 기능을 사용하기 위해서 [반드시 BLE컴포넌트를 확장자로 Import](http://appinventor.mit.edu/extensions/)시켜야합니다. 실제 앱 실행 스크린샷은 아래에 있습니다. 즐기세요~   

[![](https://github.com/mtinet/arduino101Examples/blob/master/image/17.png?raw=true)](https://youtu.be/uuapPq8GZYQ)  
(동영상을 보려면 사진을 클릭하세요.)  

아두이노101은 arduino.cc(NOT .org)와 인텔의 협업으로 만들어진 최종의 개발 보드입니다. 또한 미국 밖에서는 제누이노101으로 알려져있습니다.

##### 더 많은 토픽들 :  
* [Make: $30 Gets You the Sensor-Packed, Curie-Powered Arduino 101](https://makezine.com/2015/10/16/30-gets-you-the-sensor-packed-curie-powered-arduino-101/)  
* [Arduino/Genuino 101 CurieBLE CallbackLED](https://www.arduino.cc/en/Tutorial/Genuino101CurieBLECallbackLED)  

##### 부품 목록 :  
1. 안드로이드폰(반드시 BLE하드웨어를 내장하고 있어야 하지만, 요즘 대부분의 안드로이드장치는 이것이 문제가 되지는 않습니다.)  
2. Arduino 101  
3. 포텐시오미터(가변저항, 또는 여러분이 가지고 있는 다른 아날로그 입력 장치). 예제를 위해 포텐시오미터를 구하여, 가운데 핀(센싱핀)을 아두이노101의 A0 아날로그 입력 핀에 연결하세요. 다른 두 핀은 아두이노101의 5V, GND핀에 연결합니다. 포텐시오미터는 극성이 없으므로 여러분이 오른쪽의 핀에 아두이노101의 5V를 연결하거나 GND를 연결했을 때 발생하는 차이점은 노브를 시계방향으로 돌렸을 때 읽어들이는 값이 증가하거나/감소하는 것 뿐입니다.

![](https://github.com/mtinet/arduino101Examples/blob/master/image/18.jpg?raw=true)  



## App Inventor  
이 예제는 아두이노101의 A0핀을 연속적으로 읽을것이며, 앱인벤터로 만든 레이블과 슬라이더도 따라서 업데이트 됩니다.  


### Designer Page  
이 예제는 3개의 Clock콤포넌트를 사용합니다. 
This example had used 3 Clock components, and their TimerInterval are found after several tests, you may need to adjust them according to the real situation. Since different protocol, you can not use old BluetoothClient component to talk with Arduino 101.

![](https://github.com/mtinet/arduino101Examples/blob/master/image/19.jpg?raw=true)  


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




