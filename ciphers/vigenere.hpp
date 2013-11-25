//
// vigenere.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_VIGENERE_HPP
#define ATHENA_CIPHERS_VIGENERE_HPP

// STL
#include <cstddef>
#include <string>
#include <memory>

// Boost.Config
#include <boost/config/suffix.hpp>

// Boost.Preprocessor
#include <boost/preprocessor/punctuation/comma.hpp>

// Boost.Utility
#include <boost/assert.hpp>

// Athena.Ciphers
#include "detail/config.hpp"
#include "detail/left_rotate.hpp"
#include "detail/random_access.hpp"
#include "detail/first.hpp"
#include "detail/last.hpp"
#include "detail/length.hpp"

namespace athena {
namespace ciphers {

template <typename Alphabet, std::size_t X, std::size_t Y>
struct vigenere_table
{
  BOOST_STATIC_CONSTANT(std::size_t, value =
      detail::random_access<
          typename detail::rot<
              Alphabet BOOST_PP_COMMA()
              X
          >::type BOOST_PP_COMMA()
          Y
      >::value
  );
};

template <
    typename Alphabet
  , typename String = std::basic_string<
        char_type
      , std::char_traits<char_type>
      , std::allocator<char_type>
      >
  >
struct vigenere
{
  BOOST_STATIC_CONSTANT(std::size_t, first = detail::first<Alphabet>::value);
  BOOST_STATIC_CONSTANT(std::size_t, last = detail::last<Alphabet>::value);
  BOOST_STATIC_CONSTANT(std::size_t, length =
      detail::length<Alphabet>::value * detail::length<Alphabet>::value);

  typedef Alphabet alphabet_type;
  typedef String string_type;

  static const typename string_type::value_type data[length + 1];

  vigenere(const string_type& keyword)
    : keyword_(keyword) {}

  const string_type& keyword() const { return keyword_; }
  string_type& keyword() { return keyword_; }

  inline static typename string_type::value_type
  encode(typename string_type::value_type c,
         typename string_type::value_type key)
  {
    BOOST_ASSERT(key >= first && key <= last);

    if (c >= first && c <= last)
      c = data[(c - first) + (key - first) * detail::length<Alphabet>::value];

    return c;
  }

  inline string_type& encode(string_type& text) const
  {
    const typename string_type::size_type& tsize = text.size();
    const typename string_type::size_type& ksize = keyword_.size();

    if (tsize == 0)
      return text;

    for (std::size_t i = 0, n = 0; i < tsize; ++i)
    {
      typename string_type::reference c = text[i];

      if (c >= first && c <= last)
      {
        typename string_type::const_reference& k = keyword_[n];

        if (++n >= ksize)
          n = 0;

        c = data[(c - first) + (k - first) * detail::length<Alphabet>::value];
      }
    }

    return text;
  }

  inline static typename string_type::value_type
  decode(typename string_type::value_type c,
         typename string_type::value_type key)
  {
    BOOST_ASSERT(key >= first && key <= last);

    if (c >= first && c <= last)
    {
      typename string_type::const_pointer ptr =
          &data[(key - first) * detail::length<Alphabet>::value];
      std::size_t i = 0;

      for (; i < detail::length<Alphabet>::value; ++i)
        if (*ptr++ == c)
          break;

      c = first + i;
    }

    return c;
  }

  inline string_type& decode(string_type& text) const
  {
    const typename string_type::size_type& tsize = text.size();
    const typename string_type::size_type& ksize = keyword_.size();

    if (tsize == 0) return text;

    for (std::size_t i = 0, n = 0; i < tsize; ++i)
    {
      typename string_type::reference c = text[i];

      if (c >= first && c <= last)
      {
        typename string_type::const_reference& k = keyword_[n];
        typename string_type::const_pointer ptr =
            &data[(k - first) * detail::length<Alphabet>::value];
        std::size_t j = 0;

        if (++n >= ksize)
          n = 0;

        for (j = 0; j < detail::length<Alphabet>::value; ++j)
          if (*ptr++ == c)
            break;

        c = first + j;
      }
    }
    return text;
  }

private:
  string_type keyword_;
};

#define ATHENA_CIPHERS_VIGENERE_GET_SEQUENCE_PP_PEPEAT_MACRO(z, x, alphabet) \
  BOOST_PP_REPEAT( \
      ATHENA_CIPHERS_ALPHABET_NUMBER \
    , ATHENA_CIPHERS_VIGENERE_GET_VALUE_PP_PEPEAT_MACRO \
    , (alphabet, x) \
    ) \
  /**/

#define ATHENA_CIPHERS_VIGENERE_GET_VALUE_PP_PEPEAT_MACRO(z, y, tuple2) \
  vigenere_table< \
      BOOST_PP_TUPLE_ELEM(2, 0, tuple2) BOOST_PP_COMMA() \
      BOOST_PP_TUPLE_ELEM(2, 1, tuple2) BOOST_PP_COMMA() \
      y \
    >::value BOOST_PP_COMMA() \
  /**/

template <typename Alphabet, typename String>
const typename vigenere<Alphabet, String>::string_type::value_type
vigenere<Alphabet, String>::data[length + 1] =
{
  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_NUMBER
    , ATHENA_CIPHERS_VIGENERE_GET_SEQUENCE_PP_PEPEAT_MACRO
    , Alphabet
    )
  '\0'
};

#undef ATHENA_CIPHERS_VIGENERE_GET_SEQUENCE_PP_PEPEAT_MACRO
#undef ATHENA_CIPHERS_VIGENERE_GET_VALUE_PP_PEPEAT_MACRO

} // namespace ciphers
} // namespace athena

#endif // ATHENA_CIPHERS_VIGENERE_HPP
