#include <stdbool.h>

bool sendData(const char ipv4Address[], int port, const char str[]);
bool openListenerPort(const char ipv4Address[], int port);
void receiveData(char str[], int str_length);
void closeListenerPort();
