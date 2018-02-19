#ifndef ROBOT_DISPLAY_H
#define ROBOT_DISPLAY_H

#include "../tm16xx/TM16XX.h"
#include "DisplayConstants.h"

static const int DELAY = 300;


void TM_Ext_Test(struct TM16XX *display);
void TM_Ext_Spot(struct TM16XX *display,bool on);
void TM_Ext_Clean(struct TM16XX *display,bool on);
void TM_Ext_Trash(struct TM16XX *display,bool on);
void TM_Ext_Home(struct TM16XX *display,bool on);
void TM_Ext_Plan(struct TM16XX *display,bool on);
void TM_Ext_Hours(struct TM16XX *display, int hours, bool on);
void TM_Ext_Minutes(struct TM16XX *display,int hours, bool on);
void TM_Ext_Line(struct TM16XX *display,const char *text);
void TM_Ext_Text(struct TM16XX *display,const char *text);
void TM_Ext_ClearText(struct TM16XX *display);
void TM_Ext_HeartBeat(struct TM16XX *display);


#endif //ROBOT_DISPLAY_H
