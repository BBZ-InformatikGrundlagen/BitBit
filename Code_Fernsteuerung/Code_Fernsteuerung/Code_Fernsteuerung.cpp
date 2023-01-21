#include "MicroBit.h"

#if MICROBIT_BLE_ENABLED 
#ifdef YOTTA_CFG
#error "This example needs BLE to be disabled. Use the yotta config.json in the proximit-heart directory to do this"
#else
#error "This example needs BLE to be disabled in the microbit config file in the microbit-dal: MicroBitConfig.h"
#endif
#endif

MicroBit uBit;

//Arrays für Displayanzeige

const uint8_t stop_arr[]{
        1, 0, 0, 0, 1,
        0, 1, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 1, 0,
        1, 0, 0, 0, 1, };

const uint8_t vor_arr[]{
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0,
        1, 0, 1, 0, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, };

const uint8_t backward_arr[]{
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        1, 0, 1, 0, 1,
        0, 1, 1, 1, 0,
        0, 0, 1, 0, 0, };

const uint8_t right_arr[]{
        0, 0, 1, 0, 0,
        0, 0, 0, 1, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, };

const uint8_t left_arr[]{
        0, 0, 1, 0, 0,
        0, 1, 0, 0, 0,
        1, 1, 1, 1, 1,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, };

const uint8_t noContact_arr[]{
        1, 0, 1, 0, 1,
        1, 0, 1, 0, 1,
        1, 0, 1, 0, 1,
        0, 0, 0, 0, 0,
        1, 0, 1, 0, 1, };

MicroBitImage stop(5, 5, stop_arr);
MicroBitImage vor(5, 5, vor_arr);
MicroBitImage backward(5, 5, backward_arr);
MicroBitImage right(5, 5, right_arr);
MicroBitImage left(5, 5, left_arr);
MicroBitImage noContact(5, 5, noContact_arr);


//Funktion für Remotemodus mit Gestensteuerung
void onButtonA()
{
    while (1) {
        int x = uBit.accelerometer.getX();
        int y = uBit.accelerometer.getY();
        if (y < -100) {
            uBit.radio.datagram.send("1");
            uBit.display.print(vor);
        }
        else if (x > 100) {
            uBit.radio.datagram.send("3");
            uBit.display.print(right);
        }
        else if (x < -100) {
            uBit.radio.datagram.send("4");
            uBit.display.print(left);
        }
        else if (y > 200) {
            uBit.radio.datagram.send("5");
            uBit.display.print(stop);
            break;
        }
    }
}

//Funktion um 
void onButtonB()
{
    uBit.radio.datagram.send("20");
    uBit.display.print("GO");
}

/* We toggle broadcasting if both buttons are pressed together */
void onButtonAB()
{
    uBit.radio.datagram.send("21");
    uBit.display.print("FREE");
}

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();


    uBit.radio.enable();

    while (1) {
        if (uBit.buttonA.isPressed()) {
            onButtonA();
        }
        else if (uBit.buttonB.isPressed()) {
            onButtonB();
        }

        uBit.sleep(1000);
    }
}