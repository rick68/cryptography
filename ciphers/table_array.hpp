//
// table_array.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_TABLE_ARRAY_HPP
#define ATHENA_CIPHERS_TABLE_ARRAY_HPP

// STL
#include <cstddef>

// Boost.Config
#include <boost/config/suffix.hpp>

// Boost.Preprocessor
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>

// Athena.Ciphers
#include "detail/config.hpp"
#include "detail/length.hpp"
#include "detail/random_access.hpp"

namespace athena {
namespace ciphers {

namespace detail {

template <typename Alphabet, std::size_t X, std::size_t Y>
struct unused;

} // namespace detail

template <
    typename Alphabet
  , template <typename, std::size_t, std::size_t> class mapper = detail::unused
  >
struct table_array;

template <typename Sequence>
struct table_array<Sequence, detail::unused>
{
  static const char data[detail::length<Sequence>::value + 1];
};

template <typename Sequence>
const char table_array<Sequence>::data[detail::length<Sequence>::value + 1] =
{
  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_NUMBER
    , ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_PP_REPEAT_MACRO
    , Sequence
    )
  '\0'
};

template <
    typename Alphabet
  , template <typename, std::size_t, std::size_t> class mapper
  >
struct table_array
{
  static const char data[
      detail::length<Sequence>::value
    * detail::length<Sequence>::value
    + 1
    ];
};

#define ATHENA_CIPHERS_TABLE_ARRAY_GET_SEQUENCE_PP_PEPEAT_MACRO(z, x, alphabet) \
  BOOST_PP_REPEAT( \
      ATHENA_CIPHERS_ALPHABET_NUMBER \
    , ATHENA_CIPHERS_TABLE_ARRAY_GET_VALUE_PP_PEPEAT_MACRO \
    , (alphabet, x) \
    ) \
  /**/

#define ATHENA_CIPHERS_TABLE_ARRAY_GET_VALUE_PP_PEPEAT_MACRO(z, y, tuple2) \
  mapper< \
      BOOST_PP_TUPLE_ELEM(2, 0, tuple2) BOOST_PP_COMMA() \
      BOOST_PP_TUPLE_ELEM(2, 1, tuple2) BOOST_PP_COMMA() \
      y \
    >::value BOOST_PP_COMMA() \
  /**/

template <
    typename Alphabet
  , template <typename, std::size_t, std::size_t> class mapper
  >
const char table_array<Alphabet, mapper>
    ::data[alphabet_number * alphabet_number + 1] =
{
  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_NUMBER
    , ATHENA_CIPHERS_TABLE_ARRAY_GET_SEQUENCE_PP_PEPEAT_MACRO
    , Alphabet
    )
  '\0'
};

} // ciphers
} // athena

#endif // ATHENA_CIPHERS_TABLE_ARRAY_HPP
