/**
 * @file config_test.cc
 * @brief Configures the catch2 testing framework.
 * @note  Checkout https://github.com/catchorg/Catch2/blob/devel/docs/slow-compiles.md for more information.
 */

#include <catch2/catch2.hpp>

TEST_CASE("configure catch2")
{
	SECTION("it works")
	{
		REQUIRE(true);
	}
}
