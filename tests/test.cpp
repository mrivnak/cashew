#include <catch2/catch_test_macros.hpp>
#include <cashew.hpp>

TEST_CASE( "hello returns Cashew", "[hello]" )
{
    REQUIRE( hello() == "Cashew" );
}

TEST_CASE( "get_42 returns 42", "[get_42]" )
{
    REQUIRE( get_42() == 42 );
}