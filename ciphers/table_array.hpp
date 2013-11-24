//
// table_array.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_TABLE_ARRAY_HPP
#define ATHENA_CIPHERS_TABLE_ARRAY_HPP

// STL
#include <cstddef>

// Boost.Config
#include <boost/config/suffix.hpp>

// Boost.Preprocessor
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Athena.Ciphers
#include "detail/config.hpp"
#include "detail/random_access.hpp"

namespace athena {
namespace ciphers {

template <typename Sequence>
struct table_array
{
  static const char data[alphabet_number + 1];
};

template <typename Sequence>
const char table_array<Sequence>::data[alphabet_number + 1] =
{
  BOOST_PP_REPEAT_FROM_TO(
      0,
      ATHENA_CIPHERS_ALPHABET_NUMBER,
      ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS_PP_REPEAT_MACRO,
      Sequence)
  '\0'
};

} // ciphers
} // athena

#endif // ATHENA_CIPHERS_TABLE_ARRAY_HPP
