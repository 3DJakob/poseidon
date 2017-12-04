# What is poseidon?
Poseidon is an Arduino program for watering your plants. This program is intended for the Arduino nano but works with other Arduinos as well. It controls a relay that turns on and off a water pump when the soil is to dry. It also has support for 2 LEDs for status updates. A 3 position switch is required for operation.

# parts list
Required
* Ardunio Nano
* Water pump
* Relay
* Soil Hygrometer
* Water container
* 3 position switch

Optional
* Blue LED
* Green LED

Miscellaneous
* Resistors
* Wires
* Connectors
* DC Power adapter

# wiring
The pin numbers for wiring are as follows and can be adjusted in the `poseidon.ino` file

```arduino
int relayPin = 3;
int bluePin = 4;
int greenPin = 5;
int offPin = 6;
int waterPin = 9;
int sensePin = A0;
```
The `offPin` and `waterPin` should each be on the oposite side of the 3 position switch.
