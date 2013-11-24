//
// detail/length.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ATHENA_CIPHERS_DETAIL_LENGTH_HPP
#define ATHENA_CIPHERS_DETAIL_LENGTH_HPP

// STL
#include <cstddef>

// Boost.Config
#include <boost/config/suffix.hpp>

// Boost.MPL
#include <boost/mpl/size.hpp>

namespace athena {
namespace ciphers {
namespace detail {

template <typename Sequence>
struct length
{
  BOOST_STATIC_CONSTANT(
      std::size_t,
      value = boost::mpl::size<Sequence>::value);
};

} // detail
} // ciphers
} // athena

#endif // ATHENA_CIPHERS_DETAIL_LENGTH_HPP
