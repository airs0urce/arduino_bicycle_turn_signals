Arduino Bicycle Turn Signals
-------------------------

Arduino bicycle turn signals.

How it works
-------------------------

Press left button - turn on left led light or turn off left led light.  
Press right button - turn on right led light or turn off right led light.  

If left button pressed when right led light blinking, it will stop right led and start left.  
If left button pressed when left led light blinking, it will turn off left led light.
The same logic for right turn button.

https://www.youtube.com/watch?v=uAnk8ksx8WE


Known issues:
-------------------------

- If you press button down and hold it more than 350ms before release - it's possbile that it will be handled like second button press. I suppose it happens because of contacts bouncing. Soon I want to try to add hardware filter for this based on resistor and capacitor. If it will be working good then I'll add optional components to the schematics for those who wants to resolve that issue.

Schematics:
-------------------------

![turns 2_bb](https://user-images.githubusercontent.com/109203/99435769-2da0e980-2943-11eb-8295-d2389be3a972.jpg)


Components:
-------------------------

- One Arduino Pro Mini 3v 8Mhz.

- "FTDI FT232RL USB To TTL" to upload code to Arduino Pro Mini. Remember to change toggle to 3v on the board before connecting to Arduino Pro Mini. 
Also soldering is not required, just put FTDI pins in holes of Pro Mini and upload the sketch (BicycleTurnSignals.ino):
<img width="249" alt="Screen Shot 2020-11-19 at 12 13 53 AM" src="https://user-images.githubusercontent.com/109203/99563707-1e31a700-29fc-11eb-87d0-2210430bb450.png">


You can buy it here:
    [Link1](https://www.aliexpress.com/item/1005001636675031.html?spm=a2g0o.productlist.0.0.382162fcwDbMcN&algo_pvid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67&algo_expid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67-1&btsid=0bb0623416050047155106819ed6a9&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
    [Link2](https://www.aliexpress.com/item/32831177985.html?spm=a2g0o.productlist.0.0.382162fcwDbMcN&algo_pvid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67&algo_expid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67-5&btsid=0bb0623416050047155106819ed6a9&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
    [Link3](https://www.aliexpress.com/item/4000308024512.html?spm=a2g0o.productlist.0.0.382162fcwDbMcN&algo_pvid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67&algo_expid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67-12&btsid=0bb0623416050047155106819ed6a9&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
    
- LED lights. You can find LED lights that I used  by searching "1 Pair Truck Turn Indicators 12V" on aliexpress. I purchased 4 (2 for left and 2 for right side). 
(I used 12v LEDs because it's easier to find turn light like that. Actually you can find those working from 3.7 volt and then you don't even need 12v source like I have in schematics, you can power them from 3.7v battery too. 
You can buy the LEDs here:
    [Link1](https://www.aliexpress.com/item/4001028388076.html?spm=a2g0o.productlist.0.0.43454413XVxNj7&algo_pvid=8d6f320f-5e61-49a0-a128-c69a9eb959eb&algo_expid=8d6f320f-5e61-49a0-a128-c69a9eb959eb-2&btsid=0bb0623316050048266315715eb994&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
    [Link2](https://www.aliexpress.com/item/32800524061.html?spm=a2g0o.productlist.0.0.43454413XVxNj7&algo_pvid=8d6f320f-5e61-49a0-a128-c69a9eb959eb&algo_expid=8d6f320f-5e61-49a0-a128-c69a9eb959eb-6&btsid=0bb0623316050048266315715eb994&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
    [Link3](https://www.aliexpress.com/item/32799049355.html?spm=a2g0o.productlist.0.0.43454413XVxNj7&algo_pvid=8d6f320f-5e61-49a0-a128-c69a9eb959eb&algo_expid=8d6f320f-5e61-49a0-a128-c69a9eb959eb-7&btsid=0bb0623316050048266315715eb994&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)

- Two IRLB3034 mosfet transistors
- Two 10 kOhm and two 100 Ohm resistors.
- 3.7v battery with overdischarge protection. Any Li-ion or Li-pol battery fits perfectly. If you want to charge it from USB, buy TP4056 charging module and see how to connect it to battery in manuals on internet (there is a lot of them), TP4056 can also work as protection for non-protected battery. I didn't add the module to the schematics because I use 18650 Li-ion battery with protection [like this](https://www.aliexpress.com/item/32848096612.html?spm=a2g0o.productlist.0.0.605a7ddfCeC9Vi&algo_pvid=d45e67fb-7d36-4111-bcbd-4c9b9e63c3d7&algo_expid=d45e67fb-7d36-4111-bcbd-4c9b9e63c3d7-0&btsid=0b0a555616050870679444122e0161&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_), I put it inide holder on bicycle [like this](https://www.aliexpress.com/item/4000859859685.html?spm=a2g0o.productlist.0.0.58b53707JqadDe&algo_pvid=af3bb6cd-739b-4ee4-adf4-5221dc8fb32c&algo_expid=af3bb6cd-739b-4ee4-adf4-5221dc8fb32c-0&btsid=0b0a555e16050871046346208ea516&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_) and I take it off to charge using external charger.

You will need to remove power LED and voltage regulator from Arduino Pro Mini to save energy:
https://www.iot-experiments.com/arduino-pro-mini-power-consumption/
This way it will almost not eat energy while sleeping until you press BTN_LEFT or BTN_RIGHT.

Arduino must be powered using 3.7v battery (for example 18650, make sure battery is protected to make sure it's not overdischarged).

While sleeping the project is using about 5uA. It's about 20 years on 1000mAh battery, if I calculated correct :).  
While blinking the project is using 3mA current. About 14 days on 1000mAh battery.  
So, arduino itself will eat just a little energy. LED lamps will be eating most energy.

Btw, I use 12v battery made from 3 protected 18650 batteries connected in series and I power arduino itself from one one of those 3 batteries. I don't worry about disbalance between 3 batteries as arduino eats just a little of power. So this way you don't need second 3.7v battery, but can use one 12v battery made from 3). here is holder with 3 slots that I use:
[Link1](https://a.aliexpress.com/_9hQcJa), [Link2](https://a.aliexpress.com/_9fn2xK)

Here are photos. The red connector on second photo used to power arduino and wires from the connector go to one of those 3 batteries, so this way I get 3.7v for arduino. 

<img width="283" alt="Screen Shot 2020-11-19 at 12 12 14 AM" src="https://user-images.githubusercontent.com/109203/99563568-f8a49d80-29fb-11eb-883b-296069e90360.png">
<img width="214" alt="Screen Shot 2020-11-19 at 12 12 32 AM" src="https://user-images.githubusercontent.com/109203/99563550-f2162600-29fb-11eb-8444-8c597cf70b67.png">


To compile the source, you will need libraries installed in Arduino IDE: 
- LowPower: https://github.com/rocketscream/Low-Power (download source code and put everything to .../libraries/Low-Power/ folder)
- MsTimer2: https://github.com/PaulStoffregen/MsTimer2 (download source code and put everything to .../libraries/MsTimer2/ folder)


For info: 
- I connected LEDs to the bicycle using cable Ties and hot glue gun. This way they connected well enough to forget about fixing it later :)
- To connect turn buttons to handle I: put buttons on rectangular plastic pad, wrapper with heat-shrink tubing and used hot glue connected that to velcro strap. Then used the strap to connect buttons to the handle:

<img width="508" alt="Screen Shot 2020-11-19 at 12 11 18 AM" src="https://user-images.githubusercontent.com/109203/99563376-c5faa500-29fb-11eb-8e94-4ad6ca733fb5.png">

