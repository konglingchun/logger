#ifndef _LOGER_H_
#define _LOGER_H_

#define DEBUG	0
#define INFO	1
#define WARN	2
#define ERROR	3
#define FATAL	4
#define NOLOG	5
#define LEVEL_MAX	6

typedef struct{
	int length;
	int level;
	char buffer[1024];
}debug_message_t;

int debug_print(int level, char *name, long line, const char *function, char *format , ...);

#define printd(level, fmt, args...)\
	do{ \
		debug_print(level, __FILE__, __LINE__, __FUNCTION__, fmt, ##args);\
	}while(0)

void debug_get_time(char *buffer, int len);

#endif
