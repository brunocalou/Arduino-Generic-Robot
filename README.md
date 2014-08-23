Arduino-Generic-Robot
=====================

Arduino libraries made to create robots. The main target is to be useful on almost any arduino project.

Version
=====================
0.0.1

Installation
=====================

-Copy the all the folders to your arduino libraries path ( ../arduino/libraries )

-You can clone the project and the external libraries by using 
git clone --recursive git://github.com/brunocalou/Arduino-Generic-Robot

Next steps
=====================

<s>-Add light sensor class</s>

<s>-Add PID class</s> - Added from https://github.com/br3ttb/Arduino-PID-Library

-Add infrared sensor class

-Add filter class and use it on sensor class

-Add LED class

-Implement encoder, light and infrared sensors in the SensorBoard

-Improve Robot example

-Improve Ultrasonic class

-Improve SensorBoard class in order to accept external sensor libraries

-Improve Robot class so it can accept any character as a command (the user will choose the character to access a function, e.g. robot_object.setCommand('W', moveForward))

-Add PID example using the Robot class

-Add external libraries like MPU-9150, MPU-6050, XBee, Crystal Liquid Display, Ethernet, ...

-Add examples of all classes
