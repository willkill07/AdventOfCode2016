#ifndef _WILLIAM_KILLIAN_MD5_HPP_
#define _WILLIAM_KILLIAN_MD5_HPP_

#include <cinttypes>
#include <array>

using md5sum_t = std::array <uint32_t, 4>;

md5sum_t md5 (uint8_t* initial_msg, size_t initial_len);

#endif
