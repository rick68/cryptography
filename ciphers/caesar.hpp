//
// caesar.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_CAESAR_HPP
#define ATHENA_CIPHERS_CAESAR_HPP

// STL
#include <cstddef>

// Boost.Config
#include <boost/config/suffix.hpp>

// Boost.Preprocesssor
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>

// Athena.Ciphers
#include "detail/config.hpp"
#include "detail/left_rotate.hpp"
#include "detail/first.hpp"
#include "detail/last.hpp"
#include "detail/length.hpp"

namespace athena {
namespace ciphers {

template <typename Alphabet, std::size_t N>
struct caesar
{
  BOOST_STATIC_CONSTANT(std::size_t, n = N);
  BOOST_STATIC_CONSTANT(std::size_t, first = detail::first<Alphabet>::value);
  BOOST_STATIC_CONSTANT(std::size_t, last = detail::last<Alphabet>::value);
  BOOST_STATIC_CONSTANT(std::size_t, length = detail::length<Alphabet>::value);

  typedef Alphabet alphabet_type;
  typedef typename detail::rot<alphabet_type, N>::type sequence_type;

  static const char_type data[length + 1];

  inline static char_type encode(char_type c)
  {
    if (c >= first && c <= last)
      return data[c - first];
    return c;
  }

  inline static char_type decode(char_type c)
  {
    if (c >= first && c <= last)
    {
      char_type idx = c - first - (2 * n);
      while (idx < 0) idx += alphabet_number;
      return data[idx];
    }
    return c;
  }
};

template <typename Alphabet, std::size_t N>
const char_type
caesar<Alphabet, N>::data[length + 1] =
{
  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_NUMBER
    , ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_PP_REPEAT_MACRO
    , sequence_type
    )
  '\0'
};

#define ATHENA_CIPHERS_CAESAR_ROT_TYPEDEF_PP_REPERAT_MACRO(z, n, text) \
  template <typename Alphabet> struct BOOST_PP_CAT(rot, n) \
      : caesar<Alphabet, n> {}; \
  /**/

BOOST_PP_REPEAT(
    ATHENA_CIPHERS_ALPHABET_NUMBER
  , ATHENA_CIPHERS_CAESAR_ROT_TYPEDEF_PP_REPERAT_MACRO
  , ~)

#undef ATHENA_CIPHERS_CAESAR_ROT_TYPEDEF_PP_REPERAT_MACRO

} // ciphers
} // athena

#endif // ATHENA_CIPHERS_CAESAR_HPP
