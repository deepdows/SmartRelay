# SmartRelay
Smart relay is a socket that can be controled from any place with internet
## Installation
1. Install all libraries from folder "libraries" to arduino IDE.
2. Sign up on [CloudMQTT](https://api.cloudmqtt.com)
2. Enter your wifi name and password, and another data from dashbourd on cloudmqtt
3. Upload the sketch.
4. Connect like on the circuit.
5. Download [loT MQTT dashbourd](https://play.google.com/store/apps/details?id=com.thn.iotmqttdashboard&hl) on the phone from google play
6. When you open it first time you need to click on the button "+" and enter client ID (can be any, for example "smart_relay"), server, port, username and password, then press "create" in the top.

In the tab "subscribe" click on "+" and enter in the field Friendly name "Time for turning on" and in topic field " time1show". Do it 3 more time but with other data:
- Friendly name: "time for turning on", topic "time2show"
- Friendly name: "Check", topic "showcheck"
- Friendly name: "Check device", topic "showcheckrelay"

In the tab "publish":
1. Click on "+" and chose button, enter in the field Friendly name "Checking", topic field "check", button text "Check"and value to public "1". 
2. Click on "+" and chose TimePicker, enter in the field Friendly name "Time for turning on", topic field "time1", Time picker button label "Set", time format "24". 3. Click on "+" and chose TimePicker, enter in the field Friendly name "Time for turning off", topic field "time2", Time picker button label "Set", time format "24". 
4. Click on "+" and chose Switch, enter in the field Friendly name "Mode", topic field "mode", Text(On) "Manual", Text(Off) "Auto", publish value (On) "1", publish value (Off) "0". 
5. Click on "+" and chose Switch, enter in the field Friendly name "Manual mode", topic field "relay", Text(On) "On", Text(Off) "Off", publish value (On) "1", publish value (Off) "0". 

## Usage
Make sure the cloud in the top right is not filled with white!
In the tab "subscribe" you can watch the state of device. (device is the object that is controlled, light for example)
In the tab "publish" you can control your device.
There are two modes: automatic and manual. To use automatic you must set up time of turning off and on. Also you need your button to be on the "auto mode" selected. To use manual mode you need to click on "mode" section so it will be on "manual" selected and now you can press on "on" and "off" to turn on and off the device. 

You can check if your device is turned. Just press on "check" button and click on "subscribe" tab and you will see the state in section "Check".