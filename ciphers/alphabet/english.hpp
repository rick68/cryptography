//
// alphabet/english.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_ALPHABET_ENGLISH_HPP
#define ATHENA_CIPHERS_ALPHABET_ENGLISH_HPP

// Boost.MPL
#define BOOST_MPL_LIMIT_VECTOR_SIZE 40
#include <boost/mpl/vector_c.hpp>

// Boost.Preprocessor
#include <boost/preprocessor/cat.hpp>

namespace athena {
namespace ciphers {

#define ATHENA_CIPHERS_ALPHABET_CHAR_TYPE char
#define ATHENA_CIPHERS_ALPHABET_NUMBER 26

#define ATHENA_CIPHERS_ALPHABET_SEQUENCE_TYPE \
  BOOST_PP_CAT(boost::mpl::vector, \
  BOOST_PP_CAT(ATHENA_CIPHERS_ALPHABET_NUMBER, _c)) \
  /**/

typedef ATHENA_CIPHERS_ALPHABET_SEQUENCE_TYPE<
    ATHENA_CIPHERS_ALPHABET_CHAR_TYPE
    , 'A', 'B', 'C', 'D', 'E'
    , 'F', 'G', 'H', 'I', 'J'
    , 'K', 'L', 'M', 'N', 'O'
    , 'P', 'Q', 'R', 'S', 'T'
    , 'U', 'V', 'W', 'X', 'Y'
    , 'Z'
    > uppercase;

typedef ATHENA_CIPHERS_ALPHABET_SEQUENCE_TYPE<
    ATHENA_CIPHERS_ALPHABET_CHAR_TYPE
    , 'a', 'b', 'c', 'd', 'e'
    , 'f', 'g', 'h', 'i', 'j'
    , 'k', 'l', 'm', 'n', 'o'
    , 'p', 'q', 'r', 's', 't'
    , 'u', 'v', 'w', 'x', 'y'
    , 'z'
    > lowercase;

#define ATHENA_CIPHERS_ALPHABET_ADFGVX_ALPHABET_SIZE 6

#define ATHENA_CIPHERS_ALPHABET_ADFGVX_ALPHABET_TYPE \
  BOOST_PP_CAT(boost::mpl::vector, \
  BOOST_PP_CAT(ATHENA_CIPHERS_ALPHABET_ADFGVX_ALPHABET_SIZE, _c)) \
  /**/

#define ATHENA_CIPHERS_ALPHABET_ADFGVX_TABLE_SIZE 36

#define ATHENA_CIPHERS_ALPHABET_ADFGVX_TABLE_TYPE \
  BOOST_PP_CAT(boost::mpl::vector, \
  BOOST_PP_CAT(ATHENA_CIPHERS_ALPHABET_ADFGVX_TABLE_SIZE, _c)) \
  /**/

#if !defined(ATHENA_CIPHERS_NO_USE_DEFAULT_ADFGVX_ALPHABET)

typedef ATHENA_CIPHERS_ALPHABET_ADFGVX_ALPHABET_TYPE<
    ATHENA_CIPHERS_ALPHABET_CHAR_TYPE
    , 'A', 'D', 'F', 'G', 'V', 'X'
    > adfgvx_alphabet_uppercase;

typedef ATHENA_CIPHERS_ALPHABET_ADFGVX_ALPHABET_TYPE<
    ATHENA_CIPHERS_ALPHABET_CHAR_TYPE
    , 'a', 'd', 'f', 'g', 'v', 'x'
    > adfgvx_alphabet_lowercase;

typedef ATHENA_CIPHERS_ALPHABET_ADFGVX_TABLE_TYPE<
    ATHENA_CIPHERS_ALPHABET_CHAR_TYPE
    , 'E', 'T', 'A', 'O', 'N', 'R'
    , 'I', 'S', 'H', 'D', 'L', 'F'
    , 'C', 'M', 'U', 'G', 'Y', 'P'
    , 'W', 'B', 'V', 'K', 'J', 'X'
    , 'Q', 'Z', '0', '1', '2', '3'
    , '4', '5', '6', '7', '8', '9'
    > adfgvx_table_uppercase;

typedef ATHENA_CIPHERS_ALPHABET_ADFGVX_TABLE_TYPE<
    ATHENA_CIPHERS_ALPHABET_CHAR_TYPE
    , 'e', 't', 'a', 'o', 'n', 'r'
    , 'i', 's', 'h', 'd', 'l', 'f'
    , 'c', 'm', 'u', 'g', 'y', 'p'
    , 'w', 'b', 'v', 'k', 'j', 'x'
    , 'q', 'z', '0', '1', '2', '3'
    , '4', '5', '6', '7', '8', '9'
    > adfgvx_table_lowercase;

#endif // !defined(ATHENA_CIPHERS_NO_USE_DEFAULT_ADFGVX_ALPHABET)

} // namespace ciphers
} // namespace athena

#endif // ATHENA_CIPHERS_ALPHABET_ENGLISH_HPP
