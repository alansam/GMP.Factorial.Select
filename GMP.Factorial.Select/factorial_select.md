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
void factorial_u128(uint64_t nbegin, uint64_t nend);
void factorial_s128(uint64_t nbegin, uint64_t nend);

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
void fact_u128(uint64_t val);
void fact_s128(uint64_t val);

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
***NOTE:** In the current compiler implementation; `long int` and `long long int` are both 64-bit.* *Limited 128-bit support is available with gcc and clang compilers.*

While the C standard indicates that unsigned integer calculations can never overflow, this is, logically, not
acceptable when calculating large integers. Because the language does not trap these overflows or throw exceptions the program takes steps to ensure that logical overflows are trapped and handled. The mechanism used is via functions from the GNU built-in methods that perform arithmetic overflow checking:  `__builtin_umul_overflow()` and `__builtin_smul_overflow()` etc. See the GNU document [Built-in Functions to Perform Arithmetic with Overflow Checking](https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html) for details.

It should also be noted that the maximum size for `unsigned int`, `unsigned long int`, and `unsigned long long int` run out of space in very short order. 
See the following table for details:

| Factorial | Type | Value | Maximum Signed Value | Maximum Unsigned Value |
| :--------- | :------- | ---: | ---: | ---: |
| **12!** | `32-bit int` | `479001600` | `2147483647` | `4294967295` |
| **13!** | &mdash; | `6227020800` | &mdash; | &mdash; |
| **20!** | `64-bit int` | `2432902008176640000` | `9223372036854775807` | `18446744073709551615` |
| **21!** | &mdash; | `51090942171709440000` | &mdash; | &mdash; |
| **33!** | `128-bit int` | `8683317618811886495518194401280000000` |  `170141183460469231731687303715884105727` | &mdash; |
| **34!** | `128-bit int` | `295232799039604140847618609643520000000` | &mdash; | `340282366920938463463374607431768211455` |
| **35!** | &mdash; | `10333147966386144929666651337523200000000` | &mdash; | &mdash; |


and the same data after pivoting the tables to better see the progression:

| 32-bit values | &nbsp; | &mdash; | 64-bit values | &nbsp; | &mdash; | 128-bit values| &nbsp; |
| :---------------- | ---: | :--------------------: |  :----------------  | ---: | :---: | :--- | ---: |
| **12!**              |   `479001600` | &mdash; | **20!**                                        |   `2432902008176640000` |&mdash; | **33!** | `8683317618811886495518194401280000000` |
| **`INT_MAX`**   | `2147483647` | &mdash; |  **`LONG_MAX`/`LLONG_MAX`**    |   `9223372036854775807` |&mdash; | max signed | `170141183460469231731687303715884105727` |
| **`UINT_MAX`** | `4294967295` | &mdash; | **`ULONG_MAX`/`ULLONG_MAX`** | `18446744073709551615` |&mdash; | **34!** | `295232799039604140847618609643520000000` |
| **13!**              | `6227020800` | &mdash; | **21!**                                        | `51090942171709440000` |&mdash; | max unsigned | `340282366920938463463374607431768211455` |
| &nbsp;            | &nbsp;            | &mdash; | &nbsp;                                       | &nbsp;                                 |&mdash; | **35!** | `10333147966386144929666651337523200000000` |

As these values are not particularly large, the largest iteration is 20 before integers run out of space, it's simple to unroll both unroll loop and generate a lookup table for the first 20 factorial values. Both of these solutions are presented; the table of factorials is shown below.

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

#### Table of Factorials from 1! to 54! ####

