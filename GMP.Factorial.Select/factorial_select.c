//
//  factorial_select.c
//  GMP.Factorial.Select
//
//  MARK: - References
//  @see: https://www.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html
//  @see: https://gmplib.org/manual/index.html#Top
//  @see: https://github.com/opencv/opencv/issues/15645
//  @see: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
//
//  Created by Alan Sampson on 1/27/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//
//  TODO: - Build Setup
//  TODO: Build Settings -> Linking -> Other Linker Flags -> -lgmp
//  TODO: Build Settings -> Search Paths -> Header Search Paths -> /usr/local/include
//  TODO: Build Settings -> Search Paths -> Library Search Paths -> /usr/local/lib
//  TODO: Signing Capabilities -> Hardened Runtime -> Runtime Exceptions -> Disable Library Validations

//  MARK: - Definitions

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <float.h>
#include <gmp.h>

#include "gfg-factorial.hpp"

//  TODO: Check availability of 128-bit integers
#ifndef __SIZEOF_INT128__
# pragma message "128-bit integers not defined."
# define __SIZEOF_INT128__ sizeof(int32_t)
#endif

//  MARK: - Definition of typedef, union, structure, etc.
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;

//  MARK: union biggar
union biggar {
  uint128_t   ui128;
  int128_t    si128;
  uint64_t    ui64_a[__SIZEOF_INT128__ / sizeof(uint64_t)];
  uint32_t    ui32_a[__SIZEOF_INT128__ / sizeof(uint32_t)];
  uint16_t    ui16_a[__SIZEOF_INT128__ / sizeof(uint16_t)];
  uint8_t     ui8_a[__SIZEOF_INT128__  / sizeof(uint8_t)];
};
typedef union biggar biggar;

// MARK: - Prototypes -
//  MARK: Inline Function Localization
// This needs to be before the inclusion of version_info.h
static
inline
void version_details(void);

#include "version_info.h"

//  MARK: Drivers
void factorial_u32(uint64_t nbegin, uint64_t nend);
void factorial_s32(uint64_t nbegin, uint64_t nend);
void factorial_u64(uint64_t nbegin, uint64_t nend);
void factorial_s64(uint64_t nbegin, uint64_t nend);
void factorial_u128(uint64_t nbegin, uint64_t nend);
void factorial_s128(uint64_t nbegin, uint64_t nend);
void factorial_gmp(uint64_t nbegin, uint64_t nend);
void factorial_gfg(uint64_t nbegin, uint64_t nend);
void factorial_u64_unrolled(uint64_t nbegin, uint64_t nend);
void factorial_u64_tabular(uint64_t nbegin, uint64_t nend);
void factorial_float(uint64_t nbegin, uint64_t nend);
void factorial_double(uint64_t nbegin, uint64_t nend);
void factorial_longdouble(uint64_t nbegin, uint64_t nend);
//  MARK: Factorial Calculators
void fact_u32(uint64_t val);
void fact_s32(uint64_t val);
void fact_u64(uint64_t val);
void fact_s64(uint64_t val);
void fact_u128(uint64_t val);
void fact_s128(uint64_t val);
void fact_gmp(uint64_t val);
void fact_u64_unrolled(uint64_t val);
void fact_u64_tabular(uint64_t val);
void fact_float(uint64_t val);
void fact_double(uint64_t val);
void fact_longdouble(uint64_t val);
//  MARK: Helpers
bool umulj_overflow(uint128_t multiplicand, uint128_t multiplier, uint128_t * product);
bool smulj_overflow(int128_t  multiplicand, int128_t  multiplier, int128_t * product);
char * uint128toa(uint128_t big, char * buffp, size_t const buff_len);
char * int128toa(int128_t big, char * buffp, size_t const buff_len);
int printf_fact128str(uint64_t val, char ** pnrstr, bool overflowed, size_t * ppw_max);

// MARK: - Implementation
/*
 *  MARK: main()
 */
