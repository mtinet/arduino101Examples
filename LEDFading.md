# [앱 인벤터 IoT]
## 레슨 2 : 아두이노101 Fading(PWM)

이 문서는 아두이노 101의 BLE(Bluetooth Low Energy, Bluetooth 4.0)를 앱인벤터로 조작하는 구현하는 방법에 대한 문서입니다.  

여기에서 연재되고 있는 레슨들은 다양한 방법으로 앱인벤터와 아두이노 101(BLE)가 상호작용 할 수 있는 방법을 설명해줍니다. 단, 여러분이 이 기능을 사용하기 위해서 [반드시 BLE컴포넌트를 확장자로 Import](http://appinventor.mit.edu/extensions/)시켜야합니다.

실제 앱의 디자인, 회로도, 구동영상은 다음과 같습니다.
![](https://github.com/mtinet/arduino101Examples/blob/master/image/8.png?raw=true)  
![](https://github.com/mtinet/arduino101Examples/blob/master/image/16.png?raw=true)  
[![](https://github.com/mtinet/arduino101Examples/blob/master/image/8.png?raw=true)](https://youtu.be/ihMyDoxapBQ)  

## App Inventor
기본적으로, 해당 예제는 [앱인벤터와 아두이노 : 레슨1. LED 깜빡임] 예제와 BLE컴포넌트를 사용한다는 점을 제외하고는 거의 같다. 해당 예제어스 우리는 아두이노101에 내장된 D9 LED의 밝기를 슬라이더를 통해 제어하고자 한다.

### Designer Page

Clock컴포넌트는 정기적으로 LED의 밝기를 제어하는 슬라이더포인터의 위치를 BLE 컴포넌트를 통해 아두이노101보드에 보낸다. 슬라이더 포인터의 위치는 또한 텍스트상자를 통해서도 보여진다. 단, 해당예제를 실행할 때 사용하는 통신프로토콜이 다르기 때문에 기존의 블루투스클라이언트 컴포넌트를 사용해서는 아두이노와 통신할 수 없다. 

### Blocks

##### 초기화 및 연결
BluetoothLE1을 이용하여 사용가능한 디바이스를 검색한다. (아두이노101이 준비 된 상태에서 연결)

다음으로, ConnectButton과 ConnectButton.Click창에서 BlutoothLE1를 선택하여 특정지어진 기기를 연결하도록 한다. 사용하고 있는 아두이노101의 블루투스 주소를 입력하고(98:04- ...) 사용하고 있는 아두이노101에 따라 주소 문자열을 정한다.

##### 연결 확인

연결이 된 후에 BLuetootheLE!.Connected 창이 다음과 같이 불려질 것이다.

##### 연속전송신호

Clock을 이용한다. Timer에게 다음 두 작업을 매 0.1초마다 완성하기 위해 명령을 내린다. 
 ⦁TextBox에서 슬라이더의 포인터 위치를 표시합니다.
 ⦁Bluetoothgec.writeIntValue명령을 사용하여 포인터 위치를 전송한 다음 이 정보는 아두이노101에서 LED의 밝기     를 제어할 수 있게한다. Type in ‘19....“ in both service_uuid and characteristic_uuid columns. 아두이노 101은 이를 BLE서비스의 척도로 사용한다.

##### 연결 해제
Button_Disconnect 버튼을 누르면, BluetoothLE1컴포넌트가 기기에서 연결해제된다.


## Arduino 101 Code

다음 code를 아두이노101에 복사/붙여넣기해라. 아두이노 101에 BLE가 내장되어 있기 때문에 따로 별도의 Bluetoothe연결은 필요하지 않다. (HC05같은)
