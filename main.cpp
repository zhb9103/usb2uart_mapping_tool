
/*
 *
 * Created in 2025.05
 * Free source on GPL2.0
 *
 */

#include "main.h"

/*
 *
ATTRS{idVendor}=="0403",ATTRS{idProduct}=="6011",ATTRS{product}=="DCB00003",ATTRS{serial}=="0A_UV00",ENV{UV_USB00_EN}="1"
ATTRS{idVendor}=="0403",ATTRS{idProduct}=="6011",ATTRS{product}=="DCB00003",ATTRS{serial}=="0A_UV01",ENV{UV_USB01_EN}="1"
...

ATTRS{bInterfaceNumber}=="01",ENV{UV_USB00_EN}=="1",MODE="0777",SYMLINK+="uvUART00"
ATTRS{bInterfaceNumber}=="02",ENV{UV_USB00_EN}=="1",MODE="0777",SYMLINK+="uvUART01"
...
 *
*/


char *pTargetFile=(char*)"/etc/udev/rules.d/99-usb2uart_mapping.rules";
char *pVersion=(char*)"0.0.1";


char *idVendor_str=(char*)"0403";
char *idProduct_str=(char*)"6010";
int DEBUGE_ENABLE=0;

std::list<std::string> usb_list;
std::list<std::string> box_list;
std::list<std::string> rule_list;
/*
 * genDCB
 */
void genDCB(const char *idVendor,const char *idProduct,const char *product,const int usbNumber,const int dcbNumber,const int uartNumber);


using namespace std;

int main(int argc, char **argv)
{
  int usbSN=0;
  int dcbSN=0;
  int uartSN=0;
  int diplay_counter=0;

  int cmd_result=0;
  FILE *fp;
  struct timeval tv;
  long long t_start,t_stop;

  gettimeofday(&tv,NULL);
  t_start = tv.tv_sec * 1000000LL + tv.tv_usec;

  ap::parser p(argc, argv);
  p.add("-v", "--version",  "Version",ap::mode::BOOLEAN);
  p.add("-b", "--verbose",  "Verbose",ap::mode::BOOLEAN);
  auto args = p.parse();
  if (!args.parsed_successfully()) 
  {
    std::cerr << "Unsuccessful parse\n";	
    return -1;
  }
  if (std::stoi(args["-v"]))
  {
    printf("Ver:%s\n",pVersion);
    log_write("Ver:%s\n",pVersion);
    return 0;
  }
  printf("Ver:%s\n",pVersion);

  if (std::stoi(args["-b"]))
  {
    DEBUGE_ENABLE=1;
  }
  else
  {
    DEBUGE_ENABLE=0;
  }
  printf("\nScan USB.\n");
  if(GetInfo::getUSBInfo(usb_list)!=0)
  {
    printf("Get USB fail.\n");
    log_write("Get USB fail.\n");
    return -1;
  }
  if(usb_list.size()==0)
  {
    printf("Not found USB device.\n");
    log_write("Not found USB device.\n");
    return -1;
  }
  usb_list.sort();
  printf("Got USB list(%d):\n",usb_list.size());
  log_write("USB list(%d):\n",usb_list.size());
  diplay_counter=0;
  for (std::list<std::string>::iterator it = usb_list.begin(); it != usb_list.end(); ++it) 
  {
    printf("%d. %s\n",diplay_counter,(*it).c_str());
    diplay_counter++;
  }
  printf("\nGet BOX information.\n");
  for (std::list<std::string>::iterator it = usb_list.begin(); it != usb_list.end(); ++it)
  {
    std::string tempStr;
    if(GetInfo::getBOXInfo((*it).c_str(),tempStr)==0)
    {
      // get the normal device;
      auto it = std::find(box_list.begin(), box_list.end(), tempStr);
 
      if (it != box_list.end()) 
      {
        // data is exist;
      } 
      else 
      {
          box_list.push_back(tempStr);
      }

    }
    else
    {
      // get the exception device;
    }
  }

  if(box_list.size()==0)
  {
    printf("Not found BOX device.\n");
    log_write("Not found BOX device.\n");
    return -1;
  }
  box_list.sort();
  printf("Got BOX list(%d):\n",box_list.size());
  log_write("BOX list(%d):\n",box_list.size());
  diplay_counter=0;
  for (std::list<std::string>::iterator it = box_list.begin(); it != box_list.end(); ++it) 
  {
     printf("%d. %s\n",diplay_counter,(*it).c_str());
     diplay_counter++;
  }
  printf("\nStart to generate data.\n");
  for (std::list<std::string>::iterator it = box_list.begin(); it != box_list.end(); ++it)
  {
    genDCB(idVendor_str,idProduct_str,(*it).c_str(),usbSN,dcbSN,uartSN);
    usbSN=usbSN+8;
    uartSN=0;
    dcbSN++;
  }

  printf("Data generated.\n");

  printf("\nStart to save data.\n");
  fp = fopen((char*)pTargetFile, "w");
  for (std::list<std::string>::iterator it = rule_list.begin(); it != rule_list.end(); ++it)
  {
    fprintf(fp,"%s\n",(*it).c_str());
    log_write("%s\n",(*it).c_str());
  }


  fclose(fp);
  printf("Data saved.\n");

  usleep(100);
  printf("\nActive rules.\n");
  cmd_result=system("udevadm control --reload");
  if (cmd_result == -1) 
  {
    perror("udevadm control fail.");
    log_write("udevadm control fail.");
    return 1;
  }
  cmd_result=system("udevadm trigger");
  if (cmd_result == -1) 
  {
    perror("udevadm trigger fail.");
    log_write("udevadm trigger fail.");
    return 1;
  }
  printf("Rules actived.\n");
  gettimeofday(&tv,NULL);
  t_stop = tv.tv_sec * 1000000LL + tv.tv_usec;
  printf("\nRun success, elapsed time:%lldms.\n",(t_stop-t_start)/1000);
  return 0;

}



void genDCB(const char *idVendor,const char *idProduct,const char *product,const int usbNumber,const int dcbNumber,const int uartNumber)
{
  int tempUsbNumber=usbNumber;
  int tempUartNumber=uartNumber;
  int tempDcbNumber=dcbNumber;
  for(int usb_i=0;usb_i<1;usb_i++)
  {
    char tempUsbNumber_str[32]={0};
    sprintf(tempUsbNumber_str,"%02d",tempUsbNumber);
    char tempIdUSB[256]={0};
    DataGenerator::genIdUSB(idVendor,idProduct,product,tempUsbNumber_str,tempUsbNumber,tempIdUSB,DEBUGE_ENABLE);
    rule_list.push_back((std::string)tempIdUSB);
    for(int uart_i=0;uart_i<4;uart_i++)
    {
      char tempIdUART[256]={0};
      DataGenerator::genIdUART(uart_i,tempUsbNumber,tempDcbNumber,tempUartNumber,tempIdUART,DEBUGE_ENABLE);
      rule_list.push_back((std::string)tempIdUART);
      tempUartNumber++;
    }
    tempUsbNumber++;
  }
}


