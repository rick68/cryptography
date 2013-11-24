//
// detail/config.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_DETAIL_CONFIG_HPP
#define ATHENA_CIPHERS_DETAIL_CONFIG_HPP

#if !defined(ATHENA_CIPHERS_NO_USE_DEFAULT_ALPHABTE)
# include "../alphabet/english.hpp"
#endif // defined(ATHENA_CIPHERS_NO_USE_DEFAULT_ALPHABTE)

namespace athena {
namespace ciphers {

typedef ATHENA_CIPHERS_ALPHABET_CHAR_TYPE char_type;
enum { alphabet_number = ATHENA_CIPHERS_ALPHABET_NUMBER };

} // ciphers
} // athena

#endif // ATHENA_CIPHERS_DETAIL_CONFIG_HPP
