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

  vigenere(const string_type& key)
    : key_(key) {}

  inline const string_type& get_key() const { return key_; }
  inline void set_key(const string_type& key) { return key_ = key; }

  inline bool encrypt(const string_type& plaintext, string_type& ciphertext) const
  {
    const typename string_type::size_type& psize = plaintext.size();

    if (!psize)
      return false;

    const typename string_type::size_type& ksize = key_.size();

    BOOST_ASSERT(&plaintext != &ciphertext);
    ciphertext.resize(0);

    for (std::size_t i = 0, n = 0; i < psize; ++i)
    {
      typename string_type::const_reference c = plaintext[i];

      if (c >= first && c <= last)
      {
        typename string_type::const_reference& k = key_[n];

        if (++n >= ksize)
          n = 0;

        ciphertext.append(
            1
          , data[
                (c - first)
              + (k - first)
              * detail::length<Alphabet>::value
              ]
          );
      }
    }

    return true;
  }

  inline bool encrypt(string_type& text) const
    { return encrypt(string_type(text), text); }

  inline bool decipher(const string_type& ciphertext, string_type& plaintext) const
  {
    const typename string_type::size_type& csize = ciphertext.size();

    if (!csize)
      return false;

    BOOST_ASSERT(&ciphertext != &plaintext);
    plaintext.resize(0);

    const typename string_type::size_type& ksize = key_.size();
    typename string_type::const_pointer ptr = 0;
    std::size_t i = 0, j = 0, n = 0;

    for (i = 0, n = 0; i < csize; ++i)
    {
      typename string_type::const_reference c = ciphertext[i];

      if (c >= first && c <= last)
      {
        typename string_type::const_reference& k = key_[n];
        ptr = &data[(k - first) * detail::length<Alphabet>::value];

        if (++n >= ksize)
          n = 0;

        for (j = 0; j < detail::length<Alphabet>::value; ++j)
          if (*ptr++ == c)
            break;
        BOOST_ASSERT(j < detail::length<Alphabet>::value);

        plaintext.append(1, first + j);
      }
    }

    return true;
  }

  inline bool decipher(string_type& text) const
    { return decipher(string_type(text), text); }
 
private:
  string_type key_;
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
