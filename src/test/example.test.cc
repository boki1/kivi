/**
 * @file example_test.cc
 * @brief Demonstrates an example usage of the catch2 testing framework
 */

#include <exception>

#include <catch2/catch2.hpp>

class fib_bad_arg_exception : std::exception
{
 private:
	int m_bad_arg;
 public:
	explicit fib_bad_arg_exception(int bad_arg) : m_bad_arg(bad_arg)
	{
	}
};

constexpr static int fib(int n)
{
	if (n < 0)
	{
		throw fib_bad_arg_exception(n);
	}
	else if (n >= 100)
	{
		throw fib_bad_arg_exception(n);
	}

	switch (n)
	{
	case 0:
		return 0;
	case 1:
		return 1;
	};

	return fib(n - 1) + fib(n - 2);
}

TEST_CASE("Fibonacci calculator", "[fib]")
{
	SECTION("legal positive number")
	{
		REQUIRE(fib(5) == 5);
	}

	SECTION("illegal positive number")
	{
		REQUIRE_THROWS(fib(101));
	}

	SECTION("negative number")
	{
		REQUIRE_THROWS(fib(-3));
	}

	SECTION("zero")
	{
		REQUIRE(fib(0) == 0);
	}

	SECTION("one")
	{
		REQUIRE(fib(1) == 1);
	}
}
