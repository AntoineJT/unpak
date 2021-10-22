#pragma once

#ifdef __cplusplus
#define RT_ASSERT(cond, msg) cpp_rt_assert((cond), #cond, (msg), __LINE__, __FILE__)
void cpp_rt_assert(const bool b_cond, const char* cond, const char* msg, const int line, const char* file);
#else
#define RT_ASSERT(cond, msg) c_rt_assert((cond), #cond, (msg), __LINE__, __FILE__)
void c_rt_assert(const int b_cond, const char* cond, const char* msg, const int line, const char* file);
#endif
