#pragma once

// RT_ASSERT is used for displaying failed condition
// at runtime on stderr where it fails, then exit.
//
// RT_ENSURE is used to check if the condition passes
// else to quit after writing a message to stderr.
// Info: Please note that a variadic version of
//	the macro exists in C, called RT_ENSURE_VA, in
//	order to allow formatted printing while in C++
//	we can simply concatenate std::string or use
//	const char* by using std::string_view type
//	in the underlying function parameters.
//	Don't forget RT_ENSURE_VA is only available
//	from C code.
//
// For RT_*_[BEGIN|END] macros you must not end
// the call with a semicolon.

// RT_ENSURE_PREFIX can be defined before including
// this file in order to customize the prefix.
#ifndef RT_ENSURE_PREFIX
#define RT_ENSURE_PREFIX "error: "
#endif

#ifdef __cplusplus
// C++
#include <string>

#define RT_ASSERT(cond, msg) cpp_rt_assert((cond), #cond, (msg), __LINE__, __FILE__)
void cpp_rt_assert(const bool b_cond, const char* cond, const std::string_view msg, const int line, const char* file);
#define RT_ENSURE(cond, msg) cpp_rt_ensure((cond), RT_ENSURE_PREFIX, (msg))
void cpp_rt_ensure(const bool b_cond, const std::string_view prefix, const std::string_view msg);

#define RT_ENSURE_BEGIN(cond, msg) \
	if (!(cond)) { \
		std::cerr << RT_ENSURE_PREFIX << (msg) << std::endl;
#define RT_ENSURE_END() \
		exit(EXIT_FAILURE); \
	}
#else
// C
#include <stdio.h>

#define RT_ASSERT(cond, msg) c_rt_assert((cond), #cond, (msg), __LINE__, __FILE__)
void c_rt_assert(const int b_cond, const char* cond, const char* msg, const int line, const char* file);
#define RT_ENSURE(cond, msg) c_rt_ensure((cond), RT_ENSURE_PREFIX, (msg))
void c_rt_ensure(const int b_cond, const char* prefix, const char* msg);
#define RT_ENSURE_VA(cond, fmt, ...) c_rt_ensure_va((cond), RT_ENSURE_PREFIX, fmt, __VA_ARGS__)
void c_rt_ensure_va(const int b_cond, const char* prefix, const char* fmt, ...);

#define RT_ENSURE_BEGIN(cond, msg) \
	if (!(cond)) { \
		fprintf(stderr, "%s%s\n", RT_ENSURE_PREFIX, (msg));
#define RT_ENSURE_END() \
		exit(EXIT_FAILURE); \
	}
#endif
	