//
// caesar.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Disable autolinking for unit tests.
#if !defined(BOOST_ALL_NO_LIB)
#define BOOST_ALL_NO_LIB 1
#endif // !defined(BOOST_ALL_NO_LIB)

// Test that header file is self-contained.
#include "../ciphers/caesar.hpp"

// Athena.Ciphers
#include "unit_test.hpp"

// Boost.Preprocessor
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

// STL
#include <iostream>
#include <string>
#include <cstddef>

//------------------------------------------------------------------------------

// caesar_compile test
// ~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// caesar compile and link correctly. Runtime failures are ignored.

#define UNIT_TEST_CAESAR_COMPILE_MACRO(z, n, text) \
    UNIT_TEST_CAESAR_TYPEDEF_MACRO_D(uppercase, n) \
    UNIT_TEST_CAESAR_TYPEDEF_MACRO_D(lowercase, n) \
    UNIT_TEST_CAESAR_INSTANCE_MACRO_D(uppercase, n) \
    UNIT_TEST_CAESAR_INSTANCE_MACRO_D(lowercase, n) \
    /**/
#define UNIT_TEST_CAESAR_TYPEDEF_MACRO_D(text, n) \
    typedef caesar<text, n> \
	    BOOST_PP_CAT(BOOST_PP_CAT(caesar, n), BOOST_PP_CAT(text, _t)); \
    /**/

#define UNIT_TEST_CAESAR_INSTANCE_MACRO_D(text, n) \
    BOOST_PP_CAT(BOOST_PP_CAT(caesar, n), BOOST_PP_CAT(text, _t)) \
	BOOST_PP_CAT(BOOST_PP_CAT(caesar, n), text); \
    /**/

namespace caesar_compile {

void test()
{
  using namespace athena::ciphers;

  BOOST_PP_REPEAT_FROM_TO(
      0,
      ATHENA_CIPHERS_ALPHABET_NUMBER,
      UNIT_TEST_CAESAR_COMPILE_MACRO, ~)
}

} // namespace caesar_compile

//------------------------------------------------------------------------------

// caesar_runtime test
// ~~~~~~~~~~~~~~~~~~~
// The following test checks that the various public member functions meet the
// necessary postconditions.

#define UNIT_TEST_CAESAR_RUNTIME_MACRO(z, n, text) \
    UNIT_TEST_CAESAR_TYPEDEF_MACRO_D(uppercase, n) \
    UNIT_TEST_CAESAR_TYPEDEF_MACRO_D(lowercase, n) \
    UNIT_TEST_CAESAR_RUNTIME_ENCODE_MACRO(uppercase, n) \
    UNIT_TEST_CAESAR_RUNTIME_DECODE_MACRO(uppercase, n) \
    ATHENA_CIPHERS_CHECK(str == tmp); \
    UNIT_TEST_CAESAR_RUNTIME_ENCODE_MACRO(lowercase, n) \
    UNIT_TEST_CAESAR_RUNTIME_DECODE_MACRO(lowercase, n) \
    ATHENA_CIPHERS_CHECK(str == tmp); \
    /**/

#define UNIT_TEST_CAESAR_RUNTIME_ENCODE_MACRO(text, n) \
    for (std::size_t i = 0; i < str.size(); ++i) \
      tmp[i] = BOOST_PP_CAT \
          (BOOST_PP_CAT(caesar, n), BOOST_PP_CAT(text, _t))::encode(str[i]); \
    /**/

#define UNIT_TEST_CAESAR_RUNTIME_DECODE_MACRO(text, n) \
    for (std::size_t i = 0; i < str.size(); ++i) \
      tmp[i] = BOOST_PP_CAT \
          (BOOST_PP_CAT(caesar, n), BOOST_PP_CAT(text, _t))::decode(tmp[i]); \
    /**/

namespace caesar_runtime {

inline void
show_string(const char* alphabet_name, const std::string& str)
{
  std::cout << str << std::endl;
}

void test()
{
  using namespace athena::ciphers;

  std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::string tmp;
  tmp.resize(str.size());

  BOOST_PP_REPEAT_FROM_TO(
      0,
      ATHENA_CIPHERS_ALPHABET_NUMBER,
      UNIT_TEST_CAESAR_RUNTIME_MACRO, ~)
}

} // namespace caesar_runtime

ATHENA_CIPHERS_TEST_SUITE
(
  "caesar",
  ATHENA_CIPHERS_TEST_CASE(caesar_compile::test)
  ATHENA_CIPHERS_TEST_CASE(caesar_runtime::test)
)
