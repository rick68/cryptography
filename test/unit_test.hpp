//
// unit_test.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include "../ciphers/detail/config.hpp"

#if defined(ATHENA_CIPHERS_STANDALONE)

#include <cassert>
#include <iostream>

#if defined(NDEBUG)
# error NDEBUG must not be defined when building these unit tests
#endif // defined(NDEBUG)

#define ATHENA_CIPHERS_CHECK(expr) assert(expr)

#define ATHENA_CIPHERS_CHECK_MESSAGE(expr, msg) \
  do { if (!(expr)) { std::cout << msg << std::endl; assert(expr); } } while (0)

#define ATHENA_CIPHERS_WARN_MESSAGE(expr, msg) \
  do { if (!(expr)) { std::cout << msg << std::endl; } } while (0)

#define ATHENA_CIPHERS_ERROR(msg) assert(0 && msg)

#define ATHENA_CIPHERS_TEST_SUITE(name, tests) \
  int main() \
  { \
    std::cout << name << " test suite begins" << std::endl; \
    tests \
    std::cout << name << " test suite ends" << std::endl; \
    return 0; \
  }

#define ATHENA_CIPHERS_TEST_CASE(test) \
  test(); \
  std::cout << #test << " passed" << std::endl;

#else // defined(ATHENA_CIPHERS_STANDALONE)

#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;

#define ATHENA_CIPHERS_CHECK(expr) BOOST_CHECK(expr)

#define ATHENA_CIPHERS_CHECK_MESSAGE(expr, msg) BOOST_CHECK_MESSAGE(expr, msg)

#define ATHENA_CIPHERS_WARN_MESSAGE(expr, msg) BOOST_WARN_MESSAGE(expr, msg)

#define ATHENA_CIPHERS_ERROR(expr) BOOST_ERROR(expr)

#define ATHENA_CIPHERS_TEST_SUITE(name, tests) \
  test_suite* init_unit_test_suite(int, char*[]) \
  { \
    test_suite* t = BOOST_TEST_SUITE(name); \
    tests \
    return t; \
  }

#define ATHENA_CIPHERS_TEST_CASE(test) \
  t->add(BOOST_TEST_CASE(&test));

#endif // defined(ATHENA_CIPHERS_STANDALONE)

inline void null_test()
{
}

#endif // UNIT_TEST_HPP
