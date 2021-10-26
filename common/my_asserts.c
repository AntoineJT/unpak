#include "include/common/my_asserts.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void c_rt_assert(const int b_cond, const char* cond, const char* msg, const int line, const char* file)
{
	if (!b_cond) {
		fprintf(stderr, "assertion failed (%s@%d): "
			"\n\t%s"
			"\n>\t%s", file, line, msg, cond);
		exit(EXIT_FAILURE);
	}
}

void c_rt_ensure(const int b_cond, const char* prefix, const char* fmt, ...)
{
	if (!b_cond) {
		fprintf(stderr, "%s", prefix);
		va_list args;
		va_start(args, fmt);
		vfprintf(stderr, fmt, args);
		va_end(args);
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
}
