// Copyright (c) 2015-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#include <iostream>

#include "lua53.hpp"

int main( int argc, char** argv )  // NOLINT(bugprone-exception-escape)
{
   for( int i = 1; i < argc; ++i ) {
      TAO_PEGTL_NAMESPACE::file_input in( argv[ i ] );
      const auto r = TAO_PEGTL_NAMESPACE::parse< lua53::grammar >( in );
      std::cout << argv[ i ] << " " << r << std::endl;
   }
   return 0;
}
