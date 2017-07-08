#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>

#include "loger.h"

int debug_level_set = DEBUG;

#define     COLOR_RED              31
#define     COLOR_BLACK            30
#define     COLOR_GREEN            32
#define     COLOR_BLUE             34
#define     COLOR_YELLOW           33
#define     COLOR_WHITE            37
#define     COLOR_CYAN             36
#define     COLOR_MAGENTA          35

static char	log_level_str[][LEVEL_MAX] = { "DEBUG" , "INFO" , "WARN" , "ERROR" , "FATAL" , "NOLOG" } ;

int debug_buffer_printf(debug_message_t *message)
{
	if(message->level >= debug_level_set){
		switch (message->level){
			case DEBUG:
				printf("\e[%d;1m", COLOR_BLUE);
				break;
			case INFO:
				printf("\e[%d;1m", COLOR_GREEN);
				break;
			case WARN:
				printf("\e[%d;1m", COLOR_MAGENTA);
				break;
			case ERROR:
				printf("\e[%d;1m", COLOR_YELLOW);
				break;
			case FATAL:
				printf("\e[%d;1m", COLOR_RED);
				break;
			default:
				break;
				
		}
		fflush(stdout);
		printf("%s", message->buffer);
		printf("\e[0m");
		fflush(stdout);
	}
	return 0;
}

int debug_print(int level, char *name, long line, const char *function, char *format , ...)
{
	va_list	valist;
	char buffer[512] = "";
	char time_buffer[128] = "";
	int ret;
	debug_message_t message;
	
	va_start(valist, format);
	ret = vsnprintf(buffer, sizeof(buffer), format, valist);
	va_end(valist);
	debug_get_time(time_buffer, sizeof(time_buffer));
	message.level = level%LEVEL_MAX;
	message.length = snprintf(message.buffer, sizeof(message.buffer), "%s|%s|%s +%ld|%s|%s"
		,log_level_str[message.level]
		,time_buffer
		,name
		,line
		,function
		,buffer);
	debug_buffer_printf(&message);
	return ret;
}

void debug_get_time(char *buffer, int len)
{
	struct timeval tv;
	struct tm result;

	gettimeofday(&tv, NULL);
	gmtime_r(&tv.tv_sec, &result);
	snprintf(buffer, len, "%d-%d-%d_%d:%d:%d",
	result.tm_year + 1900, result.tm_mon + 1, result.tm_mday, result.tm_hour, result.tm_min, result.tm_sec);
}
