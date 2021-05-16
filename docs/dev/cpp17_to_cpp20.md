### Cpp17 to Cpp20 transition

-----------

The project is currently developed for `C++17`. Here are listed some major parts of the codebase which should be modified when `C++20` starts to be utilized used.

-------------

1. Add hierarchy to parser's syntactical structure  (that is `expression`, `statement`, etc.) using `cpp20`'s `<concept>` in order to mark their specific "type".

2. Use `<format>` for string formatting.
    - Error reporting