int main(int argc, char const * argv[]) {
  int RC = EXIT_SUCCESS;
  printf("GMP.Factorial.Select\n");

  version_details();

  if (argc < 3) {
    fprintf(stderr, "usage %s startN, endN", argv[0]);
    RC = EXIT_FAILURE;
  }
  else {
    uint64_t nbegin;
    uint64_t nend;
    nbegin = strtoul(argv[1], NULL, 0);
    nend = strtoul(argv[2], NULL, 0);

    factorial_u32(nbegin, nend);
    putchar('\n');
    factorial_s32(nbegin, nend);
    putchar('\n');
    factorial_u64(nbegin, nend);
    putchar('\n');
    factorial_s64(nbegin, nend);
    putchar('\n');
    factorial_u128(nbegin, nend);
    putchar('\n');
    factorial_s128(nbegin, nend);
    putchar('\n');
    factorial_gmp(nbegin, nend);
    putchar('\n');
    factorial_gfg(nbegin, nend);
    putchar('\n');
    factorial_u64_unrolled(nbegin, nend);
    putchar('\n');
    factorial_u64_tabular(nbegin, nend);
    putchar('\n');
    factorial_float(nbegin, nend);
    putchar('\n');
    factorial_double(nbegin, nend);
    putchar('\n');
    factorial_longdouble(nbegin, nend);
    putchar('\n');
  }

  return RC;
}

//  MARK: - Drivers -
//  MARK: <--> 32-bit drivers
/*
 *  MARK: factorial_u32()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_u32(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {32-bit values}:\n\n", nbegin, nend);
  printf("......>: %20" PRIu32 " <-- %s\n", UINT32_MAX, "UINT32_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_s32(nb);
  }

  return;
}

/*
 *  MARK: factorial_s32()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_s32(uint64_t nbegin, uint64_t nend) {
  
  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {32-bit values}:\n\n", nbegin, nend);
  printf("......>: %20" PRId32 " <-- %s\n", INT32_MAX, "INT32_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_u32(nb);
  }

  return;
}

//  MARK: <--> 64-bit drivers
/*
 *  MARK: factorial_u64()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_u64(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {64-bit values}:\n\n", nbegin, nend);
  printf("......>: %20" PRIu64 " <-- %s\n", UINT64_MAX, "UINT64_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_u64(nb);
  }

  return;
}

/*
 *  MARK: factorial_u64_unrolled()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_u64_unrolled(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {64-bit values}:\n\n", nbegin, nend);
  printf("......>: %20" PRIu64 " <-- %s\n", UINT64_MAX, "UINT64_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_u64_unrolled(nb);
  }

  return;
}

/*
 *  MARK: factorial_u64_tabular()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_u64_tabular(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {64-bit values}:\n\n", nbegin, nend);
  printf("......>: %20" PRIu64 " <-- %s\n", UINT64_MAX, "UINT64_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_u64_tabular(nb);
  }

  return;
}

/*
 *  MARK: factorial_s64()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_s64(uint64_t nbegin, uint64_t nend) {
  
  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {64-bit values}:\n\n", nbegin, nend);
  printf("......>: %20" PRId64 " <-- %s\n", INT64_MAX, "INT64_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_s64(nb);
  }

  return;
}

//  MARK: <--> 128-bit drivers
/*
 *  MARK: factorial_u128()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 *
 *      ----+----1----+----2----+----3----+---*4----+----5----+----6
 * 32!: 263130836933693530167218012160000000
 * 33!: 8683317618811886495518194401280000000
 * 34!: -45049567881334322615755997788248211456 *- overflow -*
 * 35!: 124676958757991025765413114570153656320 *- overflow -*
 * 36!: 64699745315476902531002227912544878592 *- overflow -*
 *
 */
