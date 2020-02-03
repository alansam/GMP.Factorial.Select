//
//  gfg-factorial.hpp
//  GMP.Factorial.Select
//
//  Created by Alan Sampson on 2/1/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#pragma once
#ifndef gfg_factorial_hpp
#define gfg_factorial_hpp

#ifdef __cplusplus
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <cinttypes>
#else
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

size_t gfg_multiply(uint64_t x_multiplicand, uint8_t res[], size_t res_size);
void gfg_factorial(uint64_t n_fact);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* gfg_factorial_hpp */
