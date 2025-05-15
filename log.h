
#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "unistd.h"
#include "errno.h"
#include "stdarg.h"




int log_write(const char *format,...);






#endif 