void factorial_u128(uint64_t nbegin, uint64_t nend) {

  biggar bggr = {
    .ui64_a[0] = 0xffffffffffffffffLL,
    .ui64_a[1] = 0xffffffffffffffffLL,
  };
  size_t const pbuff_l = 41;
  char pbuff[pbuff_l] = {0, };
  uint128toa(bggr.ui128, pbuff, pbuff_l);
  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {64-bit values}:\n\n", nbegin, nend);
  printf("......>: %40" PRIu64 " <-- %s\n", UINT64_MAX, "UINT64_MAX");
  printf("......>: %40s <-- %s\n", pbuff, "Max unsigned 128-bit integer");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_u128(nb);
  }

  return;
}

/*
 *  MARK: factorial_s128()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 *
 *      ----+----1----+----2----+----3----+---*4----+----5----+----6
 * 33!: 8683317618811886495518194401280000000
 * 34!: 295232799039604140847618609643520000000
 * 35!: 124676958757991025765413114570153656320 *- overflow -*
 * 36!: 64699745315476902531002227912544878592 *- overflow -*
 *
 */
void factorial_s128(uint64_t nbegin, uint64_t nend) {
  
  
  biggar bggr_max = {
    .ui64_a[0] = 0xffffffffffffffffLL,
    .ui64_a[1] = 0x7fffffffffffffffLL,
  };
  biggar bggr_min = {
    .ui64_a[0] = 0x0000000000000000LL,
    .ui64_a[1] = 0x8000000000000000LL,
  };
  size_t const pbuff_l = 41;
  char pbuff_max[pbuff_l] = { 0, };
  char pbuff_min[pbuff_l] = { 0, };
  int128toa(bggr_max.ui128, pbuff_max, pbuff_l);
  int128toa(bggr_min.ui128, pbuff_min, pbuff_l);
  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {64-bit values}:\n\n", nbegin, nend);
  printf("......>: %40" PRId64 " <-- %s\n", INT64_MIN, "INT64_MIN");
  printf("......>: %40" PRId64 " <-- %s\n", INT64_MAX, "INT64_MAX");
  printf("......>: %40s <-- %s\n", pbuff_min, "Min signed 128-bit integer");
  printf("......>: %40s <-- %s\n", pbuff_max, "Max signed 128-bit integer");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_s128(nb);
  }

  return;
}

//  MARK: <--> BigNum (multiple precision) drivers
/*
 *  MARK: factorial_gmp()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_gmp(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {multiple precision arithmatic}:\n\n", nbegin, nend);
  printf("......>: %20" PRId32 " <-- %s\n", INT32_MAX, "INT32_MAX");
  printf("......>: %20" PRIu32 " <-- %s\n", UINT32_MAX, "UINT32_MAX");
  printf("......>: %20" PRId64 " <-- %s\n", INT64_MAX, "INT64_MAX");
  printf("......>: %20" PRIu64 " <-- %s\n", UINT64_MAX, "UINT64_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_gmp(nb);
  }

  return;
}

/*
 *  MARK: factorial_gfg()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_gfg(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {multiple precision arithmatic}:\n\n", nbegin, nend);
  printf("......>: %20" PRId32 " <-- %s\n", INT32_MAX, "INT32_MAX");
  printf("......>: %20" PRIu32 " <-- %s\n", UINT32_MAX, "UINT32_MAX");
  printf("......>: %20" PRId64 " <-- %s\n", INT64_MAX, "INT64_MAX");
  printf("......>: %20" PRIu64 " <-- %s\n", UINT64_MAX, "UINT64_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    gfg_factorial(nb);
  }

  return;
}

//  MARK: <--> floating point drivers
/*
 *  MARK: factorial_float()
 */
