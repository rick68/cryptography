//
// detail/last.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_DETAIL_LAST_HPP
#define ATHENA_CIPHERS_DETAIL_LAST_HPP

// STL
#include <cstddef>

// Boost.Config
#include <boost/config/suffix.hpp>

// Boost.Preprocessor
#include <boost/preprocessor/dec.hpp>

// Athena.Ciphers
#include "config.hpp"
#include "random_access.hpp"

namespace athena {
namespace ciphers {
namespace detail {

template <typename Sequence>
struct last
{
  BOOST_STATIC_CONSTANT(
      char_type
    , value = ATHENA_CIPHERS_DETAIL_RANDOM_ACCESS(
          Sequence
        , BOOST_PP_DEC(ATHENA_CIPHERS_ALPHABET_NUMBER)
        )
    );
};

} // detail
} // ciphers
} // athena

#endif // ATHENA_CIPHERS_DETAIL_LAST_HPP
