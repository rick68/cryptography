//
// alphabet.cpp
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
#include "../ciphers/table_array.hpp"

#include "unit_test.hpp"

// STL
#include <iostream>

//------------------------------------------------------------------------------

// table_array_compile test
// ~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// table_array compile and link correctly. Runtime failures are ignored.

namespace table_array_compile {

void test()
{
  using namespace athena::ciphers;

  typedef table_array<uppercase> uppercase_array;
  typedef table_array<lowercase> lowercase_array;
}

} // namespace table_array_compile

//------------------------------------------------------------------------------

// table_array_runtime test
// ~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that the various public member functions meet the
// necessary postconditions.

namespace table_array_runtime {

void test()
{
  using namespace athena::ciphers;

  typedef table_array<uppercase> uppercase_array;
  typedef table_array<lowercase> lowercase_array;

  std::cout << "uppercase: " << uppercase_array::data << std::endl;
  std::cout << "lowercase: " << lowercase_array::data << std::endl;
}

} // namespace table_array_runtime

ATHENA_CIPHERS_TEST_SUITE
(
  "alphabet",
  ATHENA_CIPHERS_TEST_CASE(table_array_compile::test)
  ATHENA_CIPHERS_TEST_CASE(table_array_runtime::test)
)