void factorial_float(uint64_t nbegin, uint64_t nend) {
  
  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {single precision floating point}:\n\n", nbegin, nend);
  printf("......>: %20" PRId32 " <-- %s\n", INT32_MAX, "INT32_MAX");
  printf("......>: %20" PRIu32 " <-- %s\n", UINT32_MAX, "UINT32_MAX");
  printf("......>: %20" PRId64 " <-- %s\n", INT64_MAX, "INT64_MAX");
  printf("......>: %20" PRIu64 " <-- %s\n", UINT64_MAX, "UINT64_MAX");
  printf("......>: %20.3f <-- %s\n", FLT_MAX, "FLT_MAX");
  printf("......>: %20.14e <-- %s\n", FLT_MAX, "FLT_MAX");
  printf("......>: %20.3lf <-- %s\n", DBL_MAX, "DBL_MAX");
  printf("......>: %20.13le <-- %s\n", DBL_MAX, "DBL_MAX");
  printf("......>: %20.3Lf <-- %s\n", LDBL_MAX, "LDBL_MAX");
  printf("......>: %20.12Le <-- %s\n", LDBL_MAX, "LDBL_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_float(nb);
  }

  return;
}

/*
 *  MARK: factorial_double()
 */
void factorial_double(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {double precision floating point}:\n\n", nbegin, nend);
  printf("......>: %20" PRId32 " <-- %s\n", INT32_MAX, "INT32_MAX");
  printf("......>: %20" PRIu32 " <-- %s\n", UINT32_MAX, "UINT32_MAX");
  printf("......>: %20" PRId64 " <-- %s\n", INT64_MAX, "INT64_MAX");
  printf("......>: %20" PRIu64 " <-- %s\n", UINT64_MAX, "UINT64_MAX");
  printf("......>: %20.3f <-- %s\n", FLT_MAX, "FLT_MAX");
  printf("......>: %20.14e <-- %s\n", FLT_MAX, "FLT_MAX");
  printf("......>: %20.3lf <-- %s\n", DBL_MAX, "DBL_MAX");
  printf("......>: %20.13le <-- %s\n", DBL_MAX, "DBL_MAX");
  printf("......>: %20.3Lf <-- %s\n", LDBL_MAX, "LDBL_MAX");
  printf("......>: %20.12Le <-- %s\n", LDBL_MAX, "LDBL_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_double(nb);
  }

  return;
}

/*
 *  MARK: factorial_longdouble()
 */
void factorial_longdouble(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {long double precision floating point}:\n\n", nbegin, nend);
  printf("......>: %20" PRId32 " <-- %s\n", INT32_MAX, "INT32_MAX");
  printf("......>: %20" PRIu32 " <-- %s\n", UINT32_MAX, "UINT32_MAX");
  printf("......>: %20" PRId64 " <-- %s\n", INT64_MAX, "INT64_MAX");
  printf("......>: %20" PRIu64 " <-- %s\n", UINT64_MAX, "UINT64_MAX");
  printf("......>: %20.3f <-- %s\n", FLT_MAX, "FLT_MAX");
  printf("......>: %20.14e <-- %s\n", FLT_MAX, "FLT_MAX");
  printf("......>: %20.3lf <-- %s\n", DBL_MAX, "DBL_MAX");
  printf("......>: %20.13le <-- %s\n", DBL_MAX, "DBL_MAX");
  printf("......>: %20.3Lf <-- %s\n", LDBL_MAX, "LDBL_MAX");
  printf("......>: %20.12Le <-- %s\n", LDBL_MAX, "LDBL_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_longdouble(nb);
  }

  return;
}

//  MARK: - Implementors -
//  MARK: <--> 32-bit implementations
/*
 *  MARK: fact_u32()
 *
 *  Calculate val! using unsigned 32-bit integers
 *  Arithmetic overflow is prevented via __builtin_umul_overflow()
 *  @see: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    catch any potential arithmentic overflow
 *    factorial = factorial * iterator
 *  print result
 */
