//
// adfgvx.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_ADFGXV_HPP
#define ATHENA_CIPHERS_ADFGXV_HPP

// STL
#include <cstddef>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>

// Boost.StaticAssert
#include <boost/static_assert.hpp>

// Boost.Config
#include <boost/config/suffix.hpp>

// Boost.MPL
#include <boost/mpl/if.hpp>

// Boost.TypeTraits
#include <boost/type_traits/is_same.hpp>

// Boost.Utility
#include <boost/assert.hpp>

// Athena.Ciphers
#include "detail/config.hpp"
#include "detail/length.hpp"
#include "detail/first.hpp"
#include "detail/last.hpp"

namespace athena {
namespace ciphers {

template <
    typename Alphabet
  , typename AdfgvxAlphabetUppercase = adfgvx_alphabet_uppercase
  , typename AdfgvxTableUppercase = adfgvx_table_uppercase
  , typename AdfgvxAlphabetLowercase = adfgvx_alphabet_lowercase
  , typename AdfgvxTableLowercase = adfgvx_table_lowercase
  >
struct adfgvx
{
  BOOST_STATIC_ASSERT(
      detail::length<adfgvx_alphabet_uppercase>::value
   == detail::length<adfgvx_alphabet_lowercase>::value
    );

  BOOST_STATIC_ASSERT(
      detail::length<adfgvx_table_uppercase>::value
   == detail::length<adfgvx_table_lowercase>::value
    );

  BOOST_STATIC_CONSTANT(std::size_t, first = detail::first<Alphabet>::value);
  BOOST_STATIC_CONSTANT(std::size_t, last = detail::last<Alphabet>::value);
  BOOST_STATIC_CONSTANT(
      std::size_t
    , adfgvx_alphabet_length = ATHENA_CIPHERS_ALPHABET_ADFGVX_ALPHABET_SIZE
    );
  BOOST_STATIC_CONSTANT(
      std::size_t
    , length = detail::length<adfgvx_table_uppercase>::value
    );

  typedef Alphabet alphabet_type;

  typedef typename boost::mpl::if_c<
      boost::is_same<alphabet_type, uppercase>::value
    , adfgvx_alphabet_uppercase
    , adfgvx_alphabet_lowercase
    >::type adfgvx_alphabet_type;

  typedef typename boost::mpl::if_c<
      boost::is_same<alphabet_type, uppercase>::value
    , adfgvx_table_uppercase
    , adfgvx_table_lowercase
    >::type adfgvx_table_type;

  BOOST_STATIC_CONSTANT(
      std::size_t
    , adfgvx_alphabet_first = detail::first<adfgvx_alphabet_type>::value
    );
  BOOST_STATIC_CONSTANT(
      std::size_t
    , adfgvx_alphabet_last = detail::first<adfgvx_alphabet_type>::value
    );

  typedef std::basic_string<
      char_type
    , std::char_traits<char_type>
    , std::allocator<char_type>
    > string_type;

  static const typename string_type::value_type
      adfgvx_alphabet[adfgvx_alphabet_length + 1];
  static const typename string_type::value_type data[length + 1];

  adfgvx(const string_type& transposition_key)
    : key_(transposition_key)
    , transposition_(transposition_key.size())
    , compare_()
  {
    set_key(transposition_key);
  }

  inline const string_type& get_key() const { return key_; }

  inline void set_key(const string_type& transposition_key)
  {
    const typename string_type::size_type& limit = transposition_key.size();

    transposition_.clear();
    transposition_.resize(limit);
    key_ = transposition_key;

    for (std::size_t i = 0; i < limit; ++i)
    {
      element_type& elem = transposition_[i];
      elem.first = i;
      elem.second = transposition_key[i];
    }
    std::sort(transposition_.begin(), transposition_.end(), compare_);
  }

  inline bool
  encrypt(const string_type& plaintext, string_type& ciphertext) const
  {
    const typename string_type::size_type& psize = plaintext.size();

    if (!psize)
        return false;

    BOOST_ASSERT(&plaintext != &ciphertext);
    ciphertext.clear();
    ciphertext.reserve(psize * 2);

    const typename string_type::size_type& ksize = key_.size();
    typename string_type::size_type i = 0, j = 0, m = 0, n = 0;

    for (i = 0; i < psize; ++i)
    {
      typename string_type::const_reference c = plaintext[i];

      if ((c >= first && c <= last) || (c >= '0' && c <= '9'))
      {
        for (j = 0; j < length; ++j)
          if (data[j] == c)
            break;
        BOOST_ASSERT(j < length);

        n = j % adfgvx_alphabet_length;
        m = (j - n) / adfgvx_alphabet_length;
        BOOST_ASSERT(m < adfgvx_alphabet_length);

        ciphertext.push_back(adfgvx_alphabet[m]);
        ciphertext.push_back(adfgvx_alphabet[n]);
      }
      else
        ciphertext.push_back(c);
    }

    const typename string_type::size_type& csize = ciphertext.size();

    for (i = 0; i < csize - ksize; i += ksize)
    {
      const string_type& subciphertext = ciphertext.substr(i, ksize);

      for (j = 0; j < ksize; ++j)
      {
        n = transposition_[j].first;
        ciphertext[i + j] = subciphertext[n];
      }
    }

    return true;
  }

