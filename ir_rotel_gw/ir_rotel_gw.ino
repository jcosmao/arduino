#include <IRremote.h>
#include "test.h"
#define PIN_LED 3
#define PIN_IRRECV 4

char debug[100];
IR ircatch;

IRrecv irrecv(PIN_IRRECV);
IRsend irsend;
decode_results results;

void setup() {
    Serial.begin(9600);
    Serial.println("Init");

    irrecv.enableIRIn();
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    // poll IR receiver for signal
    receiveCode(&ircatch);

    // Receiving code from Arduino remote
    if (ircatch.codeType == NEC) {

        switch (ircatch.codeValue) {
            case ARDUINO_VOL_UP:
                sendRotelCode(ROTEL_VOL_UP);
                break;
            case ARDUINO_VOL_DOWN:
                sendRotelCode(ROTEL_VOL_DOWN);
                break;
            case ARDUINO_VOL_PAUSE:
                sendRotelCode(ROTEL_VOL_MUTE);
                break;
            case ARDUINO_POWER:
                sendRotelCode(ROTEL_POWER);
                break;
            case ARDUINO_1:
                sendRotelCode(ROTEL_SRC_CD);
                break;
            case ARDUINO_2:
                sendRotelCode(ROTEL_SRC_AUX1);
                break;
            case ARDUINO_3:
                sendRotelCode(ROTEL_SRC_AUX2);
                break;
            default:
                Serial.println("[DEBUG] No mapping found !");
        }
    }

    // Receiving code from Samsung remote
    if (ircatch.codeType == SAMSUNG || ircatch.codeType == 11) {

        switch (ircatch.codeValue) {
            case TV_UP:
                sendRotelCode(ROTEL_VOL_UP);
                break;
            case TV_DOWN:
                sendRotelCode(ROTEL_VOL_DOWN);
                break;
            case TV_ENTER:
                sendRotelCode(ROTEL_VOL_MUTE);
                break;
            case TV_A:
                sendRotelCode(ROTEL_POWER);
                break;
            case TV_B:
                sendRotelCode(ROTEL_SRC_CD);
                break;
            case TV_C:
                sendRotelCode(ROTEL_SRC_AUX1);
                break;
            case TV_D:
                sendRotelCode(ROTEL_SRC_AUX2);
                break;
            default:
                Serial.println("[DEBUG] No mapping found !");
        }
    }
}

void receiveCode(IR *i) {

    if (irrecv.decode(&results))
    {
        i->codeType = results.decode_type;
        // handle button pressed without interuption (codeLen = 0 and codeValue = -1)
        if (results.bits > 0) {
            i->codeLen = results.bits;
            i->codeValue = results.value;
        }
        irrecv.resume(); // Receive the next value

        sprintf(debug, "[DEBUG] Got IR msg: codeType = %d, codeLen = %d, codeValue = %ld", i->codeType, i->codeLen, i->codeValue);
        Serial.println(debug);
    }
    else {
        // reset all value to -1
        i->codeType = -1;
    }
}

void sendRotelCode(long code) {
    irsend.sendNEC(code, ROTEL_CODE_LEN);
    sprintf(debug, "[DEBUG] Sended IR msg: codeType: NEC (rotel), codeValue = %ld", code);
    Serial.println(debug);
    // reenable ir recv
    irrecv.enableIRIn();
}
