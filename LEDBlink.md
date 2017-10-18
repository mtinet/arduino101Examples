# [앱 인벤터 IoT]  
## 레슨 1 : 아두이노101 Blink  
이 토픽은 MIT 앱인벤터 IoT(사물인터넷) 튜토리얼의 첫번째 레슨입니다. 우리는 앱인벤터의 블루투스LE(블루투스 4.0 로우 에너지, BLE) 콤포넌트를 통해 아두이노101의 LED Blink를 제어하기 위해 여러분의 안드로이드폰을 사용하는 방법을 안내하려고 합니다.  

MIT 앱인벤터는 사물인터넷 솔루션의 핵심 장치보드로 아두이노101을 사용합니다. 여러분은 이 키트를 사용해 다양한 종류의 상호작용 프로젝트를 개발할 수 있습니다. 여러분은 이것을 사용하기 전에 BLE콤포넌트(.aix) 확장팩을 임포트해야만합니다. 실제 앱 실행장면의 스크린샷은 아래를 참고하세요.  

![](https://github.com/mtinet/genuino101Examples/blob/master/image/2016-01-26-14.50.47-1024x768-1024x768.jpg?raw=true)

[![](https://github.com/mtinet/genuino101Examples/blob/master/image/test.png?raw=true)](https://youtu.be/WSktBhO94Ug)

아두이노101은 Arduino.cc와 Intel 사이의 협업을 통해 만들어진 최신 장치 보드이다. 미국 외에서는 Genuino101이라고 부른다.  

더 많은 토픽 :  
[Make: $30 Gets You the Sensor-Packed, Curie-Powered Arduino 101](https://makezine.com/2015/10/16/30-gets-you-the-sensor-packed-curie-powered-arduino-101/)  
[Arduino/Genuino 101 CurieBLE CallbackLED](https://www.arduino.cc/en/Tutorial/Genuino101CurieBLECallbackLED)  

부품 리스트 :  
1. 안드로이드 폰(BLE 내장 필요, 요즘 대부분의 안드로이드 폰은 걱정하지 않아도 됨)  
2. 아두이노101  
3. LED, 릴레이 모듈(옵션, 온보드 칩 LED를 바로 사용할 수 있음)  

### App Inventor  
기본적으로 이 프로젝트는 BLE콤포넌트를 제외하고는 [App Inventor and Arduino: Lesson 1: LED Blink](http://www.appinventor.tw/arduino_bt_blink)와 거의 같다. 우리는 여러분이 버튼을 누르고 있는 동안 아두이노101의 온보드 칩 LED가 깜빡이도록 제어하려고 한다. 잊지 마세요. 여러분은 이 프로젝트를 통해 기본적인 스마트홈 데모를 만들 수 있는 진짜 LED들과 릴레이 모듈로 확장할 수 있습니다.  

#### Designer 

Familiar, right? You will use this kind of interface frequently along our tutorials. Quite easy interface with one of one ListPicker and two Button components. And one Bluetooth client components for Bluetooth communication. Please check the description below:

1. ConnectButton (Button): Click to connect to specified BLE device, which is Arduino 101 in this project.
2. TurnOnButton (Button): Click to send string "0" to Arduino 101.
3. TurnOffButton (Button): Click to send string "1" to Arduino 101.
4. Button_Disconnect (Button): Click to close connection between Android phone and Arduino 101.
5. *BluetoothLE (non visible): experimental components for BLE communication. Please import BLE .aix file to your AI2 project.
