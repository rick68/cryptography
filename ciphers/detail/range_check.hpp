//
// detail/range_check.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_DETAIL_RANGE_CHECK_HPP
#define ATHENA_CIPHERS_DETAIL_RANGE_CHECK_HPP

// STL
#include <cstddef>

// Boost.StaticAssert
#include <boost/static_assert.hpp>

// Athena.Ciphers
#include "length.hpp"

namespace athena {
namespace ciphers {
namespace detail {

#define ATHENA_CIPHERS_DETAIL_RANGE_CHECK_ASSERT(seq, i) \
    BOOST_STATIC_ASSERT(i >= 0 && i < length<seq>::value); \
    /**/

template <typename Sequence, std::size_t I>
struct range_check
{
  ATHENA_CIPHERS_DETAIL_RANGE_CHECK_ASSERT(Sequence, I)
};

} // detail
} // ciphers
} // athena

#endif // ATHENA_CIPHERS_DETAIL_RANGE_CHECK_HPP
