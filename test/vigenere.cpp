//
// vigenere.cpp
// ~~~~~~~~~~~~
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
#include "../ciphers/vigenere.hpp"

#include "unit_test.hpp"

// STL
#include <iostream>
#include <cstddef>

// Boost.Preproccess
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/cat.hpp>

//------------------------------------------------------------------------------

// vigenere_compile test
// ~~~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// vigenere compile and link correctly. Runtime failures are ignored.

namespace vigenere_compile {

#define UNIT_TEST_VIGENERE_COMPILE_GET_SEQUENCE_PP_PEPEAT_MACRO(z, x, alp) \
  BOOST_PP_REPEAT( \
      ATHENA_CIPHERS_ALPHABET_NUMBER, \
      UNIT_TEST_VIGENERE_COMPILE_GET_ELEM_PP_PEPEAT_MACRO, \
      (alp, x)) \
  /**/

#define UNIT_TEST_VIGENERE_COMPILE_GET_ELEM_PP_PEPEAT_MACRO(z, y, tuple2) \
  typedef vigenere_table< \
      BOOST_PP_TUPLE_ELEM(2, 0, tuple2) BOOST_PP_COMMA() \
      BOOST_PP_TUPLE_ELEM(2, 1, tuple2) BOOST_PP_COMMA() \
      y> \
  BOOST_PP_CAT(vt_, \
  BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 1, tuple2), \
  BOOST_PP_CAT(_, \
  BOOST_PP_CAT(y, \
  BOOST_PP_CAT(_, \
  BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 0, tuple2), _t)))))); \
  /**/

void test()
{
  using namespace athena::ciphers;

  typedef vigenere<uppercase> vu_t;
  typedef vigenere<lowercase> vl_t;

  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_NUMBER,
      UNIT_TEST_VIGENERE_COMPILE_GET_SEQUENCE_PP_PEPEAT_MACRO,
      uppercase)

  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_NUMBER,
      UNIT_TEST_VIGENERE_COMPILE_GET_SEQUENCE_PP_PEPEAT_MACRO,
      lowercase)

  vu_t vu("HELLO");
  vl_t vl("world");
}

} // namespace vigenere_compile

//------------------------------------------------------------------------------

// vigenere_runtime test
// ~~~~~~~~~~~~~~~~~~~~~
// The following test checks that the various public member functions meet the
// necessary postconditions.

namespace vigenere_runtime {

#define UNIT_TEST_VIGENERE_RUNTIME_SHOW_SEQUENCE_PP_PEPEAT_MACRO(z, x, alp) \
  BOOST_PP_REPEAT( \
      ATHENA_CIPHERS_ALPHABET_NUMBER, \
      UNIT_TEST_VIGENERE_RUNTIME_SHOW_ELEM_PP_PEPEAT_MACRO, \
      (alp, x)) \
  std::cout << std::endl; \
  /**/

#define UNIT_TEST_VIGENERE_RUNTIME_SHOW_ELEM_PP_PEPEAT_MACRO(z, y, tuple2) \
  std::cout << (char_type) vigenere_table< \
      BOOST_PP_TUPLE_ELEM(2, 0, tuple2) BOOST_PP_COMMA() \
      BOOST_PP_TUPLE_ELEM(2, 1, tuple2) BOOST_PP_COMMA() \
      y>::value; \
  /**/

void vigenere_table_test()
{
  using namespace athena::ciphers;

  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_NUMBER,
      UNIT_TEST_VIGENERE_RUNTIME_SHOW_SEQUENCE_PP_PEPEAT_MACRO,
      uppercase)
  std::cout << vigenere<uppercase>::data << std::endl;

  BOOST_PP_REPEAT(
      ATHENA_CIPHERS_ALPHABET_NUMBER,
      UNIT_TEST_VIGENERE_RUNTIME_SHOW_SEQUENCE_PP_PEPEAT_MACRO,
      lowercase)
  std::cout << vigenere<lowercase>::data << std::endl;
}

void test()
{
  using namespace athena::ciphers;

  vigenere_table_test();

  typedef vigenere<uppercase> vu_t;
  typedef vigenere<lowercase> vl_t;

  vu_t vu("HELLO");
  vl_t vl("world");

  vu_t::string_type vu_kw = vu.keyword();
  vl_t::string_type vl_kw = vl.keyword();

  ATHENA_CIPHERS_CHECK(vu_kw == "HELLO");
  ATHENA_CIPHERS_CHECK(vl_kw == "world");

  std::string utext = "ATTACKATDAWN";
  std::string ltext = "attackatdawn";

  for (std::size_t i = 0, n = 0; i < utext.size(); ++i)
  {
    ATHENA_CIPHERS_CHECK
        (vu.decode(vu.encode(utext[i], vu_kw[n]), vu_kw[n]) == utext[i]);
    ATHENA_CIPHERS_CHECK
        (vl.decode(vl.encode(ltext[i], vl_kw[n]), vl_kw[n]) == ltext[i]);
  }

  ATHENA_CIPHERS_CHECK(vu.decode(vu.encode(utext)) == "ATTACKATDAWN");
  ATHENA_CIPHERS_CHECK(vl.decode(vl.encode(ltext)) == "attackatdawn");
}

} // namespace vigenere_runtime

ATHENA_CIPHERS_TEST_SUITE
(
  "vigenere",
  ATHENA_CIPHERS_TEST_CASE(vigenere_compile::test)
  ATHENA_CIPHERS_TEST_CASE(vigenere_runtime::test)
)