void fact_u32(uint64_t val) {

  uint32_t fv = 1;
  bool overflow;
  bool overflowed;
  overflow = overflowed = false;;

  for (uint32_t i_ = 1; i_ <= val ; ++i_) {
    uint32_t intermediate;
    overflow = __builtin_umul_overflow(fv, i_, &intermediate);
    overflowed = overflowed ? overflowed : overflow;
    fv = intermediate;
    //fv = fv * i_;
  }

  printf("%6" PRIu64 "!: %20" PRIu32 " %s\n", val, fv, overflowed ? "*- overflow -*" : "");

  return;
}

/*
 *  MARK: fact_s32()
 *
 *  Calculate val! using signed 32-bit integers
 *  Arithmetic overflow is prevented via __builtin_smul_overflow()
 *  @see: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    catch any potential arithmentic overflow
 *    factorial = factorial * iterator
 *  print result
 */
void fact_s32(uint64_t val) {
  
  int32_t fv = 1;
  bool overflow;
  bool overflowed;
  overflow = overflowed = false;;

  for (int32_t i_ = 1; i_ <= val ; ++i_) {
    int32_t intermediate;
    overflow = __builtin_smul_overflow(fv, i_, &intermediate);
    overflowed = overflowed ? overflowed : overflow;
    fv = intermediate;
    //fv = fv * i_;
  }

  printf("%6" PRIu64 "!: %20" PRId32 " %s\n", val, fv, overflowed ? "*- overflow -*" : "");

  return;
}

//  MARK: <--> 64-bit implementations
/*
 *  MARK: fact_u64()
 *
 *  Calculate val! using unsigned 64-bit integers
 *  Arithmetic overflow is prevented via __builtin_umulll_overflow()
 *  @see: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    catch any potential arithmentic overflow
 *    factorial = factorial * iterator
 *  print result
 */
void fact_u64(uint64_t val) {

  uint64_t fv = 1;
  bool overflow;
  bool overflowed;
  overflow = overflowed = false;;

  for (uint64_t i_ = 1; i_ <= val ; ++i_) {
    uint64_t intermediate;
    overflow = __builtin_umulll_overflow(fv, i_, &intermediate);
    overflowed = overflowed ? overflowed : overflow;
    fv = intermediate;
    // fv = fv * i_;
  }

  printf("%6" PRIu64 "!: %20" PRIu64 " %s\n", val, fv, overflowed ? "*- overflow -*" : "");

  return;
}

/*
 *  MARK: fact_u64_unrolled()
 *
 *  Calculate val! using unsigned 64-bit integers.
 *  Observing that the largest factorial that can be stored in a 64-bit integer is 20!
 *  and a 32-bit integer is 12! the loop unrolled and replaced by a switch statement.
 */
void fact_u64_unrolled(uint64_t val) {

  uint64_t fv = 1;
  bool overflowed;
  overflowed = false;;

  uint64_t ix = 1;
  switch (val) {
    case 20:  //  TODO: max factorial for 64-bit integers
      fv = fv * ++ix;
    case 19:
      fv = fv * ++ix;
    case 18:
      fv = fv * ++ix;
    case 17:
      fv = fv * ++ix;
    case 16:
      fv = fv * ++ix;
    case 15:
      fv = fv * ++ix;
    case 14:
      fv = fv * ++ix;
    case 13:
      fv = fv * ++ix;
    case 12:  //  TODO: max factorial for 32-bit integers
      fv = fv * ++ix;
    case 11:
      fv = fv * ++ix;
    case 10:
      fv = fv * ++ix;
    case  9:
      fv = fv * ++ix;
    case  8:
      fv = fv * ++ix;
    case  7:
      fv = fv * ++ix;
    case  6:
      fv = fv * ++ix;
    case  5:
      fv = fv * ++ix;
    case  4:
      fv = fv * ++ix;
    case  3:
      fv = fv * ++ix;
    case  2:
      fv = fv * ++ix;
      break;

    case  1:
      fv = 1;
      break;

    default:
      fv = 0;
      overflowed = true;
      break;
  }

  printf("%6" PRIu64 "!: %20" PRIu64 " %s\n", val, fv, overflowed ? "*- overflow -*" : "");

  return;
}

