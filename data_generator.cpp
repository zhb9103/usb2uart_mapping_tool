

#include "data_generator.h"





DataGenerator::DataGenerator()
{
}

DataGenerator::~DataGenerator()
{
}


void DataGenerator::genIdUSB(const char *idVendor,const char *idProduct,const char *product,const char *serial,const int usbNumber,char *pIdUSB,const char debugEnable)
{
  sprintf(pIdUSB,"ATTRS{idVendor}==\"%s\",ATTRS{idProduct}==\"%s\",ATTRS{product}==\"%s\",ATTRS{serial}==\"%s\",ENV{UV_USB%02d_EN}=\"1\"",idVendor,idProduct,product,serial,usbNumber);
#if 1
  if(debugEnable)
  {
    printf("%s\n",pIdUSB);
  }
#endif
}

void DataGenerator::genIdUART(const int interfaceNumber,const int usbNumber,const int boxNumber,const int uartNumber,char *pIdUART,const char debugEnable)
{
  sprintf(pIdUART,"ATTRS{bInterfaceNumber}==\"%02d\",ENV{UV_USB%02d_EN}==\"1\",MODE=\"0777\",SYMLINK+=\"box%d_UART%02d\"",interfaceNumber,usbNumber,boxNumber,uartNumber);
#if 1
  if(debugEnable)
  {
    printf("%s\n",pIdUART);
  }
#endif
}






