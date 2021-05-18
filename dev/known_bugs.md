### Known bugs

-----------

There are a bunch of bugs which are found, but are not highest priority and therefore are not fixed yet. Here we list all them. 

-------------

#### Infinite loop when comma after last function's parameter
1. Example:
```c++
foo n,: {
auto a = 3;
}
```

#### Cannot catch syntax errors from bison
###### Examples
1. `syntax error, unexpected ',', expecting ':'`

```c++
foo ,n: { 
    auto a = 3; 
}
```
2. `syntax error, unexpected END`. Notice there is no new line after the statement, so the `}` is included in the comment. However, the compiler expects the closing bracket symbol at the end of the function and as a result unexpected end syntax error is generated.

```c++
foo { //auto a = 3; }
``` 

3. Cannot catch if while loops occur during the parsing. That should be done as a test. Checkout point 1.
