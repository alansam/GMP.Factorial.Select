//
//  factorial_select.c
//  GMP.Factorial.Select
//
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
#include <gmp.h>

#include "gfg-factorial.hpp"

static
inline
void version_details(void);
#include "version_info.h"

void factorial_u32(uint64_t nbegin, uint64_t nend);
void factorial_s32(uint64_t nbegin, uint64_t nend);
void factorial_u64(uint64_t nbegin, uint64_t nend);
void factorial_s64(uint64_t nbegin, uint64_t nend);
void factorial_gmp(uint64_t nbegin, uint64_t nend);
void factorial_gfg(uint64_t nbegin, uint64_t nend);
void factorial_u64_unrolled(uint64_t nbegin, uint64_t nend);
void factorial_u64_tabular(uint64_t nbegin, uint64_t nend);
void fact_u32(uint64_t val);
void fact_s32(uint64_t val);
void fact_u64(uint64_t val);
void fact_s64(uint64_t val);
void fact_gmp(uint64_t val);
void fact_u64_unrolled(uint64_t val);
void fact_u64_tabular(uint64_t val);

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
    factorial_gmp(nbegin, nend);
    putchar('\n');
    factorial_gfg(nbegin, nend);
    putchar('\n');
    factorial_u64_unrolled(nbegin, nend);
    putchar('\n');
    factorial_u64_tabular(nbegin, nend);
    putchar('\n');
  }

  return RC;
}

/*
 *  MARK: factorial_u32()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_u32(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {32-bit values}:\n\n", nbegin, nend);
  printf("......>: %20" PRIu32 " <-- %s\n", __UINT32_MAX__, "UINT32_MAX");
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
  printf("......>: %20" PRId32 " <-- %s\n", __INT32_MAX__, "INT32_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_u32(nb);
  }

  return;
}

/*
 *  MARK: factorial_u64()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_u64(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {64-bit values}:\n\n", nbegin, nend);
  printf("......>: %20" PRIu64 " <-- %s\n", __UINT64_MAX__, "UINT64_MAX");
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
  printf("......>: %20" PRIu64 " <-- %s\n", __UINT64_MAX__, "UINT64_MAX");
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
  printf("......>: %20" PRIu64 " <-- %s\n", __UINT64_MAX__, "UINT64_MAX");
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
  printf("......>: %20" PRId64 " <-- %s\n", __INT64_MAX__, "INT64_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_s64(nb);
  }

  return;
}

/*
 *  MARK: factorial_gmp()
 *
 *  Display table of factorials within ranges "nbegin" and "nend"
 */
void factorial_gmp(uint64_t nbegin, uint64_t nend) {

  printf("Function: %s\n", __func__);
  printf("Factorials from %" PRIu64 " to %" PRIu64 " {multiple precision arithmatic}:\n\n", nbegin, nend);
  printf("......>: %20" PRId32 " <-- %s\n", __INT32_MAX__, "INT32_MAX");
  printf("......>: %20" PRIu32 " <-- %s\n", __UINT32_MAX__, "UINT32_MAX");
  printf("......>: %20" PRId64 " <-- %s\n", __INT64_MAX__, "INT64_MAX");
  printf("......>: %20" PRIu64 " <-- %s\n", __UINT64_MAX__, "UINT64_MAX");
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
  printf("......>: %20" PRId32 " <-- %s\n", __INT32_MAX__, "INT32_MAX");
  printf("......>: %20" PRIu32 " <-- %s\n", __UINT32_MAX__, "UINT32_MAX");
  printf("......>: %20" PRId64 " <-- %s\n", __INT64_MAX__, "INT64_MAX");
  printf("......>: %20" PRIu64 " <-- %s\n", __UINT64_MAX__, "UINT64_MAX");
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    gfg_factorial(nb);
  }

  return;
}

/*
 *  MARK: fact_u32()
 *
 *  Calculate val! using unsigned 32-bit integers
 *  Arithmetic overflow is prevented via __builtin_umul_overflow()
 *  @see: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
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

/*
 *  MARK: fact_u64()
 *
 *  Calculate val! using unsigned 64-bit integers
 *  Arithmetic overflow is prevented via __builtin_umulll_overflow()
 *  @see: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
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

/*
 *  MARK: fact_gmp()
 *
 *  Calculate val! using GNU Multiple Precision Aritmetic Library (GMP)
 *  @see: https://gmplib.org/manual/index.html#Top
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
