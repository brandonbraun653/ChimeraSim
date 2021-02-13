# Virtual Peripherals

The main goal behind a virtual peripheral is that it simulates the functionality of hardware to allow
writing complex higher layer software more quickly and in a more testable manner.


1. Communicate with the outside world
2. Swap behaviors at runtime to facilitate testing
3. Easily extendable


## Simulator Use Case
One functionality that I would find useful is exposing the hardware interfaces of the system to the outside
world so that virtual device models and virtual "wires" can be connected up. For example, an accelerometer
model in Python could communicate with the SPI connection and transfer bytes back and forth, whether they are
real data or fake. This would allow writing a test framework in a much more expressive/powerful language and
make injecting data to test system performance much easier.