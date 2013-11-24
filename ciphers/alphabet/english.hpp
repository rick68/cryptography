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
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30
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
    ATHENA_CIPHERS_ALPHABET_CHAR_TYPE,
    'A', 'B', 'C', 'D', 'E',
    'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y',
    'Z'> uppercase;

typedef ATHENA_CIPHERS_ALPHABET_SEQUENCE_TYPE<
    ATHENA_CIPHERS_ALPHABET_CHAR_TYPE,
    'a', 'b', 'c', 'd', 'e',
    'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y',
    'z'> lowercase;

} // namespace ciphers
} // namespace athena

#endif // ATHENA_CIPHERS_ALPHABET_ENGLISH_HPP
