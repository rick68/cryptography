//
// alphabet/english.cpp
// ~~~~~~~~~~~~~~~~~~~~
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
#include "../../ciphers/alphabet/english.hpp"

#include "../unit_test.hpp"

ATHENA_CIPHERS_TEST_SUITE
(
  "english",
  ATHENA_CIPHERS_TEST_CASE(null_test)
)
