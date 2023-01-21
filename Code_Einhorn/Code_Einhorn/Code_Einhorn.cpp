#include "MicroBit.h"

#if MICROBIT_BLE_ENABLED
#ifdef YOTTA_CFG
#error "This example needs BLE to be disabled. Use the yotta config.json in the proximit-heart directory to do this"
#else
#error "This example needs BLE to be disabled in the microbit config file in the microbit-dal: MicroBitConfig.h"
#endif
#endif
//MicroBit initialisieren
MicroBit uBit;


//Arrays für Displayanzeige

//Stop
const uint8_t stop_arr[]{
        1, 0, 0, 0, 1,
        0, 1, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 1, 0,
        1, 0, 0, 0, 1, };

//Vorwärts
const uint8_t vor_arr[]{
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0,
        1, 0, 1, 0, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, };

//Rückwärts
const uint8_t backward_arr[]{
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        1, 0, 1, 0, 1,
        0, 1, 1, 1, 0,
        0, 0, 1, 0, 0, };

//Rechts
const uint8_t right_arr[]{
        0, 0, 1, 0, 0,
        0, 0, 0, 1, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, };

//Links
const uint8_t left_arr[]{
        0, 0, 1, 0, 0,
        0, 1, 0, 0, 0,
        1, 1, 1, 1, 1,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, };

//Signalverlust
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

//Funktionen für Motorsteuerung im Remotemodus
void mForward() {
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(100);
    uBit.io.P1.setAnalogValue(500);
    uBit.io.P1.setAnalogPeriodUs(100);
}
void mRight() {
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(100);
    uBit.io.P1.setAnalogPeriodUs(0);
    uBit.io.P1.setAnalogValue(100);
}
void mLeft() {
    uBit.io.P0.setAnalogValue(0);
    uBit.io.P0.setAnalogPeriodUs(100);
    uBit.io.P1.setAnalogValue(500);
    uBit.io.P1.setAnalogPeriodUs(100);
}
void mStop() {
    uBit.io.P0.setAnalogValue(0);
    uBit.io.P0.setAnalogPeriodUs(0);
    uBit.io.P1.setAnalogValue(0);
    uBit.io.P1.setAnalogPeriodUs(0);
    uBit.display.scroll(stop);
    uBit.sleep(1);
}

//Fester Weg für Einhorn
void onButtonA()
{
    uBit.display.scroll("GO");
    //gerade aus fahren
    uBit.display.print(vor);
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(1500);
    uBit.io.P1.setAnalogValue(500);
    uBit.io.P1.setAnalogPeriodUs(1500);
    uBit.sleep(1000);

    //90°Rechtskurve
    uBit.display.print(right);
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(1000);
    uBit.io.P1.setAnalogPeriodUs(0);
    uBit.io.P1.setAnalogValue(100);
    uBit.sleep(1000);

    //gerade aus fahren
    uBit.display.print(vor);
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(1500);
    uBit.io.P1.setAnalogValue(500);
    uBit.io.P1.setAnalogPeriodUs(1500);
    uBit.sleep(1000);

    //Kreis im Uhrzeigersinn
    uBit.display.print(right);
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(1500);
    uBit.io.P1.setAnalogValue(300);
    uBit.io.P1.setAnalogPeriodUs(1500);
    uBit.sleep(1000);

    //gerade aus fahren
    uBit.display.print(vor);
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(1500);
    uBit.io.P1.setAnalogValue(500);
    uBit.io.P1.setAnalogPeriodUs(1500);
    uBit.sleep(1000);

    //Im gegenuhrzeigersinn drehen
    uBit.display.print(left);
    uBit.io.P0.setAnalogValue(0);
    uBit.io.P0.setAnalogPeriodUs(0);
    uBit.io.P1.setAnalogValue(500);
    uBit.io.P1.setAnalogPeriodUs(2500);
    uBit.sleep(1000);

    //gerade aus fahren
    uBit.display.print(vor);
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(1500);
    uBit.io.P1.setAnalogValue(500);
    uBit.io.P1.setAnalogPeriodUs(1500);
    uBit.sleep(1000);

    //90° rechtskurve
    uBit.display.print(right);
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(800);
    uBit.io.P1.setAnalogValue(0);
    uBit.io.P1.setAnalogPeriodUs(100);
    uBit.sleep(1000);

    //Im uhrzeigersinn drehen
    uBit.display.print(right);
    uBit.io.P0.setAnalogValue(500);
    uBit.io.P0.setAnalogPeriodUs(100);
    uBit.io.P1.setAnalogValue(0);
    uBit.io.P1.setAnalogPeriodUs(100);
    uBit.sleep(1000);

    //ende
    uBit.io.P0.setAnalogValue(0);
    uBit.io.P0.setAnalogPeriodUs(0);
    uBit.io.P1.setAnalogValue(0);
    uBit.io.P1.setAnalogPeriodUs(0);
    uBit.display.print("O");
    uBit.sleep(1);

}

//Funktion für Remotemodus
void onData(MicroBitEvent)
{
    while (1) {

        ManagedString s = uBit.radio.datagram.recv();
        if (s == "1") {
            uBit.display.scroll(vor);
            mForward();
            ManagedString s = uBit.radio.datagram.recv();

        }
        else if (s == "3") {
            uBit.display.scroll(right);
            mRight();
            ManagedString s = uBit.radio.datagram.recv();

        }
        else if (s == "4") {
            uBit.display.scroll(left);
            mLeft();
            ManagedString s = uBit.radio.datagram.recv();

        }
        else if (s == "5") {
            uBit.display.scroll(stop);
            mStop();
            ManagedString s = uBit.radio.datagram.recv();
        }
        else if (s == "20") {
            uBit.display.scroll("Go");
            onButtonA();
            ManagedString s = uBit.radio.datagram.recv();

        }
        else if (uBit.buttonA.isPressed()) {
            onButtonA();
        }

    }
}
//Kein Kontakt zur Fernsteuerung und keine Eingabe, Buzzer Piep
void search(int dauer) {
    uBit.io.P2.setAnalogValue(1000);
    uBit.io.P2.setAnalogPeriod(1);

    uBit.sleep(dauer);

    uBit.io.P2.setAnalogValue(0);
    uBit.io.P2.setAnalogPeriod(0);
}

int main()
{
    //Initialisierungen
    uBit.init();

    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
    uBit.radio.enable();

    //Motor Links
    uBit.io.P0.isAnalog();
    uBit.io.P0.isOutput();
    //Motor Rechts
    uBit.io.P1.isAnalog();
    uBit.io.P1.isOutput();
    //Buzzer
    uBit.io.P2.isAnalog();
    uBit.io.P2.isOutput();

    while (1) {
        //Aufruf auf MicroBit Einhorn für den Festgesetzten Weg, ohne Fernsteuerung
        uBit.sleep(1);
    }
}
