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
이 예제는 3개의 Clock콤포넌트를 사용합니다. TimerInterval은 여러 번의 테스트 후에 찾아냈습니다만 여러분은 그것들의 실제 상황에 따라 조정해야 할 필요가 있을 것입니다. 기존의 오래된 BluetoothClient콤포넌트는 서로 다른 프로토콜로 인해 아두이노101과 통신하는데 사용할 수 없습니다.

![](https://github.com/mtinet/arduino101Examples/blob/master/image/19.png?raw=true)  


#### 사용 방법 :
간단하게 말해서, 이 프로젝트는 여러분의 아두이노101에 직접적으로 연결합니다. 이는 블루투스의 맥주소가 코드에 이미 지정되어 있음을 의미합니다. 만약 여러분의 앱이 몇몇의 서로 다른 장치에 연결해야 한다면, 이 장치들을 먼저 페어링하고 앱인벤터의 ListPicker 콤포넌트를 이용해 선택하는 것이 더 나은 해결책이라고 생각합니다.  

여러분의 아두이노101과 안드로이드폰을 페어링(연결)하는 방법 : 우선 여러분은 여러분의 안드로이드폰에 있는 블루투스 모듈을 페어링해야만 합니다. 다음으로 여러분은 모든 하드웨어(회로)를 연결합니다. 그러면 여러분은 블루투스 모듈의 붉은색 LED가 깜빡거리는 것을 볼 수 있습니다. 연결할 준비가 되었음을 의미합니다. 그 다음 여러분의 안드로이드폰의 블루투스 세팅 페이지를 여십시오.('설정'안에 있는... 각 폰마다 다릅니다.) 여러분의 모듈(HC-05등과 같은) 이름을 클릭하세요. 페어링 키를 물어보는 프롬프트가 뜨면 1234 또는 0000을 입력하세요.  

여러분이 앱을 열면 단 하나의 BTList가 있습니다. BTList를 클릭하세요. 그러면 여러분 폰에 페어링 된 모든 블루투스 장치가 보일 것입니다. 여러분의 모듈 이름을 클릭하세요. 연결에는 1~2초가 소요되며, 메인스크린으로 돌아갑니다. 여러분은 [LED Turn On]버튼을 누를 수 있게 되고 블루투스 모듈의 LED는 켜진 상태를 유지합니다. 버튼을누르면 아두이노의 LED가 켜지고 버튼의 문자가 [LED Turn Off]로 바뀝니다. 다시 버튼을 누르면 LED가 꺼지고, 버튼의 문자가 되돌아갑니다.

여러분이 더 이상 사용하고 싶지 않을 때는 [Disconnect]버튼을 클릭하세요. 이것은 여러분의 폰과 블루투스 모듈의 연결을 해제하고, 모듈의 LED는 다시 깜빡거리게 됩니다.


### Blocks  
##### 1. 초기화 및 연결  
Screen1.Initializing event에 의해 초기화되고 있는 동안에 BluetoothLE1콤포넌트는 사용가능한 장치를 스캔하므로, 여러분의 아두이노101이 준비되어 있어야 합니다.

여러분이 Button_Connect.Click event의 ConnectButton을 클릭하면, BluetoothLE1 콤포넌트는 지정된 장치에 연결을 시도 할 것입니다. 우리는 다음과 같은 우리의 아두이노101의 블루투스 맥주소(98:4F:....)를 넣습니다. 여러분의 아두이노101에 맞춰 이 문자열을 수정하세요.  

![](https://github.com/mtinet/arduino101Examples/blob/master/image/20.png?raw=true)  

##### 2. 연결 확인  
BluetoothLE1.connected event는 연결이 완료된 후에 호출됩니다. 우리는 스크린의 타이틀바에서 메시지를 보게됩니다. 이것은 메시지를 띄우는데 꽤 유용합니다.

![](https://github.com/mtinet/arduino101Examples/blob/master/image/21.png?raw=true)  

##### 3. Clock1 (매 1초마다 호출됨): 아두이노101이 보낸 데이터 읽기  

Clock1 component can tell whether it had already connected with an Arduino 101 by disconnect variable value. If it is true, the App Inventor will further check if there was a connection, if connected then cut off connection(BluetoothLE.DisconnectWithAddress), otherwise then start scanning BLE devices (BluetoothLE.StartScanning).

On the other hand, if disconnect variable value is false, then App Inventor will start to combine two variables (data1 and data2) to get real analog pin status. But first you need to enable the Timer event of Clock2 and Clock3.

The reason why combining two variables is because the range of Arduino's analog pin is 0~1023, so it need two integer variables(data2 and data1) to represent. Finally to show this combined value on Label and Slider, done~

![](https://github.com/mtinet/arduino101Examples/blob/master/image/22.png?raw=true)  

##### 4. Clock2 (매 0.9초마다 호출됨): 
Clock2는 자체 Timer event를 비활성화하고 Clock3을 매 0.9초마다 비활성화합니다. 그런 다음 disconnect 값에 따라 Timer event를 재활성화합니다

![](https://github.com/mtinet/arduino101Examples/blob/master/image/23.png?raw=true)  


##### 5. Clock3 (매 0.005초마다 호출됨):  오프셋 값을 제어하고 2개의 데이터를 실제로 읽을 수 있도록 묶음  
Clock3 will control how to read a integer from Arduino 101(BluetoothLE.ReadIntValue) according to status variable(0 or 1). Then assign the result of BluetoothLE.IntGattValue to data variable, if the value of data is within 128~256, then minus 128 from it before assigning to data2.

However, if data is less than 128, them assign data to data1, we will combine it in Clock1.Timer event.

service_uuid and characteristic_uuid are also specified in the sketch as “19B10011-E8F2-537E-4F6C-D104768A1214″,  which must be the same with the string you use in App Inventor.  

![](https://github.com/mtinet/arduino101Examples/blob/master/image/24.png?raw=true)  


##### 6. 연결 해제  
Button_Disconnect를 클릭하면, 우리는 disconnect 변수를 true로 설정하게 될 것입니다. 이것은 Step3에있는 Clock1.Timer 이벤트의 BluetoothLE.DisconnectWithAddress를 동작시킵니다.  

![](https://github.com/mtinet/arduino101Examples/blob/master/image/25.png?raw=true)  



## Complete Arduino 101 sketch  
코드를 복사해서 아두이노101에 붙여 넣습니다. 아두이노101은 BLE가 있어 여러분이 HC-05같은 블루투스 모듈을 따로 연결할 필요가 없습니다.  \

스케치에 지정된 “19B10011-E8F2-537E-4F6C-D104768A1214″와 같은 service_uuid와 characteristic_uuid 는 여러분이 앱인벤터에 사용한 문자열과 같아야합니다.  


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




