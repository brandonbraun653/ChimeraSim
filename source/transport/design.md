Serial Data Transfer
- SPI
- UART
- USART

Network Data Transfer
- CAN

Data Generation
- ADC

System Control & Reaction
- Clock
- EXTI
- GPIO
- System
- Watchdog


The main problem is how to inject functionality of the peripheral.
https://www.fluentcpp.com/2019/06/07/write-your-own-dependency-injection-container/

I think what might be a good idea is to have the simulator be able to accept both the generic "sim" variant
that always succeeds (return codes success but no data flow yet), then also be able to accept mock objects.
The key to this is going to be virtual classes.

The actual sim driver has to implement the physical class defined in the peripheral interface, but this physical
class is based on a virtual driver interface. Both the mock and the sim driver can inherit this interface and
then be registered with the real class implementation. I think this is going to require another interface to actually
create the class type and then another to inject it?

The main point is that I need to inject varied driver functionality based on the kind of virtual driver I'm doing.