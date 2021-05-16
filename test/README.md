### Test

This directory contains all the unit tests for the KIVI programming language. The Catch2 framework is used.

-------------

**Contents**

- `backend` Hence the name, the backend/ directory contains the source code related to the implementation of the backend of KIVI compiler.

- `frontend` - The frontend/ directory contains the source code related to the implementation of the frontend of KIVI compiler.

- `config.test.cc` - The file configures the Catch2 testing framework. Checkout the [slow-compiles.md](https://github.com/catchorg/Catch2/blob/devel/docs/slow-compiles.md) section of the Catch2 documentation for more details.

- `example.test.cc` - This file tests all the examples provided by the KIVI compiler.

**How to build my own tests?**

You can always checkout the [Catch2 documentation](https://github.com/catchorg/Catch2/blob/devel/docs/Readme.md#top) for additional information and different examples. However, here we have picked up one that we assume as useful.

```c++
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

```