/*
 * Created in 2025.05
 * Copyright reserved.
 */

#ifndef __DATA_GENERATOR_H__
#define __DATA_GENERATOR_H__
#include "stdio.h"
#include "stdlib.h"
#include "string.h"






class DataGenerator
{
public:
  DataGenerator();
  ~DataGenerator();



public:
  /*
   * genIdUSB
   */
  static void genIdUSB(const char *idVendor,const char *idProduct,const char *product,const char *serial,const int usbNumber,char *pIdUSB,const char debugEnable);
  
  /*
   * genIdUART
   */
  static void genIdUART(const int interfaceNumber,const int usbNumber,const int boxNumber,const int uartNumber,char *pIdUART,const char debugEnable);


};

#endif


