//
// detail/right_rotate.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_DETAIL_LEFT_ROTATE_HPP
#define ATHENA_CIPHERS_DETAIL_LEFT_ROTATE_HPP

// STL
#include <cstddef>

// Boost.Config
#include <boost/config/suffix.hpp>

// Boost.StaticAssert
#include <boost/static_assert.hpp>

// Boost.Preprocessor
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Athena.Ciphers
#include "length_check.hpp"
#include "random_access.hpp"
#include "range_check.hpp"

namespace athena {
namespace ciphers {
namespace detail {

template <typename Sequence>
struct left_rotate
    : length_check<Sequence, alphabet_number>
{
  typedef ATHENA_CIPHERS_ALPHABET_SEQUENCE_TYPE<
      char_type
    , BOOST_PP_REPEAT_FROM_TO(
          1
        , ATHENA_CIPHERS_ALPHABET_NUMBER
        , ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_PP_REPEAT_MACRO
        , Sequence
        )
      ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS(Sequence, 0)
    > type;
};

// ROTn "rotate by n places"
template <typename Alphabet, std::size_t N>
struct rot : range_check<Alphabet, N>
{
  BOOST_STATIC_CONSTANT(std::size_t, value = N);
  typedef Alphabet alphabet_type;
  typedef typename rot<
      typename detail::left_rotate<alphabet_type>::type
    , N - 1
    >::type type;
};

template <typename Alphabet>
struct rot<Alphabet, 0> : range_check<Alphabet, 0>
{
  BOOST_STATIC_CONSTANT(std::size_t, value = 0);
  typedef Alphabet alphabet_type;
  typedef alphabet_type type;
};

} // detail
} // ciphers
} // athena

#endif // ATHENA_CIPHERS_DETAIL_LEFT_ROTATE_HPP