| Factorial | Value |
| ---: | ---: |
| **1!** | `1` |
| **2!** | `2` |
| **3!** | `6` |
| **4!** | `24` |
| **5!** | `120` |
| **6!** | `720` |
| **7!** | `5040` |
| **8!** | `40320` |
| **9!** | `362880` |
| **10!** | `3628800` |
| **11!** | `39916800` |
| **12!** | `479001600` |
| **13!** | `6227020800` |
| **14!** | `87178291200` |
| **15!** | `1307674368000` |
| **16!** | `20922789888000` |
| **17!** | `355687428096000` |
| **18!** | `6402373705728000` |
| **19!** | `121645100408832000` |
| **20!** | `2432902008176640000` |
| **21!** | `51090942171709440000` |
| **22!** | `1124000727777607680000` |
| **23!** | `25852016738884976640000` |
| **24!** | `620448401733239439360000` |
| **25!** | `15511210043330985984000000` |
| **26!** | `403291461126605635584000000` |
| **27!** | `10888869450418352160768000000` |
| **28!** | `304888344611713860501504000000` |
| **29!** | `8841761993739701954543616000000` |
| **30!** | `265252859812191058636308480000000` |
| **31!** | `8222838654177922817725562880000000` |
| **32!** | `263130836933693530167218012160000000` |
| **33!** | `8683317618811886495518194401280000000` |
| **34!** | `295232799039604140847618609643520000000` |
| **35!** | `10333147966386144929666651337523200000000` |
| **36!** | `371993326789901217467999448150835200000000` |
| **37!** | `13763753091226345046315979581580902400000000` |
| **38!** | `523022617466601111760007224100074291200000000` |
| **39!** | `20397882081197443358640281739902897356800000000` |
| **40!** | `815915283247897734345611269596115894272000000000` |
| **41!** | `33452526613163807108170062053440751665152000000000` |
| **42!** | `1405006117752879898543142606244511569936384000000000` |
| **43!** | `60415263063373835637355132068513997507264512000000000` |
| **44!** | `2658271574788448768043625811014615890319638528000000000` |
| **45!** | `119622220865480194561963161495657715064383733760000000000` |
| **46!** | `5502622159812088949850305428800254892961651752960000000000` |
| **47!** | `258623241511168180642964355153611979969197632389120000000000` |
| **48!** | `12413915592536072670862289047373375038521486354677760000000000` |
| **49!** | `608281864034267560872252163321295376887552831379210240000000000` |
| **50!** | `30414093201713378043612608166064768844377641568960512000000000000` |
| **51!** | `1551118753287382280224243016469303211063259720016986112000000000000` |
| **52!** | `80658175170943878571660636856403766975289505440883277824000000000000` |
| **53!** | `4274883284060025564298013753389399649690343788366813724672000000000000` |
| **54!** | `230843697339241380472092742683027581083278564571807941132288000000000000` |


### Floating Point Calculators

For completness the floating point types are also provided. The three floating point types `float`, `double`, and `long double`. These types while allowing very large values are limited in accuracy due to the design of floating point arithmatic and the losses introduced. However, floating point results perform marginally better than their integer equivalents: a float is accurate up to 13!, double to 22!, and long double to 25!

| Factorial | Type  | Value |
| :--- | :--- | ---: |
| **12!** | `int32_t` &amp; `uint32_t` | `479001600` |
| **13!** | `float` | `6227020800` |
| **20!** | `int64_t` &amp; `uint64_t` | `2432902008176640000` |
| **22!** | `double` | `1124000727777607680000` |
| **25!** | `long double` | `15511210043330985984000000` |
| **33!** | `__int128` | `8683317618811886495518194401280000000` |
| **34!** | `unsigned __int128` | `295232799039604140847618609643520000000` |

#### Comparison of results. Multiple precision vs floating point. ####

