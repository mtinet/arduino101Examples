# [앱 인벤터 IoT]
## 레슨 2 : 아두이노101 Fading(PWM)

이 문서는 아두이노 101의 BLE(Bluetooth Low Energy, Bluetooth 4.0)를 앱인벤터로 조작하는 구현하는 방법에 대한 문서입니다.  

여기에서 연재되고 있는 레슨들은 다양한 방법으로 앱인벤터와 아두이노 101(BLE)가 상호작용 할 수 있는 방법을 설명해줍니다. 단, 여러분이 이 기능을 사용하기 위해서 [반드시 BLE컴포넌트를 확장자로 Import](http://appinventor.mit.edu/extensions/)시켜야합니다.  

실제 앱의 디자인, 회로도, 구동영상은 다음과 같습니다.  
![](https://github.com/mtinet/arduino101Examples/blob/master/image/8.png?raw=true)  
![](https://github.com/mtinet/arduino101Examples/blob/master/image/16.png?raw=true)  
[![](https://github.com/mtinet/arduino101Examples/blob/master/image/9.png?raw=true)](https://youtu.be/ihMyDoxapBQ)  

아두이노101은 arduino.cc(NOT .org)와 인텔의 협업으로 만들어진 최종의 개발 보드입니다. 또한 미국 밖에서는 제누이노101으로 알려져있습니다.  


## App Inventor  
기본적으로, 해당 예제는 [앱인벤터와 아두이노 : 레슨1. LED 깜빡임] 예제와 BLE컴포넌트를 사용한다는 점을 제외하고는 거의 같다. 해당 예제에서 우리는 아두이노101의 D9번 핀에 연결된 LED의 밝기를 슬라이더를 통해 제어하고자 합니다.  


### Designer Page  
Block컴포넌트는 정기적으로 LED의 밝기를 제어하는 슬라이더포인터의 위치를 BLE 컴포넌트를 통해 아두이노101보드에 보냅니다. 슬라이더 포인터의 위치는 또한 텍스트상자를 통해서도 보여집니다. 단, 해당예제를 실행할 때 사용하는 통신프로토콜이 다르기 때문에 기존의 블루투스클라이언트 컴포넌트를 사용해서는 아두이노와 통신할 수 없습니다. 
![](https://github.com/mtinet/arduino101Examples/blob/master/image/10.png?raw=true)  

* BLE Extension을 Import하는 방법 : [BLE Extension Download](https://github.com/mtinet/arduino101Examples/blob/master/LEDBlink/edu.mit.appinventor.ble.BluetoothLE.aix) - 앱인벤터 열기 - Project - start new project - 왼쪽하단의 Extension 클릭 - Import Extension 클릭 - From my computer에서 파일선택 후 Import 클릭  


### Blocks  
##### 초기화 및 연결  
초기화면에서 BluetoothLE1을 이용하여 사용가능한 디바이스를 검색합니다. (아두이노101이 전원이 연결되어 준비되어 있다면 감지될 것입니다.)  

다음으로, ConnectButton.Click창 안의 ConnectButton은 특정한 장치에 연결하기 위해 BlutoothLE1을 선택합니다. 사용하고 있는 아두이노101의 블루투스의 맥주소를 입력합니다.(98:04- ...) 맥주소 문자열을 여러분이 사용하고 있는 아두이노101의 것으로 수정합니다.  
![](https://github.com/mtinet/arduino101Examples/blob/master/image/11.png?raw=true)  
![](https://github.com/mtinet/arduino101Examples/blob/master/image/12.png?raw=true)  

##### 연결 확인  
연결이 되고 나면 BLuetootheLE!.Connected 창이 다음과 같이 호출될 것입니다.  
![](https://github.com/mtinet/arduino101Examples/blob/master/image/13.png?raw=true)  

##### 연속전송신호  
Clock을 이용합니다. Timer는 다음 두 작업을 매 0.1초마다 완성하기 위해 명령을 내립니다.  

 ⦁TextBox에서 슬라이더의 포인터 위치를 표시합니다.  
 ⦁BluetoothLE1.writeIntValue명령을 사용하여 포인터 위치를 전송하면, 아두이노101에서 이 정보는 analogWrite명령을 통해 LED의 밝기를 제어합니다. service_uuid칸에는 “19B10010-E8F2-537E-4F6C-D104768A1214″를 characteristic_uuid칸에는 “19B10011-E8F2-537E-4F6C-D104768A1214″를 입력하세요.아두이노 101은 이 파라메터를 BLE서비스에 사용합니다.  
![](https://github.com/mtinet/arduino101Examples/blob/master/image/14.png?raw=true)  


##### 연결 해제  
Button_Disconnect.Click window의 Button_Disconnect 버튼을 누르면, BluetoothLE1컴포넌트가 기기에서 연결해제됩니다.  
![](https://github.com/mtinet/arduino101Examples/blob/master/image/15.png?raw=true)  



## Arduino 101 Code  

다음 code를 아두이노101에 복사/붙여넣기 하세요. 아두이노 101에 BLE가 내장되어 있기 때문에 따로 HC-05와 같은 별도의 Bluetoothe연결은 필요하지 않습니다.  

스케치에서 사용되는 service_uuid와 characteristic_uuid는 반드시 여러분이 앱인벤터에서 사용한 문자열과 같아야 합니다.  

```
/*   

  A simple demo of how to control Arduino 101' LED fading with App Inventor's BLE component.

  By CAVEDU (service@cavedu.com)

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
```

## 관련 파일 다운로드  
[Arduino101_LED.fzz](https://github.com/mtinet/arduino101Examples/blob/master/BLEFading/Arduino101_LED.fzz)  
[BLE_PWM_1.aia](https://github.com/mtinet/arduino101Examples/blob/master/BLEFading/Ble_pwm_1/BLE_PWM.aia)  
[Ble_pwm_1.ino](https://github.com/mtinet/arduino101Examples/blob/master/BLEFading/Ble_pwm_1/Ble_pwm.ino)  
[BLE_PWM_2.aia](https://github.com/mtinet/arduino101Examples/blob/master/BLEFading/Ble_pwm_2/BLE_PWM_2.aia)  
[Ble_pwm_2.ino](https://github.com/mtinet/arduino101Examples/blob/master/BLEFading/Ble_pwm_2/Ble_pwm_2.ino)  



