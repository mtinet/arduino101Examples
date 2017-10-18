# [앱 인벤터 IoT]  
## 레슨 1 : 아두이노101 Blink  
이 토픽은 MIT 앱인벤터 IoT(사물인터넷) 튜토리얼의 첫번째 레슨입니다. 우리는 앱인벤터의 블루투스LE(블루투스 4.0 로우 에너지, BLE) 콤포넌트를 통해 아두이노101의 LED Blink를 제어하기 위해 여러분의 안드로이드폰을 사용하는 방법을 안내하려고 합니다.  

MIT 앱인벤터는 사물인터넷 솔루션의 핵심 장치보드로 아두이노101을 사용합니다. 여러분은 이 키트를 사용해 다양한 종류의 상호작용 프로젝트를 개발할 수 있습니다. 여러분은 이것을 사용하기 전에 BLE콤포넌트(.aix) 확장팩을 임포트해야만합니다. 실제 앱 실행장면의 스크린샷은 아래를 참고하세요.  

![](https://github.com/mtinet/genuino101Examples/blob/master/image/2016-01-26-14.50.47-1024x768-1024x768.jpg?raw=true)

[![](https://github.com/mtinet/genuino101Examples/blob/master/image/test.png?raw=true)](https://youtu.be/WSktBhO94Ug)(동영상을 보려면 사진을 클릭하세요.)  

아두이노101은 Arduino.cc와 Intel 사이의 협업을 통해 만들어진 최신 장치 보드입니다. 미국 외에서는 Genuino101이라고 부릅니다.  

##### 더 많은 토픽 :  
[Make: $30 Gets You the Sensor-Packed, Curie-Powered Arduino 101](https://makezine.com/2015/10/16/30-gets-you-the-sensor-packed-curie-powered-arduino-101/)  
[Arduino/Genuino 101 CurieBLE CallbackLED](https://www.arduino.cc/en/Tutorial/Genuino101CurieBLECallbackLED)  

##### 부품 리스트 :  
1. 안드로이드 폰(BLE 내장 필요, 요즘 대부분의 안드로이드 폰은 걱정하지 않아도 됨)  
2. 아두이노101  
3. LED, 릴레이 모듈(옵션, 온보드 칩 LED를 바로 사용할 수 있음)  

### App Inventor  
기본적으로 이 프로젝트는 BLE콤포넌트를 제외하고는 [App Inventor and Arduino: Lesson 1: LED Blink](http://www.appinventor.tw/arduino_bt_blink)와 거의 같습니다. 우리는 여러분이 버튼을 누르고 있는 동안 아두이노101의 온보드 칩 LED가 깜빡이도록 제어하려고 합니다. 잊지 마세요. 여러분은 이 프로젝트를 통해 기본적인 스마트홈 데모를 만들 수 있는 진짜 LED들과 릴레이 모듈로 확장할 수 있습니다.  

#### Designer 
비슷합니다. 맞죠? 여러분은 종종 우리 튜토리얼의 이러한 종류의 인터페이스를 사용하게 될 것입니다. 하나의 ListPicker와 두개의 버튼 콤포넌트로 구성된 꽤 쉬운 인터페이스입니다. 그리고 블루투스 통신을 위한 하나의 Bluetooth Client 콤포넌트를 사용합니다. 아래의 설명을 확인하세요.  

1. ConnectButton(Button) : 이 프로젝트에서 아두이노101의 BLE 장치에 연결하기 위해 클릭합니다.  
2. TurnOnButton(Button) : 아두이노101에 "0"문자열을 보내기 위해 클릭합니다.  
3. TurnOffButton(Button) : 아두이노101에 "1"문자열을 보내기 위해 클릭합니다.  
4. Button_Disconnect(Button) : 안드로이드폰과 아두이노101사이의 연결을 닫기 위해  
5. *BluetoothLE(non visible) : BLE통신을 위한 콤포넌트, 여러분의 AI2 프로젝트에 BLE.aix파일을 임포트 하세요.  
