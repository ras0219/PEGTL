// Copyright (c) 2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_INTERNAL_PREDICATES_HPP
#define TAO_PEGTL_INTERNAL_PREDICATES_HPP

#include "../config.hpp"

#include "enable_control.hpp"
#include "failure.hpp"

#include "../type_list.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< typename Peek, typename... Predicates >
   struct predicates
   {
      using peek_t = Peek;
      using data_t = typename Peek::data_t;

      using rule_t = predicates;
      using subs_t = empty_list;

      [[nodiscard]] static bool test( const data_t c ) noexcept
      {
         return ( Predicates::test( c ) || ... );  // TODO: Static assert that predicates::peek_t is the same as peek_t?!
      }

      template< typename ParseInput >
      [[nodiscard]] static bool match( ParseInput& in ) noexcept( noexcept( Peek::peek( in ) ) )
      {
         if( const auto t = Peek::peek( in ) ) {
            if( test( t.data ) ) {
               in.bump( t.size );
               return true;
            }
         }
         return false;
      }
   };

   template< typename Peek >
   struct predicates< Peek >
      : failure
   {};

   template< typename Peek, typename... Predicates >
   inline constexpr bool enable_control< predicates< Peek, Predicates... > > = false;

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif