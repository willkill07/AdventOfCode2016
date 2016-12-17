#ifndef _WILLIAM_KILLIAN_MD5_HPP_
#define _WILLIAM_KILLIAN_MD5_HPP_

#include <cstddef>
#include <cinttypes>
#include <iterator>
#include <x86intrin.h>

template <typename T, size_t N> using vector = T __attribute__((ext_vector_size(N)));

using uint128_t = unsigned __int128;

constexpr uint8_t val(const char c) {
  return (c >= 'A') ? c - 'A' + 10 : (c - '0');
}

constexpr uint128_t operator"" _uint128_t(const char *str, size_t width) {
  uint128_t result{0};
  for (size_t i{0}; i < width; ++i)
    result = (result << 4) | val(str[i]);
  return result;
}

constexpr uint128_t operator"" _mask(const char *str, size_t width) {
  size_t reps{32 / width};
  uint128_t mask{0}, result{0};
  for (size_t i{0}; i < width; ++i)
    mask = (mask << 4) | val(str[i]);
  for (size_t i{0}; i < reps; ++i)
    result = (result << (width << 2)) | mask;
  return result;
}

typedef uint16_t v16hi __attribute__ ((vector_size (32)));
typedef uint8_t  v32qi __attribute__ ((vector_size (32)));

union md5sum_t {
  vector<uint8_t,16> v8x16;
  vector<uint16_t,8> v16x8;
  vector<uint32_t,4> v32x4;
  vector<uint64_t,8> v64x2;
  uint8_t  a8[16];
  uint16_t a16[8];
  uint32_t a32[4];
  uint64_t a64[2];
  uint128_t imm;
  __m128i m128i;
};

union md5str_t {
  vector<uint8_t,32>  v8x32;
  vector<uint16_t,16> v16x16;
  vector<uint32_t,8>  v32x8;
  vector<uint64_t,4>  v64x4;
  v16hi h;
  v32qi q;
  char c[32];
  __m256i m256i;

  using value_type = char;
  using size_type = size_t;
  using iterator = value_type*;
  using const_iterator = const value_type*;

  constexpr inline size_type size() const { return 32; };
  constexpr inline iterator begin() { return &c[0]; };
  constexpr inline iterator end() { return &c[size()]; };
  constexpr inline const_iterator cbegin() const { return &c[0]; }
  constexpr inline const_iterator cend() const { return &c[size()]; }
};

md5sum_t md5 (uint8_t* initial_msg, size_t initial_len);

void md5str (uint8_t* initial_msg, size_t initial_len, md5str_t* out);

#endif
