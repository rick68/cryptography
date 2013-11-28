//
// adfgvx.cpp
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
#include "../ciphers/adfgvx.hpp"

#include "unit_test.hpp"

// STL
#include <iostream>
#include <string>
#include <cstddef>

//------------------------------------------------------------------------------

// adfgvx_compile test
// ~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// adfgvx compile and link correctly. Runtime failures are ignored.

namespace adfgvx_compile {

void test()
{
  using namespace athena::ciphers;

  typedef adfgvx<uppercase> ADFGVX_t;
  typedef adfgvx<lowercase> adfgvx_t;

  std::cout << ADFGVX_t::adfgvx_alphabet << std::endl;
  std::cout << ADFGVX_t::data << std::endl;
  std::cout << adfgvx_t::adfgvx_alphabet << std::endl;
  std::cout << adfgvx_t::data << std::endl;

  ADFGVX_t ADFGVX("CARGO");
  adfgvx_t adfgvx("cargo");
}

} // namespace adfgvx_compile

//------------------------------------------------------------------------------

// adfgvx_runtime test
// ~~~~~~~~~~~~~~~~~~~~~
// The following test checks that the various public member functions meet the
// necessary postconditions.

namespace adfgvx_runtime {

void test()
{
  using namespace athena::ciphers;

  typedef adfgvx<uppercase> ADFGVX_t;
  typedef adfgvx<lowercase> adfgvx_t;

  std::cout << ADFGVX_t::adfgvx_alphabet << std::endl;
  std::cout << ADFGVX_t::data << std::endl;
  std::cout << adfgvx_t::adfgvx_alphabet << std::endl;
  std::cout << adfgvx_t::data << std::endl;

  ADFGVX_t ADFGVX("CARGO");
  adfgvx_t adfgvx("cargo");

  std::cout << ADFGVX.get_key() << std::endl;
  std::cout << adfgvx.get_key() << std::endl;

  std::string utext = "ATTACKATDAWN";
  std::string ltext = "attackatdawn";
  std::string resutl;

  ATHENA_CIPHERS_CHECK(ADFGVX.encrypt(utext, resutl));
  ATHENA_CIPHERS_CHECK(ADFGVX.decipher(resutl));
  ATHENA_CIPHERS_CHECK(resutl == utext);

  ATHENA_CIPHERS_CHECK(ADFGVX.encrypt(resutl));
  ATHENA_CIPHERS_CHECK(ADFGVX.decipher(std::string(resutl), resutl));
  ATHENA_CIPHERS_CHECK(resutl == utext);

  ATHENA_CIPHERS_CHECK(adfgvx.encrypt(ltext, resutl));
  ATHENA_CIPHERS_CHECK(adfgvx.decipher(resutl));
  ATHENA_CIPHERS_CHECK(resutl == ltext);

  ATHENA_CIPHERS_CHECK(ADFGVX.encrypt(resutl));
  ATHENA_CIPHERS_CHECK(ADFGVX.decipher(std::string(resutl), resutl));
  ATHENA_CIPHERS_CHECK(resutl == ltext);

  utext = "A D F G V X";
  ltext = "a d f g v X";

  ATHENA_CIPHERS_CHECK(!ADFGVX.decipher(utext, resutl));
  ATHENA_CIPHERS_CHECK(!adfgvx.decipher(ltext, resutl));
}

} // namespace adfgvx_runtime

ATHENA_CIPHERS_TEST_SUITE
(
  "adfgvx",
  ATHENA_CIPHERS_TEST_CASE(adfgvx_compile::test)
  ATHENA_CIPHERS_TEST_CASE(adfgvx_runtime::test)
)