/*
 *  MARK: fact_u64_tabular()
 *
 *  Function to calculate factorials using a lookup table.
 *
 *  Uses the realization that the maximum factorial that can be stored in a
 *  64-bit unsigned integer is 20! Thus all factorials from 1! to 20! can
 *  be maintained in a 20 element array.
 */
void fact_u64_tabular(uint64_t val) {

  static
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
  uint64_t fv = 0;
  bool overflow;
  bool * oflow = & overflow;

  if (val > 0 && val < factorials_c) {
    fv = factorials[val];
    *oflow = false;
  }
  else {
    fv = 0;
    *oflow = true;
  }
  
  printf("%6" PRIu64 "!: %20" PRIu64 " %s\n", val, fv, overflow ? "*- overflow -*" : "");

  return;
}

/*
 *  MARK: fact_s64()
 *
 *  Calculate val! using signed 64-bit integers.
 *  Arithmetic overflow is prevented via __builtin_smulll_overflow()
 *  @see: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    catch any potential arithmentic overflow
 *    factorial = factorial * iterator
 *  print result
 */
void fact_s64(uint64_t val) {
  
  int64_t fv = 1;
  bool overflow;
  bool overflowed;
  overflow = overflowed = false;;

  for (int64_t i_ = 1; i_ <= val ; ++i_) {
    int64_t intermediate;
    overflow = __builtin_smulll_overflow(fv, i_, &intermediate);
    overflowed = overflowed ? overflowed : overflow;
    fv = intermediate;
    // fv = fv * i_;
  }

  printf("%6" PRIu64 "!: %20" PRId64 " %s\n", val, fv, overflowed ? "*- overflow -*" : "");

  return;
}

//  MARK: <--> 128-bit implementations
/*
 *  MARK: fact_u128()
 *
 *  Calculate val! using unsigned 128-bit integers
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    catch any potential arithmentic overflow
 *    factorial = factorial * iterator
 *  print result
 */
void fact_u128(uint64_t val) {

  static size_t const nrstr_l = 41;
  static size_t pwidth_max = 0;

  uint128_t fv;
  bool overflow;
  bool overflowed;

  fv = 1;
  overflowed = false;;

  for (uint64_t i_ = 1; i_ <= val ; ++i_) {
    uint128_t intermediate;
    overflow = umulj_overflow(fv, i_, &intermediate);
    overflowed = overflowed ? overflowed : overflow;
    fv = intermediate;
  }

  char * nrstr;

  nrstr = malloc(nrstr_l);
  nrstr = uint128toa(fv, nrstr, nrstr_l);
  printf_fact128str(val, &nrstr, overflowed, &pwidth_max);
  free(nrstr);

  return;
}

/*
 *  MARK: fact_s128()
 *
 *  Calculate val! using signed 128-bit integers.
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    catch any potential arithmentic overflow
 *    factorial = factorial * iterator
 *  print result
 */
void fact_s128(uint64_t val) {
  
  static size_t const nrstr_l = 41;
  static size_t pwidth_max = 0;

  int128_t fv;
  bool overflow;
  bool overflowed;

  fv = 1;
  overflowed = false;;

  for (int64_t i_ = 1; i_ <= val ; ++i_) {
    int128_t intermediate;
    overflow = smulj_overflow(fv, i_, &intermediate);
    overflowed = overflowed ? overflowed : overflow;
    fv = intermediate;
  }

  char * nrstr;

  nrstr = malloc(nrstr_l);
  nrstr = int128toa(fv, nrstr, nrstr_l);
  printf_fact128str(val, &nrstr, overflowed, &pwidth_max);
  free(nrstr);

  return;
}

