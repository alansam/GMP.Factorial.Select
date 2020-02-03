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
void factorial_u64(uint64_t nbegin, uint64_t nend);
void factorial_gmp(uint64_t nbegin, uint64_t nend);
void factorial_gfg(uint64_t nbegin, uint64_t nend);
void fact_u32(uint64_t val);
void fact_u64(uint64_t val);
void fact_gmp(uint64_t val);

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
    puts("");
    factorial_u64(nbegin, nend);
    puts("");
    factorial_gmp(nbegin, nend);
    puts("");
    factorial_gfg(nbegin, nend);
  }

  return RC;
}

/*
 *  MARK: factorial_u32()
 */
void factorial_u32(uint64_t nbegin, uint64_t nend) {

  printf("Factorials from %" PRIu64 " to %" PRIu64 " {32-bit values}:\n\n", nbegin, nend);
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_u32(nb);
  }

  return;
}

/*
 *  MARK: factorial_u64()
 */
void factorial_u64(uint64_t nbegin, uint64_t nend) {

  printf("Factorials from %" PRIu64 " to %" PRIu64 " {64-bit values}:\n\n", nbegin, nend);
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_u64(nb);
  }

  return;
}

/*
 *  MARK: factorial_gmp()
 */
void factorial_gmp(uint64_t nbegin, uint64_t nend) {

  printf("Factorials from %" PRIu64 " to %" PRIu64 " {multiple precision aritmatic}:\n\n", nbegin, nend);
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    fact_gmp(nb);
  }

  return;
}

void factorial_gfg(uint64_t nbegin, uint64_t nend) {

  printf("Factorials from %" PRIu64 " to %" PRIu64 " {multiple precision aritmatic}:\n\n", nbegin, nend);
  for (uint64_t nb = nbegin; nb <= nend; ++nb) {
    gfg_factorial(nb);
  }

  return;
}
/*
 *  MARK: fact_u32()
 */
void fact_u32(uint64_t val) {

  uint32_t fv = 1;
  bool overflow;
  bool overflowed;
  overflow = overflowed = false;;

  for (uint32_t i_ = 1; i_ <= val ; ++i_) {
    uint32_t intermediate;
    overflow = __builtin_mul_overflow(fv, i_, &intermediate);
    overflowed = overflowed ? overflowed : overflow;
    fv = intermediate;
    //fv = fv * i_;
  }

  printf("%6" PRIu64 "!: %20" PRIu32 " %s\n", val, fv, overflowed ? "*- overflow -*" : "");

  return;
}

/*
 *  MARK: fact_u64()
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
 *  MARK: fact_gmp()
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

