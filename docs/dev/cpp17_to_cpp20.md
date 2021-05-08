### Cpp17 to Cpp20 transition

1. The whole parser hierarchy (that is `I_expression`, `I_statement`, etc.) should be instead of interface defined,
using `cpp20`'s `<concept>` in order to mark their specific "type".

2. Use `<format>` for string formatting.
    - Error reporting

