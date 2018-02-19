#include <string.h>
#include "Display.h"
#include "DisplayConstants.h"

void TM_Ext_Test(struct TM16XX *display) {

    TM_clear(display);
    TM_Ext_Spot(display, true);
    TM_Delay(DELAY);
    TM_Ext_Spot(display, false);
    TM_Delay(DELAY);
    TM_Ext_Clean(display, true);
    TM_Delay(DELAY);
    TM_Ext_Clean(display, false);
    TM_Delay(DELAY);
    TM_Ext_Home(display, true);
    TM_Delay(DELAY);
    TM_Ext_Home(display, false);
    TM_Delay(DELAY);
    TM_Ext_Plan(display, true);
    TM_Delay(DELAY);
    TM_Ext_Plan(display, false);
    TM_Delay(DELAY);
    TM_Ext_Trash(display, true);
    TM_Delay(DELAY);
    TM_Ext_Trash(display, false);
    TM_Delay(DELAY);
    TM_Ext_Text(display, "ERR!");
    int i = 0;
    for (i = 0; i < 30; ++i) {
        TM_Ext_Minutes(display, i, true);
        TM_Delay(DELAY);
    }
    TM_Ext_Minutes(display, 0, false);
    i = 0;
    for (i = 0; i < 30; ++i) {
        TM_Ext_Hours(display, i, true);
        TM_Delay(DELAY);
    }
    TM_Ext_Hours(display, 0, false);

}
void TM_Ext_Spot(struct TM16XX *display, bool on) {
    TM_sendData(display, SPOT_ADDR1, on ? ON_HALF1 : OFF);
    TM_sendData(display, SPOT_ADDR2, on ? ON_HALF2 : OFF);
}
void TM_Ext_Clean(struct TM16XX *display, bool on) {
    TM_sendData(display, CLEAN_ADDR, on ? ON_FULL : OFF);
}
void TM_Ext_Hours(struct TM16XX *display, int hours, bool on) {
    TM_sendData(display, SEG1_ADDR, on ? NUMBER_FONT[hours / 10] : OFF);
    TM_sendData(display, SEG2_ADDR, on ? NUMBER_FONT[hours % 10] : OFF);
}
void TM_Ext_Minutes(struct TM16XX *display, int hours, bool on) {
    TM_sendData(display, SEG3_ADDR, on ? NUMBER_FONT[hours / 10] : OFF);
    TM_sendData(display, SEG4_ADDR, on ? NUMBER_FONT[hours % 10] : OFF);
}
void TM_Ext_Line(struct TM16XX *display, const char *text) {
    display->buffer = text;
    if (display->bufferPosition >= strlen(display->buffer)) {
        display->bufferPosition = 0;
    }
    TM_sendData(display, SEG1_ADDR, FONT_DEFAULT[display->buffer[display->bufferPosition] - 32]);
    TM_sendData(display, SEG2_ADDR, FONT_DEFAULT[display->buffer[display->bufferPosition + 1] - 32]);
    TM_sendData(display, SEG3_ADDR, FONT_DEFAULT[display->buffer[display->bufferPosition + 2] - 32]);
    TM_sendData(display, SEG4_ADDR, FONT_DEFAULT[display->buffer[display->bufferPosition + 3] - 32]);
    display->bufferPosition++;
    TM_Delay(DELAY);
}
void TM_Ext_Text(struct TM16XX *display, const char *text) {
    display->buffer = text;
    display->bufferPosition = 0;
    TM_sendData(display, SEG1_ADDR, FONT_DEFAULT[display->buffer[0] - 32]);
    TM_sendData(display, SEG2_ADDR, FONT_DEFAULT[display->buffer[1] - 32]);
    TM_sendData(display, SEG3_ADDR, FONT_DEFAULT[display->buffer[2] - 32]);
    TM_sendData(display, SEG4_ADDR, FONT_DEFAULT[display->buffer[3] - 32]);
}
void TM_Ext_Trash(struct TM16XX *display, bool on) {
    TM_sendData(display, TRASH_ADDR, on ? ON : OFF);
}
void TM_Ext_Home(struct TM16XX *display, bool on) {
    TM_sendData(display, HOME_ADDR1, on ? ON_HALF1 : OFF);
    TM_sendData(display, HOME_ADDR2, on ? ON_HALF2 : OFF);
}
void TM_Ext_Plan(struct TM16XX *display, bool on) {
    TM_sendData(display, PLAN_ADDR, on ? ON : OFF);
}
void TM_Ext_ClearText(struct TM16XX *display) {
    TM_Ext_Text(display, "    ");
}


void TM_Ext_HeartBeat(struct TM16XX *display) {
    for (int i = 0; i < 7; i++) {
        TM_Brightness(display, true, i);
        TM_Delay(10);
    }
    for (int i = 7; i > 0; i--) {
        TM_Brightness(display, true, i);
        TM_Delay(10);
    }

}
