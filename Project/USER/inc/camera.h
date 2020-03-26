#ifndef __CAMERA_H
#define __CAMERA_H

#include "headfile.h"
#include "init.h"

#define THRESHOLD   30

void OTUS(uint8 *image, uint16 col, uint16 row); 
void image_scan(void);
void find_line(void);

#endif