#ifndef SYSFS_GPIO_H_
#define SYSFS_GPIO_H_

// Called to configure the pin as an input or output
void gpioOutput(int pin);
void gpioInput(int pin);

// Called to set and output pin to a given value (1 or 0)
void gpioWrite(int pin, int value);

// Called to get the status (1 or 0) of a pin
int gpioRead(int pin);

#endif
