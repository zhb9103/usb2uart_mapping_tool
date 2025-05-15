


#include "log.h"


int log_write(const char *format,...)
{
	FILE* pFile;
	va_list arg;
	int done;
	char filefullname[1024];
	
	va_start(arg,format);

	time_t time_log=time(NULL);
	struct tm* tm_log=localtime(&time_log);
	memset(filefullname,0,100);
	sprintf(filefullname,"./log_%04d%02d%02d.log",tm_log->tm_year+1900,tm_log->tm_mon+1,tm_log->tm_mday);
	pFile=fopen(filefullname,"a");
	fprintf(pFile,"%02d:%02d:%02d ",tm_log->tm_hour,tm_log->tm_min,tm_log->tm_sec);

	done=vfprintf(pFile,format,arg);
	va_end(arg);

	fflush(pFile);
	fclose(pFile);
	return done;
}





