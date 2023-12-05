# TFCTech Coding conventions

## Classes
### Class names
Class names shall be `PascalCase`, meaning every word shall be upper-case,
otherwise all the other letters shall be lower-case. Underscores between words are strongly 
discouraged but are allowed to clarify acronyms or abbreviations, e.g., `MPI_ID` is allowed to 
prevent having to use `MPIID`.

### Class method names
Class method-names should be `camelCase`, meaning every word, except the first, should be 
upper-case, otherwise all the other letters shall be lower-case. Underscores are strongly 
discouraged. Exceptions are allowed for using an upper-case character for the first character,
as well as for the use of underscores, just make sure there is a good reason for this.

### Class member names
Class member-names shall be `snake_case_` with a trailing underscore. Exceptions to the trailing
underscore are allowed, e.g., if using the member's `operator()` like what is done in the `TFC` 
runtime, i.e., `TFC::log()`.

## Switch conditional blocks
### Use GCC to enforce all enums are supported
```c++
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wswitch-enum"
switch (option)
{
  ...
}
#pragma GCC diagnostic push
```
