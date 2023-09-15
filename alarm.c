// Main Burglar Alarm Application

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <unistd.h>
#include "sysfs_gpio.h"
#include "udp.h"

#define SERVER_LISTENER_PORT 4096

#define TIMEOUT_SECONDS 25

bool isAnyKeyPressed()
{
    struct pollfd pfd;
    pfd.fd = 1;
    pfd.events = POLLIN;
    poll(&pfd, 1, 1);
    return pfd.revents == POLLIN;
}

int main(int argc, char* argv[])
{
    char *remoteIp;
    int remotePort;
    bool armed = false;
    bool quit = false;
    int timeout = TIMEOUT_SECONDS;

    // Verify arguments are good
    bool goodArguments = (argc == 2);
    if (goodArguments)
        remoteIp = argv[1];
    if (!goodArguments)
    {
        printf("usage: alarm IPV4_ADDRESS\n");
        printf("  where:\n");
        printf("  IPV4_ADDRESS is address of the remote machine\n");
        exit(EXIT_FAILURE);
    }

    // Set remote port
    remotePort = SERVER_LISTENER_PORT;

    // Setup pins as inputs
    gpioInput(26);
    gpioInput(21);
    gpioInput(6);



    // Send disarmed message
    sendData(remoteIp, remotePort, "disarmed");

    // Loop until 'q' is pressed on keyboard
    while (!quit)
    {

        //read the MOTION sensor
        if ((gpioRead(26)==1) && (armed==false))
        {
            sendData(remoteIp, remotePort, "armed" ) ;
            printf("Arming system\n");
            armed = true;
        }


        else if ((gpioRead(26)==1) && (armed==true))
        {
            sendData(remoteIp, remotePort, "disarmed" ) ;
            printf("disarming system\n");
            armed = false;
        }


        //send messages and display on screen
        if ((gpioRead(6)==1) && (armed==true))
        {
            sendData(remoteIp, remotePort, "door" ) ;
            printf("Door open\n");
        }

        //read the ARM/DISARM push button
        if ((gpioRead(21)==1) && (armed==true))
        {
            sendData(remoteIp, remotePort, "motion" ) ;
            printf("motion detected\n");
        }


        //Get key or quit
        if (isAnyKeyPressed())
        {
            char c = fgetc(stdin);
            if (c == 'q')
                break;
        }


        // Sleep for 1 second
        // When the timeout reaches zero:
        //       - send a pulse message to keep connection alive
        //       - reload the timeout variable with TIMEOUT_SECONDS
        if (!quit)
        {
            usleep(1000000);

            timeout--;
            if (timeout == 0) {
                sendData(remoteIp, remotePort, "pulse");
                timeout= TIMEOUT_SECONDS;
            }
        }
    }
    return EXIT_SUCCESS;
}