//  MARK: <--> BigNum (multiple precision) implementations
/*
 *  MARK: fact_gmp()
 *
 *  Calculate val! using GNU Multiple Precision Aritmetic Library (GMP)
 *  @see: https://gmplib.org/manual/index.html#Top
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    factorial = factorial * iterator
 *  print result
 */
void fact_gmp(uint64_t val) {

  mpz_t pf;

  mpz_init_set_ui(pf, 1);
  for (size_t i_ = 1; i_ <= val; ++i_) {
    mpz_mul_ui(pf, pf, i_);
  }

  gmp_printf("%6" PRIu64 "!: %20Zd\n", val, pf);
  mpz_clear(pf);

  return;
}

//  MARK: <--> floating point implementations
/*
 *  MARK: fact_float()
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    factorial = factorial * iterator
 *  print result
 */
void fact_float(uint64_t val) {

  float fv = 1;

  for (uint64_t i_ = 1; i_ <= val ; ++i_) {
    fv = fv * i_;
  }

  printf("%6" PRIu64 "!: %20.0f\n", val, fv);

  return;
}

/*
 *  MARK: fact_double()
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    factorial = factorial * iterator
 *  print result
 */
void fact_double(uint64_t val) {

  double fv = 1;

  for (uint64_t i_ = 1; i_ <= val ; ++i_) {
    fv = fv * i_;
  }

  printf("%6" PRIu64 "!: %20.0lf\n", val, fv);

  return;
}

/*
 *  MARK: fact_longdouble()
 *
 *  Uses an iterative method to calculate the factorial of the argument.
 *  assign factorial the value 1
 *  loop with iterator from 1 to argument
 *    factorial = factorial * iterator
 *  print result
 */
void fact_longdouble(uint64_t val) {

  long double fv = 1;

  for (uint64_t i_ = 1; i_ <= val ; ++i_) {
    fv = fv * i_;
  }

  printf("%6" PRIu64 "!: %20.0Lf\n", val, fv);

  return;
}

//  MARK: - Utilities and Helper Functions -
/*
 *  MARK: umulj_overflow()
 *
 *  Check overflow multiplication for unsigned 128-bit integers
 *
 *  Basic algorithm:
 *  get product as multiplication of multiplicand with multiplier
 *  get quotient as division of product with multiplicand
 *  compare quotient to multiplier - if not equal, overflow occured!
 *  return outcome of comparison
 */
bool umulj_overflow(uint128_t multiplicand, uint128_t multiplier, uint128_t * product) {

  /*
   *  TODO: Formal terms used in equations:
   *  addition:       augend        + addend      = sum
   *  subtraction:    subtrahend    - minuend     = differnce
   *  multiplication: multiplicand  x multiplier  = product
   *  division:       dividend      ÷ divisor     = quotient
   */
  bool overflow;
  if (product != NULL) {
    uint128_t _product;  // TODO: debugging
    uint128_t quotient;
    *product = _product = multiplicand * multiplier;
    quotient = _product / multiplicand;
    overflow = (multiplicand != 0 && quotient != multiplier) ? true : false;
  }
  else {
    //  TODO: better reporting of NULL pointer
    overflow = true;
  }

  return overflow;
}

/*
 *  MARK: smulj_overflow()
 *
 *  Check overflow multiplication for signed 128-bit integers
 *
 *  Basic algorithm:
 *  get product as multiplication of multiplicand with multiplier
 *  get quotient as division of product with multiplicand
 *  compare quotient to multiplier - if not equal, overflow occured!
 *  return outcome of comparison
 */
bool smulj_overflow(int128_t  multiplicand, int128_t  multiplier, int128_t * product) {

  /*
   *  TODO: Formal terms used in equations:
   *  addition:       augend        + addend      = sum
   *  subtraction:    subtrahend    - minuend     = differnce
   *  multiplication: multiplicand  x multiplier  = product
   *  division:       dividend      ÷ divisor     = quotient
   */
  bool overflow;
  if (product != NULL) {
    int128_t _product;   // TODO: debugging
    int128_t quotient;
    *product = _product = multiplicand * multiplier;
    quotient = _product / multiplicand;
    overflow = (multiplicand != 0 && quotient != multiplier) ? true : false;
  }
  else {
    //  TODO: better reporting of NULL pointer
    overflow = true;
  }

  return overflow;
}

