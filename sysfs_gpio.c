#include <stdio.h>

void gpioOutput(int pin)
{
    FILE* file;
    char str[35];
    file = fopen("/sys/class/gpio/export", "w");
    fprintf(file, "%d", pin);
    fclose(file);
    sprintf(str, "/sys/class/gpio/gpio%d/direction", pin);
    file = fopen(str, "w");
    fprintf(file, "out");
    fclose(file);
}

void gpioInput(int pin)
{
    FILE* file;
    char str[35];
    file = fopen("/sys/class/gpio/export", "w");
    fprintf(file, "%d", pin);
    fclose(file);
    sprintf(str, "/sys/class/gpio/gpio%d/direction", pin);
    file = fopen(str, "w");
    fprintf(file, "in");
    fclose(file);
}

void gpioWrite(int pin, int value)
{
    FILE* file;
    char str[35];
    sprintf(str, "/sys/class/gpio/gpio%d/value", pin);
    file = fopen(str, "w");
    fprintf(file, "%d", value);
    fclose(file);
}

int gpioRead(int pin)
{
    FILE* file;
    int result;
    char str[30];
    sprintf(str, "/sys/class/gpio/gpio%d/value", pin);
    file = fopen(str, "rw");
    fscanf(file, "%d", &result);
    fclose(file);
    return result;
}
