**Bare minimum**
> ./tools/run.sh\
> ./tools/clean.sh

In order to successfully build you will need:
```
bison>=3.7
re2c=>2.03
g++ (C++17)
cmake>=3.17
make>=4.21
```

**Docs**
> ./tools/doc.sh

In order to successfully build the documentation you will need:
```
Doxygen>=1.8
```

In order to successfully run the tests you will need:
> ./tools/test.sh
>
```
Catch2=2
```

**Optional**
> ghp-import -npf docs/build/html

In order to successfully upload the current version of comment documentation build of `root/docs/build/html` in github pages:
```
ghp-import>=1.1
```


