# SmartRelay
Smart relay is a socket that can be controlled from any place with internet
## Installation
1. Install all libraries from folder "libraries" to arduino IDE.
2. Sign up on [CloudMQTT](https://api.cloudmqtt.com)
2. Enter your wifi name and password, and another data from dashbourd on cloudmqtt
3. upload the sketch.
4. connect like on the circuit.
5. download [loT MQTT dashbourd](https://play.google.com/store/apps/details?id=com.thn.iotmqttdashboard&hl) on the phone from google play
## Usage
Make sure the clound in the top right is not filled with white!
In the tab "subscribe" you can watch the state of device. (device is the object that is controlled, light for example)
In the tab "publish" you can control your device.
There are two modes: automatic and manual. To use automatic you must set up time of turning off and on. Also you need your button to be on the "automatic mode" selected. To use manual mode you need to click on "mode" section so it will be on "manual" selected and now you can press on "on" and "off" to turn on and off the device. 
You can check if your device is turned. Just press on "check" button and click on "subscribe" tab and you will see the state in section "Check".