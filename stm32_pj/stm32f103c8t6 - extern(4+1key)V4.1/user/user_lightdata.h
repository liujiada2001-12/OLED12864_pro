#ifndef __USER_LIGHTDATA_H
#define __USER_LIGHTDATA_H
#include "stdint.h"
void User_Data_Show(void);
void User_DataChoice_Show(int data_no);
void User_Detect_Show(void);
int User_DeleteData(int delete_no);

void lightdata_detect();
void lightdata_show();
void lightdata_up();
void lightdata_down();
void lightdata_askfordelete();
void lightdata_delete();
#endif 
