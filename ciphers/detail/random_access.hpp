//
// detail/random_access.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_HPP
#define ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_HPP

// STL
#include <cstddef>

// Boost.Config
#include <boost/config/suffix.hpp>

// Boost.MPL
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

// Boost.Preprocessor
#include <boost/preprocessor/punctuation/comma.hpp>

// Athena.Ciphers
#include "range_check.hpp"

namespace athena {
namespace ciphers {
namespace detail {

#define ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS(seq, i) \
  boost::mpl::at_c<seq, i>::type::value \
  /**/

template <typename Sequence, std::size_t I>
struct random_access : range_check<Sequence, I>
{
  BOOST_STATIC_CONSTANT(
      bool,
      value = ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS(Sequence, I));
};

#define ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_PP_REPEAT_MACRO(z, n, text) \
  ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS(text, n) BOOST_PP_COMMA() \
  /**/

} // detail
} // ciphers
} // athena

#endif // ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_HPP
