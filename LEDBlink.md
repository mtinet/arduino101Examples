# [앱 인벤터 IoT]  
## 레슨 1 : 아두이노101 Blink  
이 토픽은 MIT 앱인벤터 IoT(사물인터넷) 튜토리얼의 첫번째 레슨입니다. 우리는 앱인벤터의 블루투스LE(블루투스 4.0 로우 에너지, BLE) 콤포넌트를 통해 아두이노101의 LED Blink를 제어하기 위해 여러분의 안드로이드폰을 사용하는 방법을 안내하려고 합니다.  

MIT 앱인벤터는 사물인터넷 솔루션의 핵심 장치보드로 아두이노101을 사용합니다. 여러분은 이 키트를 사용해 다양한 종류의 상호작용 프로젝트를 개발할 수 있습니다. 여러분은 이것을 사용하기 전에 BLE콤포넌트(.aix) 확장팩을 임포트해야만합니다. 실제 앱 실행장면의 스크린샷은 아래를 참고하세요.  

![](https://github.com/mtinet/genuino101Examples/blob/master/image/1.jpg?raw=true)

[![](https://github.com/mtinet/genuino101Examples/blob/master/image/2.png?raw=true)](https://youtu.be/WSktBhO94Ug)(동영상을 보려면 사진을 클릭하세요.)  

아두이노101은 Arduino.cc와 Intel 사이의 협업을 통해 만들어진 최신 장치 보드입니다. 미국 외에서는 Genuino101이라고 부릅니다.  

##### 더 많은 토픽 :  
[Make: $30 Gets You the Sensor-Packed, Curie-Powered Arduino 101](https://makezine.com/2015/10/16/30-gets-you-the-sensor-packed-curie-powered-arduino-101/)  
[Arduino/Genuino 101 CurieBLE CallbackLED](https://www.arduino.cc/en/Tutorial/Genuino101CurieBLECallbackLED)  

##### 부품 리스트 :  
1. 안드로이드 폰(BLE 내장 필요, 요즘 대부분의 안드로이드 폰은 걱정하지 않아도 됨)  
2. 아두이노101  
3. LED, 릴레이 모듈(옵션, 온보드 칩 LED를 바로 사용할 수 있음)  

## App Inventor  
기본적으로 이 프로젝트는 BLE콤포넌트를 제외하고는 [App Inventor and Arduino: Lesson 1: LED Blink](http://www.appinventor.tw/arduino_bt_blink)와 거의 같습니다. 우리는 여러분이 버튼을 누르고 있는 동안 아두이노101의 온보드 칩 LED가 깜빡이도록 제어하려고 합니다. 잊지 마세요. 여러분은 이 프로젝트를 통해 기본적인 스마트홈 데모를 만들 수 있는 진짜 LED들과 릴레이 모듈로 확장할 수 있습니다.  

### Designer 
비슷합니다. 맞죠? 여러분은 종종 우리 튜토리얼의 이러한 종류의 인터페이스를 사용하게 될 것입니다. 하나의 ListPicker와 두개의 버튼 콤포넌트로 구성된 꽤 쉬운 인터페이스입니다. 그리고 블루투스 통신을 위한 하나의 Bluetooth Client 콤포넌트를 사용합니다. 아래의 설명을 확인하세요.  

1. ConnectButton(Button) : 이 프로젝트에서 아두이노101의 BLE 장치에 연결하기 위해 클릭합니다.  
2. TurnOnButton(Button) : 아두이노101에 "0"문자열을 보내기 위해 클릭합니다.  
3. TurnOffButton(Button) : 아두이노101에 "1"문자열을 보내기 위해 클릭합니다.  
4. Button_Disconnect(Button) : 안드로이드폰과 아두이노101사이의 연결을 닫기 위해  
5. *BluetoothLE(non visible) : BLE통신을 위한 콤포넌트, 여러분의 AI2 프로젝트에 BLE.aix파일을 임포트 하세요.  


![](https://github.com/mtinet/genuino101Examples/blob/master/image/3.png?raw=true)

#### 사용하는 방법 :
간단하게도, 이 프로젝트는 여러분의 아두이노101에 바로 연결됩니다. 이것은 블루투스 주소가 코드안에 배정되어 있음을 의미합니다. 만약에 여러분의 앱이 몇몇 장치를 연결해야 한다면 이 장치로 우선 페어링을 하고 앱인벤터에서 ListPicker콤포넌트를 통해 그 장치를 선택하는 것이 더 나은 솔루션입니다.  

##### 여러분의 아두이노101과 안드로이드 폰을 페어링하는 방법 : 
앱의 Connect버튼을 누르면 앱 안에 이미 등록되어 있는 맥주소를 통해 자동으로 연결됩니다.

### Blocks  
##### 1. 초기화와 연결
초기화를 하는동안(Screen1.Initionalizing event), 블루투스LE1 콤포넌트는 사용가능한 장치를 스캔할 것입니다. 이것은 여러분의 아두이노101이 연결을 준비하고 있어야 한다는 것을 의미합니다.

여러분이 Button_Connect를 클릭했을 때(ConnectButton_Connect.Click event), 블루투스LE1 콤포넌트는 지정된 장치에 연결을 시도할 것입니다. 우리는 우리의 아두이노101의 블루투스 주소를 여기에 넣었습니다(98:4F:EE:0F:XX:XX, 총 12digits). nrf Connect 앱을 다운받고 여러분의 아두이노101의 진짜 주소를 확인하세요.  

![](https://github.com/mtinet/genuino101Examples/blob/master/image/4.png?raw=true)

##### 2. 연결 확인  
블루투스LE1.connected event는 연결이 완료된 후에 호출됩니다. 우리는 Label1에 "Connected"를 볼 수 있고, 다른 콤포넌트를 사용할 수 있도록 조정됩니다.  

##### 3. 1과 0을 이용해 LED 제어
여러분이 Button_LED(Button_LED.Click event)를 클릭했을 때, 이것은 Button_LED의 텍스트에 따라 여러분의 아두이노101에 정수 1과 0을 내보내기 위해 BluetoothLE1.WriteIntValue메소드를 사용할 것입니다.  

아두이노 스케치에 따라, 아두이노101은 "1"이라는 값이 받아졌을 때 13번 핀의 LED를 켜고, "0"이라는 값이 받아졌을 때 LED를 끌 것입니다.  

“19B10010-E8F2-537E-4F6C-D104768A1214″라는 service_uuid와 “19B10011-E8F2-537E-4F6C-D104768A1214″라는 characteristic_uuid를 사용해야하는 것을 주의하세요. 이것은 아두이노101의 BLE서비스를 의미합니다. 이 UUID쌍은 아두이노 스케치에 있는 것과 같아야만합니다.  

여러분은 버튼 대신에 센서값, 구글 음성 인식기(Google Speech Recognizer), 슬라이더 등으로 트리거 이벤트를 바꿀 수 있습니다. 아두이노 스케치에서 더 많은 I/O인터페이스 케이스는 [[App Inventor IoT ] Lesson 4: 4-axis robotarm](http://www.appinventor.tw/ble_lesson4_robotarm)을 확인하세요.  

![](https://github.com/mtinet/genuino101Examples/blob/master/image/5.png?raw=true)

##### 4. 연결 해제
여러분이 Button_Disconnect button(Button_Disconnect.Click event)을 눌렀을 때, 블루투스LE1 콤포넌트는 지정된 아두이노101과의 연결을 닫고, 모든 콤포넌트를 초기 상태로 세팅합니다. 여러분은 다시 아두이노101에 연결할 수 있습니다.  

![](https://github.com/mtinet/genuino101Examples/blob/master/image/6.png?raw=true)

Arduino 101

This sketch is contributed by MIT App Inventor team. Please notice that Arduino 101 has onboard BLE hardware, therefore you don't have to connect Bluetooth modules like HC05.

There are two BLE objects in the sketch: blePeripheral(Arduino 101) and bleCentral(Android). blePeripheral is used to configure all the attributes of the Arduino 101, such as service_uuid and characteristic_uuid. And bleCentral is reponsible for the connection between the board and phone.

service_uuid and characteristic_uuid are also specified in the sketch, they are ″19B10010-E8F2-537E-4F6C-D104768A1214″ and ″19B10011-E8F2-537E-4F6C-D104768A1214″,  which must be the same with the string you use in App Inventor, as below:


~~~
BLEService lightService("19B10010-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic switchCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
~~~

The core of this sketch is that we use incom = EDStatus.value() to check what Arduino 101 has received. Arduino 101 will light up #13 LED when it receive an integer 1; Otherwise (integer 0 in our case) it will keep the LED off.

~~~
while (central.connected()) {
//Serial.println(LEDStatus.written());
if (LEDStatus.written())
{
        incom = LEDStatus.value();
        Serial.print("incom ");
        Serial.println(incom);
if (incom != last_incom)  //compare current value with last one
{
if (incom == 1)        //integer 1
{
            Serial.println("LED On");
digitalWrite(LED, HIGH);
}
else
{
            Serial.println("LED Off");
digitalWrite(LED, LOW);
}
}
        last_incom = incom;
}
}
~~~

## 아두이노101 스케치 완성
~~~
#include <CurieBLE.h>

#define LED 13

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService ControlLED("19B10010-E8F2-537E-4F6C-D104768A1214"); // BLE AnalogRead Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedIntCharacteristic LEDStatus("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite  );

int incom = 0;
int last_incom = 0;

void setup() {
  Serial.begin(9600);
  // set Light pin to output mode
  // set advertised local name and service UUID:
  blePeripheral.setLocalName("ControlLED");
  blePeripheral.setAdvertisedServiceUuid(ControlLED.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(ControlLED);
  blePeripheral.addAttribute(LEDStatus);

  // begin advertising BLE Light service:
  blePeripheral.begin();

  Serial.println("BLE AnalogRead service.");
  pinMode(LED, OUTPUT);
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
      //Serial.println(LEDStatus.written());
      if (LEDStatus.written())
      {
        incom = LEDStatus.value();
        Serial.print("incom ");
        Serial.println(incom);
        if (incom != last_incom)
        {
          if (incom == 1)  //integer 1
          {
            Serial.println("LED On");
            digitalWrite(LED, HIGH);
          }
          else             //integer 0 in our case
          {
            Serial.println("LED Off");
            digitalWrite(LED, LOW);
          }
        }
        last_incom = incom;
      }
    }
    delay(100);
  }

  // when the central disconnects, print it out:
  Serial.print(F("Disconnected from central: "));
  Serial.println(central.address());
}
~~~
