#include "include/common/my_asserts.h"

#include <stdio.h>
#include <stdlib.h>

void c_rt_assert(const int b_cond, const char* cond, const char* msg, const int line, const char* file)
{
	if (!b_cond) {
		fprintf(stderr, "assertion failed (%s@%d): "
			"\n\t%s"
			"\n>\t%s", file, line, msg, cond);
		exit(EXIT_FAILURE);
	}
}

void c_rt_ensure(const int b_cond, const char* prefix, const char* msg)
{
	if (!b_cond) {
		fprintf(stderr, "%s%s\n", prefix, msg);
		exit(EXIT_FAILURE);
	}
}