/*
 *  MARK: uint128toa()
 *
 *  String formatter for unsigned 128-bit integers
 *
 *  Basic algorithm:
 *  Check output buffer is not NULL - done
 *  Check for special case "zero": set output buffer to "0" - done
 *  loop:
 *    get modulo of number / 10
 *    get character representation of modulo
 *    store character representation in output buffer (fill from the right)
 *    iterate
 *  return output buffer
 */
char * uint128toa(uint128_t big, char * buffp, size_t const buff_len) {

  char const * const numbers = "0123456789";
  if (buffp != NULL) {
    biggar bgr = { 0, };

    bgr.ui128 = big;

    if (big == 0) {
      buffp[0] = numbers[0];
      buffp[1] = '\0';
    }
    else {
      char * str = malloc(buff_len * sizeof(char));
      memset(str, 0, buff_len);
      char * next = str + buff_len - 1; // start at right most char.
      while (big != 0) {
        *--next = numbers[big % 10];  // save last digit
        big /= 10;                    // remove last digit
      }
      strncpy(buffp, next, buff_len);
      free(str);
    }
  }

  return buffp;
}

/*
 *  MARK: int128toa()
 *
 *  String formatter for signed 128-bit integers
 *
 *  Basic algorithm:
 *  Check output buffer is not NULL - done
 *  Check for special case "zero": set output buffer to "0" - done
 *  convert number to +ve
 *  loop:
 *    get modulo of number / 10
 *    get character representation of modulo
 *    store character representation in output buffer (fill from the right)
 *    iterate
 *  if number was -ve, insert a sign in buffer
 *  return output buffer
 */
char * int128toa(int128_t big, char * buffp, size_t const buff_len) {

  char const * const numbers = "0123456789";
  if (buffp != NULL) {
    biggar bgr = { 0, };

    bgr.si128 = big;

    if (big == 0) {
      buffp[0] = numbers[0];
      buffp[1] = '\0';
    }
    else {
      char * str = malloc(buff_len * sizeof(char));
      memset(str, 0, buff_len);
      char * next = str + buff_len - 1; // start at right most char.
      bgr.ui128 = big >= 0 ? big : ~big + 1;
      while (bgr.ui128 != 0) {
        *--next = numbers[bgr.ui128 % 10]; // save last digit
        bgr.ui128 /= 10;                   // remove last digit
      }
      if (big < 0) {
        *--next = '-';
      }
      strncpy(buffp, next, buff_len);
      free(str);
    }
  }

  return buffp;
}

/*
 *  MARK: printf_fact128str()
 */
int printf_fact128str(uint64_t val, char ** pnrstr, bool overflowed, size_t * ppw_max) {

  static size_t const nrstr_l = 41;

  int pc;
  char * nrstr;
  size_t pwidth_max;
  size_t pwidth_next;

  nrstr = *pnrstr;
  pwidth_max = *ppw_max;
  pwidth_next = strlen(nrstr);

  if (pwidth_next < pwidth_max) {
    char * strwork;
    char * here;

    strwork = calloc(nrstr_l, sizeof(char));
    here = strwork;
    for (size_t n_ = 0; n_ < pwidth_max - pwidth_next; ++n_) {
      *here++ = ' ';
    }
    strcpy(here, nrstr);
    free(nrstr);

    *pnrstr = nrstr = strwork;
  }
  *ppw_max = strlen(nrstr);
  pc = printf("%6" PRIu64 "!: %20s %s\n",
              val, nrstr, overflowed ? "*- overflow -*" : "");

  return pc;
}
