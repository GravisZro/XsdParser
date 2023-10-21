#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <string>
#include <string_view>

template<typename T>
std::string operator +(const std::string_view& a, T b)
  { return std::string().append(a).append(b); }
/*
template<typename T>
std::string operator +(const char* const a, T b)
  { return std::string().append(a).append(b); }
*/
template<typename T, int N>
std::string operator +(const char a[N], T b)
  { return std::string().append(a).append(b); }

template<typename T>
std::string operator +(const std::string& a, T b)
  { return std::string().append(a).append(b); }

inline std::string operator *(const std::string_view& a) { return std::string(a); }

#endif // STRINGOPERATIONS_H
