#include "include/common/my_asserts.h"

#include <iostream>
#include <cstdio>
#include <cstdarg>

void cpp_rt_assert(const bool b_cond, const char* cond, const std::string_view msg, const int line, const char* file)
{
	if (!b_cond) {
		std::cerr << "assertion failed (" << file << "@" << line << "): "
				<< "\n\t" << msg
				<< "\n>\t" << cond << std::endl;
		exit(EXIT_FAILURE);
	}
}

void cpp_rt_ensure(const bool b_cond, const std::string_view prefix, const std::string_view fmt, ...)
{
	if (!b_cond) {
		const auto oPrefixStr = std::string(prefix);
		const auto oFmtStr = std::string(fmt);
		const auto pFmt = oFmtStr.c_str();
		fprintf(stderr, "%s", oPrefixStr.c_str());
		va_list args;
		va_start(args, pFmt);
		vfprintf(stderr, pFmt, args);
		va_end(args);
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
}
