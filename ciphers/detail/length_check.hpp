//
// detail/length_check.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_DETAIL_LENGTH_CHECK_HPP
#define ATHENA_CIPHERS_DETAIL_LENGTH_CHECK_HPP

// STL
#include <cstddef>

// Boost.StaticAssert
#include <boost/static_assert.hpp>

// Athena.Ciphers
#include "length.hpp"

namespace athena {
namespace ciphers {
namespace detail {

#define ATHENA_CIPHERS_DETAIL_LENGTH_CHECK_ASSERT(seq, n) \
  BOOST_STATIC_ASSERT(length<seq>::value == n); \
  /**/

template <typename Sequence, std::size_t N>
struct length_check
{
  ATHENA_CIPHERS_DETAIL_LENGTH_CHECK_ASSERT(Sequence, N)
};

} // detail
} // ciphers
} // athena

#endif // ATHENA_CIPHERS_DETAIL_LENGTH_CHECK_HPP