  inline bool encrypt(string_type& text) const
    { return encrypt(string_type(text), text); }

  inline bool
  decipher(const string_type& ciphertext, string_type& plaintext) const
  {
    const typename string_type::size_type& csize = ciphertext.size();

    if (!csize)
        return false;

    BOOST_ASSERT(&ciphertext != &plaintext);
    plaintext.clear();

    string_type text(ciphertext);
    const typename string_type::size_type& ksize = key_.size();
    typename string_type::size_type i = 0, j = 0;

    for (i = 0; i < csize - ksize; i += ksize)
    {
      for (j = 0; j < ksize; ++j)
      {
        const typename string_type::size_type& n = transposition_[j].first;
        BOOST_ASSERT(n < adfgvx_alphabet_length);
        text[i + n] = ciphertext[i + j];
      }
    }

    const typename string_type::size_type& tsize = text.size();
    typename string_type::size_type indices[2];
    const typename string_type::const_pointer begin_ptr = &adfgvx_alphabet[0];
    const typename string_type::const_pointer end_ptr = 
        &adfgvx_alphabet[adfgvx_alphabet_length];
    typename string_type::const_pointer ptr = 0;

    for (i = 0; i < tsize; ++i)
    {
      for (j = 0; j < 2; ++j)
      {
        typename string_type::size_type& index = indices[j];

        if (i + 2 > tsize)
          break;

        ptr = std::find(begin_ptr, end_ptr, text[i + j]);
        if (ptr == end_ptr)
          break;

        index = ptr - begin_ptr;
      }
      if (j == 0)
      {
        plaintext.push_back(text[i]);
        continue;
      }
      if (j != 2)
        return false;

      ++i;

      plaintext.push_back(
          data[indices[0] * adfgvx_alphabet_length + indices[1]]);
    }

    return true;
  }

  inline bool decipher(string_type& text) const
    { return decipher(string_type(text), text); }

private:
  typedef std::pair<
      std::size_t
    , typename string_type::value_type
    > element_type;

  std::vector<element_type> transposition_;

  struct compare : std::binary_function<element_type, element_type, bool>
  {
    bool operator()(const element_type& x, const element_type& y) const
        { return x.second < y.second; }
  } compare_;

  string_type key_;
};

template <
    typename Alphabet
  , typename AdfgvxAlphabetUppercase
  , typename AdfgvxTableUppercase
  , typename AdfgvxAlphabetLowercase
  , typename AdfgvxTableLowercase
  >
const typename adfgvx<
    Alphabet
  , AdfgvxAlphabetUppercase
  , AdfgvxTableUppercase
  , AdfgvxAlphabetLowercase
  , AdfgvxTableLowercase
  >::string_type::value_type
adfgvx<
    Alphabet
  , AdfgvxAlphabetUppercase
  , AdfgvxTableUppercase
  , AdfgvxAlphabetLowercase
  , AdfgvxTableLowercase
>::adfgvx_alphabet[adfgvx_alphabet_length + 1] =
{
  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_ADFGVX_ALPHABET_SIZE
    , ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_PP_REPEAT_MACRO
    , adfgvx_alphabet_type
    )
  '\0'
};

template <
    typename Alphabet
  , typename AdfgvxAlphabetUppercase
  , typename AdfgvxTableUppercase
  , typename AdfgvxAlphabetLowercase
  , typename AdfgvxTableLowercase
  >
const typename adfgvx<
    Alphabet
  , AdfgvxAlphabetUppercase
  , AdfgvxTableUppercase
  , AdfgvxAlphabetLowercase
  , AdfgvxTableLowercase
  >::string_type::value_type
adfgvx<
    Alphabet
  , AdfgvxAlphabetUppercase
  , AdfgvxTableUppercase
  , AdfgvxAlphabetLowercase
  , AdfgvxTableLowercase
>::data[length + 1] =
{
  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_ADFGVX_TABLE_SIZE
    , ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_PP_REPEAT_MACRO
    , adfgvx_table_type
    )
  '\0'
};

} // namespace ciphers
} // namespace athena

#endif // ATHENA_CIPHERS_ADFGXV_HPP
