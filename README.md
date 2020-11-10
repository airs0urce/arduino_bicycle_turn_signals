Arduino Bicycle Turns
-------------------------

Arduino bicycle turns.

Components:

- One Arduino Pro Mini 3v 8Mhz.

- "FTDI FT232RL USB To TTL" to upload code to Arduino Pro Mini.  You can buy it here:
    https://www.aliexpress.com/item/1005001636675031.html?spm=a2g0o.productlist.0.0.382162fcwDbMcN&algo_pvid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67&algo_expid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67-1&btsid=0bb0623416050047155106819ed6a9&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_
    https://www.aliexpress.com/item/32831177985.html?spm=a2g0o.productlist.0.0.382162fcwDbMcN&algo_pvid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67&algo_expid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67-5&btsid=0bb0623416050047155106819ed6a9&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_
    https://www.aliexpress.com/item/4000308024512.html?spm=a2g0o.productlist.0.0.382162fcwDbMcN&algo_pvid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67&algo_expid=bcbd6b5a-d8f4-4580-876b-6e6965fb7b67-12&btsid=0bb0623416050047155106819ed6a9&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_

- LED lights. You can find LED lights that I used (12v. you can control any, but usually only 12v sold) by searching "1 Pair Truck Turn Indicators 12V" on aliexpress. I purchased 4 (2 for left and 2 for right side). You can buy it here:
    https://www.aliexpress.com/item/4001028388076.html?spm=a2g0o.productlist.0.0.43454413XVxNj7&algo_pvid=8d6f320f-5e61-49a0-a128-c69a9eb959eb&algo_expid=8d6f320f-5e61-49a0-a128-c69a9eb959eb-2&btsid=0bb0623316050048266315715eb994&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_
    https://www.aliexpress.com/item/32800524061.html?spm=a2g0o.productlist.0.0.43454413XVxNj7&algo_pvid=8d6f320f-5e61-49a0-a128-c69a9eb959eb&algo_expid=8d6f320f-5e61-49a0-a128-c69a9eb959eb-6&btsid=0bb0623316050048266315715eb994&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_
    https://www.aliexpress.com/item/32799049355.html?spm=a2g0o.productlist.0.0.43454413XVxNj7&algo_pvid=8d6f320f-5e61-49a0-a128-c69a9eb959eb&algo_expid=8d6f320f-5e61-49a0-a128-c69a9eb959eb-7&btsid=0bb0623316050048266315715eb994&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_

- Two IRLB3034 mosfet transistors

You will need to remove power LED and voltage regulator from Arduino Pro Mini to save energy:
https://www.iot-experiments.com/arduino-pro-mini-power-consumption/
This way it will almost not eat energy while sleeping until you press BTN_LEFT or BTN_RIGHT.

Arduino must be powered using 3.7v battery (for example 18650, make sure battery is protected to make sure it's not overdischarged).

While sleeping the project is using about 150uA. It's about 10 months on 1000mAh battery.
While blinking the project is using 3mA current. About 14 days on 1000mAh battery.
So, arduino itself will eat just a little energy. LED lamps will be eating most energy.

How it works: https://www.youtube.com/watch?v=5mdGutMXXeE&feature=youtu.be


Schematics:

![turns_bb](https://user-images.githubusercontent.com/109203/98668673-cd2e0d00-2382-11eb-9139-51e54b6c9164.png)
