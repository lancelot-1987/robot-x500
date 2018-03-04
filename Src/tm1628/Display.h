#ifndef ROBOT_DISPLAY_H
#define ROBOT_DISPLAY_H

#include "../tm16xx/TM16XX.h"
#include "DisplayConstants.h"

static const int DELAY = 300;


void TM_Ext_Test(TM16XX *display);
void TM_Ext_Spot(TM16XX *display,bool on);
void TM_Ext_Clean(TM16XX *display,bool on);
void TM_Ext_Trash(TM16XX *display,bool on);
void TM_Ext_Home(TM16XX *display,bool on);
void TM_Ext_Plan(TM16XX *display,bool on);
void TM_Ext_Hours(TM16XX *display, int hours, bool on);
void TM_Ext_Minutes(TM16XX *display,int hours, bool on);
void TM_Ext_Line(TM16XX *display,const char *text);
void TM_Ext_Text(TM16XX *display,const char *text);
void TM_Ext_ClearText(TM16XX *display);
void TM_Ext_HeartBeat(TM16XX *display);


#endif //ROBOT_DISPLAY_H
