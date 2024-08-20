#ifndef _MENU_H_
#define _MENU_H_
#include "zf_common_headfile.h"

void UI();

void DisplayCursor();
void UI_ContentKey(void);
void UI_Content(void);
void UI_Datapage(void);
void UI_DatapageKey(void);

uint8 pagenumup(void);
uint8 pagenumdown(void);

void DisplayMain(void);
void DisplayMt9v03Para(void);
void DisplayOpenArtPara(void);
void DisplaySpeedPara(void);
void DisplayServoPara(void);
void DisplayIMUPara(void);
void DisplayElementPara(void);
void DisplayStartPara(void);
void DisplayImage(void);

#endif