# Factorial Calculators for Different Data Types

A selection of factorial calculations for the various data types available to C demonstrating the limitations
in those datatypes in dealing with very large numbers.

## C functions within the program 
### Driver Functions
The driver functions set up the environment then a main loop that calls the related calculator function a specified number of times. The start and end values are provided as arguments to the program's main
routine.
```
void factorial_u32(uint64_t nbegin, uint64_t nend);
void factorial_s32(uint64_t nbegin, uint64_t nend);
void factorial_u64(uint64_t nbegin, uint64_t nend);
void factorial_s64(uint64_t nbegin, uint64_t nend);

void factorial_u64_unrolled(uint64_t nbegin, uint64_t nend);
void factorial_u64_tabular(uint64_t nbegin, uint64_t nend);

void factorial_float(uint64_t nbegin, uint64_t nend);
void factorial_double(uint64_t nbegin, uint64_t nend);
void factorial_longdouble(uint64_t nbegin, uint64_t nend);

void factorial_gmp(uint64_t nbegin, uint64_t nend);
void factorial_gfg(uint64_t nbegin, uint64_t nend);
```
### Factorial Calculators
Each calculator uses an iterative method to resolve the factorial of the value given as the argument to the function. Each function displays the result to the standard output stream. The functions are broken into three major groups: integer, floating point, and arbitary precision. The integer calculations are further broken down into iterative, unrolled loop and tabular methods.
```
void fact_u32(uint64_t val);
void fact_s32(uint64_t val);
void fact_u64(uint64_t val);
void fact_s64(uint64_t val);

void fact_u64_unrolled(uint64_t val);
void fact_u64_tabular(uint64_t val);

void fact_float(uint64_t val);
void fact_double(uint64_t val);
void fact_longdouble(uint64_t val);

void fact_gmp(uint64_t val);
void gfg_factorial(uint64_t n_fact);
```
## Methodology
### Integer Calculators
***NOTE:** In the current compiler implementation; `long int` and `long long int` are both 64-bit.*

While the C standard indicates that unsigned integer calculations can never overflow, this logically not
acceptable when calculating larhe integers. Because the language does not trap these overflows or throw exceptions the program takes steps to ensure that logical overflows are trapped and handled. The mechanism used via functions from the GNU built-in methods that perform arithmetic overflow checking:  `__builtin_umul_overflow()` and `__builtin_smul_overflow()` etc. See the GNU document [Built-in Functions to Perform Arithmetic with Overflow Checking](https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html) for details.

It should also be noted that the maximum size for `unsigned int`, `unsigned long int`, and `unsigned long long int` run out of space in very short order. 
See the following table for details:

| Factorial | Type | Value | Maximum Signed Value | Maximum Unsigned Value |
| :--- | :--- | ---: | ---: | ---: |
| **12!** | 32-bit int | `479001600` | `2147483647` | `4294967295` |
| **13!** | &mdash; | `6227020800` | &mdash; | &mdash; |
| **20!** | 64-bit int | `2432902008176640000` | `9223372036854775807` | `18446744073709551615` |
| **21!** | &mdash; | `51090942171709440000` | &mdash; | &mdash; |

and the same data after pivoting the tables to better see the progression:

| 32-bit values | &nbsp; | &mdash; | 64-bit values | &nbsp; |
| :---------------- | ---: | :--------------------: |  :----------------  | ---: |
| **12!**              |   `479001600` | &mdash; | **20!**                                        |   `2432902008176640000` |
| **`INT_MAX`**   | `2147483647` | &mdash; |  **`LONG_MAX`/`LLONG_MAX`**    |   `9223372036854775807` |
| **`UINT_MAX`** | `4294967295` | &mdash; | **`ULONG_MAX`/`ULLONG_MAX`** | `18446744073709551615` |
| **13!**              | `6227020800` | &mdash; | **21!**                                        | `51090942171709440000` |

As these values are not particularly large, the largest iteration is 20 before integers run out of space, it's simple to unroll both unroll loop and generate a lookup table fro the first 20 factorrial values. Both of these solutions are presented and the table of factorials is presented below.

### Table of factorial values from 1! to 20!
```
  uint64_t const factorials[] = {
    /* 0!*/                   0ULL, /* TODO: Added to make picking factorials intuitive */
    /* 1!*/                   1ULL,
    /* 2!*/                   2ULL,
    /* 3!*/                   6ULL,
    /* 4!*/                  24ULL,
    /* 5!*/                 120ULL,
    /* 6!*/                 720ULL,
    /* 7!*/                5040ULL,
    /* 8!*/               40320ULL,
    /* 9!*/              362880ULL,
    /*10!*/             3628800ULL,
    /*11!*/            39916800ULL,
    /*12!*/           479001600ULL, /* TODO: max factorial for 32-bit integers */
    /*13!*/          6227020800ULL,
    /*14!*/         87178291200ULL,
    /*15!*/       1307674368000ULL,
    /*16!*/      20922789888000ULL,
    /*17!*/     355687428096000ULL,
    /*18!*/    6402373705728000ULL,
    /*19!*/  121645100408832000ULL,
    /*20!*/ 2432902008176640000ULL, /* TODO: max factorial for 64-bit integers */
  };
  size_t factorials_c = sizeof(factorials) / sizeof(*factorials);
```

### Arbitrary Precision Arithmetic Calculators

Two methods are presented that provide arbitrary precision solutions; one via the [GNU Multiple Precision Arithmetic Library](https://gmplib.org), the other from an article on the [Geeks for Geeks](https://www.geeksforgeeks.org/factorial-large-number/) portal. These methods both provide results that far outstrip the results of the largest available integer calculators.

### Floating Point Calculators

For completness the floating point types are also provided. The three floating point types `float`, `double`, and `long double`. These types while allowing very large values are limited in accuracy due to the design of floating point arithmatic and the losses introduced. However, floating point results perform marginally better than their integer equivalents: a float is accurate up to 13!, double to 22!, and long double to 25!

| Factorial | Type  | Value |
| :--- | :--- | ---: |
| **12!** | `int32_t` & `uint32_t` | `479001600` |
| **13!** | `float` | `6227020800` |
| **20!** | `int64_t` & `uint64_t` | `2432902008176640000` |
| **22!** | `double` | `1124000727777607680000` |
| **25!** | `long double` | `15511210043330985984000000` |

## Appendices

### A1. Build Details
Built with Xcode 11.3.1 (clang C and clang++ C++ compilers).

#### Additional Build switches
**C Switches**
: **`-std=gnu17`** *[C Language Dialect]*

**C++ Switches**
: **`-std=gnu++17`** *[C++ Language Dialect]*

**Other Linker Flags**
:  **`-lm`** *[Math Library]*
: **`-lgmp`** *[GNU Multiple Precision Library]*

**Entitlements**
: **Disable Library Validation**: `Yes`

### A2. References
- <https://www.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html>
- <https://gmplib.org/>
- <https://gmplib.org/manual/>
- <https://github.com/opencv/opencv/issues/15645>
- <https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html>
- <https://www.geeksforgeeks.org/factorial-large-number/>
