

#include "get_info.h"



GetInfo::GetInfo()
{
}



GetInfo::~GetInfo()
{
}


int GetInfo::getUSBInfo(std::list<std::string> &listPara)
{
  // find /dev/ -name "ttyUSB*"
  FILE *fp;
  char usb_content_buffer[1024]={0};
  int usb_counter=0;

  fp = popen("find /dev/ -name \"ttyUSB*\"", "r");
  if (fp == NULL) 
  {
      printf("Failed to run command\n");
      return 1;
  }

  while (fgets(usb_content_buffer, sizeof(usb_content_buffer), fp) != NULL) 
  {
    std::string str=(std::string)usb_content_buffer;
    str.erase(std::remove_if(str.begin(), str.end(), [](char c) { return c == '\n'; }), str.end());
    listPara.push_back(str.erase(0,5));
    usb_counter++;
  }
  pclose(fp);
  
  if(usb_counter<=0)
  {
    printf("Not found USB device\n");
    return 2;
  }

  return 0;
}


int GetInfo::getBOXInfo(const char *pUSBDevice,std::string &boxStr)
{
  // udevadm info -a -p /sys/class/tty/ttyUSB0
  FILE *fp;
  char box_content_buffer[1024]={0};
  char temp_cmd_buffer[1024]={0};
  int box_counter=0;
  int info_line_index=0;
  std::string str;
  sprintf(temp_cmd_buffer,"udevadm info -a -p /sys/class/tty/%s",pUSBDevice);

  fp = popen(temp_cmd_buffer, "r");
  if (fp == NULL) 
  {
      printf("Failed to run command\n");
      return 1;
  }

  while (fgets(box_content_buffer, sizeof(box_content_buffer), fp) != NULL) 
  {
    str=(std::string)box_content_buffer;
    size_t pos = str.find("ATTRS{product}==");
    if(pos != std::string::npos)
    {
      str=str.erase(0,strlen("ATTRS{product}==")+pos);
      str.erase(std::remove_if(str.begin(), str.end(), [](char c) { return c == '\n'; }), str.end());
      if(str.length()==16)
      {
        str=str.substr(1, 14);
        box_counter++;
        break;
      }
    }
    info_line_index++;
  }

  pclose(fp);

  if(box_counter<=0)
  {
    printf("Not found BOX device\n");
    return 2;
  }
  boxStr=str;

  return 0;
}