| Factorial | Value | Type | Match | Note |
| :--- | ---: | :--- | :---: | :--- |
| **10!** | `3628800` | &ndash; | &ndash; | |
| **10!** | `3628800` | `long double` | **yes** | |
| **10!** | `3628800` | `double` | **yes** | |
| **10!** | `3628800` | `float` | **yes** | |
| &nbsp; | | | | |
| **11!** | `39916800` | &ndash; | &ndash; | |
| **11!** | `39916800` | `long double` | **yes** | |
| **11!** | `39916800` | `double` | **yes** | |
| **11!** | `39916800` | `float` | **yes** | |
| &nbsp; | | | | |
| **12!** | `479001600` | &ndash; | &ndash; | *max factorial for 32-bit integers* |
| **12!** | `479001600` | `long double` | **yes** | |
| **12!** | `479001600` | `double` | **yes** | |
| **12!** | `479001600` | `float` | **yes** | |
| &nbsp; | | | | |
| **13!** | `6227020800` | &ndash; | &ndash; | |
| **13!** | `6227020800` | `long double` | **yes** | |
| **13!** | `6227020800` | `double` | **yes** | |
| **13!** | `6227020800` | `float` | **yes** | *&lt;-- last float* |
| &nbsp; | | | | |
| **14!** | `87178291200` | &ndash; | &ndash; | |
| **14!** | `87178291200` | `long double` | **yes** | |
| **14!** | `87178291200` | `double` | **yes** | |
| **14!** | `87178289152` | `float` | **low** | |
| &nbsp; | | | | |
| **15!** | `1307674368000` | &ndash; | &ndash; | |
| **15!** | `1307674368000` | `long double` | **yes** | |
| **15!** | `1307674368000` | `double` | **yes** | |
| **15!** | `1307674279936` | `float` | **high** | |
| &nbsp; | | | | |
| **16!** | `20922789888000` | &ndash; | &ndash; | |
| **16!** | `20922789888000` | `long double` | **yes** | |
| **16!** | `20922789888000` | `double` | **yes** | |
| **16!** | `20922788478976` | `float` | **low** | |
| &nbsp; | | | | |
| **17!** | `355687428096000` | &ndash; | &ndash; | |
| **17!** | `355687428096000` | `long double` | **yes** | |
| **17!** | `355687428096000` | `double` | **yes** | |
| **17!** | `355687414628352` | `float` | **low** | |
| &nbsp; | | | | |
| **18!** | `6402373705728000` | &ndash; | &ndash; | |
| **18!** | `6402373705728000` | `long double` | **yes** | |
| **18!** | `6402373705728000` | `double` | **yes** | |
| **18!** | `6402373530419200` | `float` | **low** | |
| &nbsp; | | | | |
| **19!** | `121645100408832000` | &ndash; | &ndash; | |
| **19!** | `121645100408832000` | `long double` | **yes** | |
| **19!** | `121645100408832000` | `double` | **yes** | |
| **19!** | `121645096004222976` | `float` | **low** | |
| &nbsp; | | | | |
| **20!** | `2432902008176640000` | &ndash; | &ndash; | *max factorial for 64-bit integers* |
| **20!** | `2432902008176640000` | `long double` | **yes** | |
| **20!** | `2432902008176640000` | `double` | **yes** | |
| **20!** | `2432902023163674624` | `float` | **high** | |
| &nbsp; | | | | |
| **21!** | `51090942171709440000` | &ndash; | &ndash; | |
| **21!** | `51090942171709440000` | `long double` | **yes** | |
| **21!** | `51090942171709440000` | `double` | **yes** | |
| **21!** | `51090940837169725440` | `float` | **low** | |
| &nbsp; | | | | |
| **22!** | `1124000727777607680000` | &ndash; | &ndash; | |
| **22!** | `1124000727777607680000` | `long double` | **yes** | |
| **22!** | `1124000727777607680000` | `double` | **yes** | *&lt;-- last double* |
| **22!** | `1124000724806013026304` | `float` | **low** | |
| &nbsp; | | | | |
| **23!** | `25852016738884976640000` | &ndash; | &ndash; | |
| **23!** | `25852016738884976640000` | `long double` | **yes** | |
| **23!** | `25852016738884978212864` | `double` | **high** | |
| **23!** | `25852017444594485559296` | `float` | **high** | |
| &nbsp; | | | | |
| **24!** | `620448401733239439360000` | &ndash; | &ndash; | |
| **24!** | `620448401733239439360000` | `long double` | **yes** | |
| **24!** | `620448401733239409999872` | `double` | **low** | |
| **24!** | `620448454699064672387072` | `float` | **high** | |
| &nbsp; | | | | |
| **25!** | `15511210043330985984000000` | &ndash; | &ndash; | |
| **25!** | `15511210043330985984000000` | `long double` | **yes** | *&lt;-- last long double* |
| **25!** | `15511210043330986055303168` | `double` | **high** | |
| **25!** | `15511211079246240657965056` | `float` | **high** | |
| &nbsp; | | | | |
| **26!** | `403291461126605635584000000` | &ndash; | &ndash; | |
| **26!** | `403291461126605635592388608` | `long double` | **high** | |
| **26!** | `403291461126605650322784256` | `double` | **high** | |
| **26!** | `403291499589617303175561216` | `float` | **high** | |
| &nbsp; | | | | |
| **33!** | `8683317618811886495518194401280000000` | &ndash; | &ndash; | *max factorial for signed 128-bit integer* |
| **33!** | `8683317618811886496153221372728836096` | `long double` | **high** | |
| **33!** | `8683317618811885938715673895318323200` | `double` | **low** | |
| **33!** | `8683318509846655538309012935952826368` | `float` | **high** | |
| &nbsp; | | | | |
| **34!** | `295232799039604140847618609643520000000` | &ndash; | &ndash; | *max factorial for unsigned 128-bit integer* |
| **34!** | `295232799039604140861139076140532498432` | `long double` | **high** | |
| **34!** | `295232799039604119555149671006000381952` | `double` | **low** | |
| **34!** | `295232822996533287161359432338880069632` | `float` | **high** | |

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
