# sdvxplus-controller

This is my fully custom Sound Voltex (sdvx) controller running on Arduino that has enough buttons to play pretty much any other mania style rhythm game.
![20211203_172135_2](https://user-images.githubusercontent.com/95504904/144685637-27c9d163-fd02-41ed-aade-0c5286d8aecc.jpg)

![20211203_172153](https://user-images.githubusercontent.com/95504904/144685624-b5832a84-6c20-4893-8d42-1e8b78b1f5c0.jpg)

# Inside of the device
My soldering job definitely could have been better.
![20211203_172239](https://user-images.githubusercontent.com/95504904/144685686-63fd70cf-d52d-41be-a5ec-e37da81962b6.jpg)


# Notes
- The case, knobs and keycaps were designed in Fusion 360 and 3D printed by me.
- Code written in Arduino using the Keyboard, Mouse, and Encoder libraries.
- Using standard mechanical keyboard switches - in this case Kailh Box Navy switches
- The microcontroller is a SparkFun Qwiic Pro Micro - USB-C (ATmega32U4)
- I definitely could have simplified the design by using the internal pull up resistors on the microcontroller rather than external pull down resistors like I am currently using.




I was inspired by other projects like  
https://github.com/speedypotato/Pocket-SDVX  
https://github.com/mon/PocketVoltex  
but I wanted a device that could handle more inputs so I got to work on making my own.
