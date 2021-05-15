## Welcome to the Kivi programming language

![The Kivi Logo](https://postimg.cc/2qHmRHH7)

```c
gcd a, b:
{
	while b:
	{
		auto tmp = b;
		b = a % b;
		a = b;
	}

	return a;
}

```

### About Kivi

**What is Kivi?**

Kivi is a compiler under active development. It has educational purposes only. Kivi is designed to process a (currently) simplified C-like language, classified as procedural imperative general purpose programming language.

**Why is Kivi?**

Kivi is initially started as a Software development school project at ELSYS. The principle objectives for us, the creators, are to learn about the fundamental ideas and design principles associated with compiler and programming language design.

**What is Kivi not?**

It is not intended as a useful programming language in real world project. Although Kivi has a lot of similarities to the C programming language, is not intended to be an alternative implementation of any C compiler.

**How to Kivi?**

Additional dev-documentation is provided [here](dev/dev.md).

**What is in Kivi?**

The current functionalities supported are:
- mathematical expressions
- variable definitions
- function definitions
- control flow
	+ `if` statements
	+ `while` statements
	+ `return`

Some of the next things which are going to be implemented:
- type system
- pointers

**Useful links**

[Code documentation](doc-build/index.html)

[GitHub repository](https://github.com/boki1/kivi)
