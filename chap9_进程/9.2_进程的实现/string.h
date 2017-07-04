#ifndef __STRING_H__
#define __STRING_H__

static inline int strcmp(const char * cs,const char * ct){
	register signed char __res;
	while (1) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
	}
	return __res;
}

static inline void * memset(void * s,int c,unsigned int count){
	char *xs = (char *) s;
	while (count--)
		*xs++ = c;
	return s;
}

static inline char * strcpy(char * dest,const char *src){
	char *tmp = dest;
	while ((*dest++ = *src++) != '\0');
	return tmp;
}

static inline char * strncpy(char * dest,const char *src,unsigned int count){
	char *tmp = dest;
	while (count-- && (*dest++ = *src++) != '\0');
	return tmp;
}

static inline unsigned int strlen(const char * s){
	const char *sc;
	for (sc = s; *sc != '\0'; ++sc);
	return sc - s;
}

static inline char * strchr(const char * s, int c){
	for(; *s != (char) c; ++s)
		if (*s == '\0')
			return (void *)0;
	return (char *) s;
}

#endif
