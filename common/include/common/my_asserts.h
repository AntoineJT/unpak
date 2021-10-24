#pragma once

// RT_ASSERT is used for displaying failed condition
// at runtime on stderr where it fails, then exit.
//
// RT_ENSURE is used to check if the condition passes
// else to quit after writing a message to stderr.

#ifdef __cplusplus
#define RT_ASSERT(cond, msg) cpp_rt_assert((cond), #cond, (msg), __LINE__, __FILE__)
void cpp_rt_assert(const bool b_cond, const char* cond, const char* msg, const int line, const char* file);
#define RT_ENSURE(cond, msg) cpp_rt_ensure((cond), msg)
void cpp_rt_ensure(const bool b_cond, const char* msg);
#else
#define RT_ASSERT(cond, msg) c_rt_assert((cond), #cond, (msg), __LINE__, __FILE__)
void c_rt_assert(const int b_cond, const char* cond, const char* msg, const int line, const char* file);
#define RT_ENSURE(cond, msg) c_rt_ensure((cond), msg)
void c_rt_ensure(const int b_cond, const char* msg);
#endif
