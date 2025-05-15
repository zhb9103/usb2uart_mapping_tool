
#ifndef __GET_INFO_H__
#define __GET_INFO_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <regex>



using namespace std;

class GetInfo
{
public:
  GetInfo();
  ~GetInfo();


public:
  static int getUSBInfo(std::list<std::string> &listPara);
  static int getBOXInfo(const char *pUSBDevice,std::string &boxStr);



};





#endif


