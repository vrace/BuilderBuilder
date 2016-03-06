#ifndef __BB_UTIL_H__
#define __BB_UTIL_H__

const char* TrimLeft(const char *str);
void StrcpyUntilAny(char *dest, const char *str, const char *control);
int FileExists(const char *file);

#endif
