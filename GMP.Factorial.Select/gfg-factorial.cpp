//
//  @see: https://www.geeksforgeeks.org/factorial-large-number/
//  @author: Harshit Agrawal
//
//  gfg-factorial.cpp
//  GMP.Factorial.Select
//
//  Created by Alan Sampson on 2/1/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

/*
 *
 * How to compute factorial of 100 using a C/C++ program?
 * Factorial of 100 has 158 digits. It is not possible to store these many digits
 * even if we use long long int.
 *
 * Examples :
 *
 * Input : 100
 * Output : 933262154439441526816992388562667004-
 *          907159682643816214685929638952175999-
 *          932299156089414639761565182862536979-
 *          208272237582511852109168640000000000-
 *          00000000000000
 *
 * Input :50
 * Output : 3041409320171337804361260816606476884-
 *          4377641568960512000000000000
 * Following is a simple solution where we use an array to store individual digits
 * of the result. The idea is to use basic mathematics for multiplication.
 *
 * The following is detailed algorithm for finding factorial.
 *
 * factorial(n)
 * 1) Create an array ‘res[]’ of MAX size where MAX is number of maximum digits in output.
 * 2) Initialize value stored in ‘res[]’ as 1 and initialize ‘res_size’ (size of ‘res[]’)
 *    as 1.
 * 3) Do following for all numbers from x = 2 to n.
 * ……a) Multiply x with res[] and update res[] and res_size to store the multiplication
 *      result.
 *
 * How to multiply a number ‘x’ with the number stored in res[]?
 * The idea is to use simple school mathematics. We one by one multiply x with every
 * digit of res[]. The important point to note here is digits are multiplied from
 * rightmost digit to leftmost digit. If we store digits in same order in res[], then
 * it becomes difficult to update res[] without extra space. That is why res[] is
 * maintained in reverse way, i.e., digits from right to left are stored.
 *
 * multiply(res[], x)
 * 1) Initialize carry as 0.
 * 2) Do following for i = 0 to res_size – 1
 * ….a) Find value of res[i] * x + carry. Let this value be prod.
 * ….b) Update res[i] by storing last digit of prod in it.
 * ….c) Update carry by storing remaining digits in carry.
 * 3) Put all digits of carry in res[] and increase res_size by number of digits in carry.
 *
 * Example to show working of multiply(res[], x)
 * A number 5189 is stored in res[] as following.
 * res[] = {9, 8, 1, 5}
 * x = 10
 *
 * Initialize carry = 0;
 *
 * i = 0, prod = res[0]*x + carry = 9*10 + 0 = 90.
 * res[0] = 0, carry = 9
 *
 * i = 1, prod = res[1]*x + carry = 8*10 + 9 = 89
 * res[1] = 9, carry = 8
 *
 * i = 2, prod = res[2]*x + carry = 1*10 + 8 = 18
 * res[2] = 8, carry = 1
 *
 * i = 3, prod = res[3]*x + carry = 5*10 + 1 = 51
 * res[3] = 1, carry = 5
 *
 * res[4] = carry = 5
 *
 * res[] = {0, 9, 8, 1, 5}
 *
 * Below is the implementation of above algorithm.
 *
 * Output :
 * Factorial of given number is
 * 9332621544394415268169923885626670049071596826438162146859296389
 * 5217599993229915608941463976156518286253697920827223758251185210
 * 916864000000000000000000000000
 *
 * The above approach can be optimized in many ways. We will soon be discussing optimized
 * solution for same.
 */

#include "gfg-factorial.hpp"

// C++ program to compute factorial of big numbers

#ifdef __cplusplus
extern "C" {
#endif

// Maximum number of digits in output
#ifdef NEED_MAX
#define MAX NEED_MAX
#else
#define MAX 5000
#endif

// This function finds factorial of large numbers
// and prints them
void gfg_factorial(uint64_t n_fact) {
  uint8_t res[MAX] = { 0, };

  // Initialize result
  res[0] = 1;
  size_t res_size = 1;

  // Apply simple factorial formula n! = 1 * 2 * 3 * 4...*n
  for (uint64_t x_ = 2; x_ <= n_fact; x_++) {
    res_size = gfg_multiply(x_, res, res_size);
  }

//  std::cout << "Factorial of given number is ";
//  std::cout << n_fact << "! is: ";
  std::string factorial;
  for (size_t i_ = res_size; i_ > 0; i_--) {
//    std::cout << res[i_ - 1];
    std::string intermediate = std::to_string(res[i_ - 1]);
    factorial.append(intermediate);
  }
  std::cout << std::setw(6) << n_fact << "! " << std::setw(20) << factorial << std::endl;
//  std::cout << std::endl;

  return;
}

// This function multiplies x with the number represented by res[].
// res_size is size of res[] or number of digits in the number represented by res[].
// This function uses simple school mathematics for multiplication.
// This function may value of res_size and returns the new value of res_size
size_t gfg_multiply(uint64_t x_multiplicand, uint8_t res[], size_t res_size) {
  uint8_t carry = 0; // Initialize carry

  // One by one multiply n with individual digits of res[]
  for (size_t i_ = 0; i_ < res_size; i_++) {
    uint64_t prod = res[i_] * x_multiplicand + carry;

    // Store last digit of 'prod' in res[]
    res[i_] = prod % 10;

    // Put rest in carry
    carry = prod / 10;
  }

  // Put carry in res and increase result size
  while (carry) {
    res[res_size] = carry % 10;
    carry = carry / 10;
    res_size++;
  }

  return res_size;
}

#ifdef __cplusplus
}
#endif

#ifdef NEED_MAIN
// Driver program
int main()
{
  gfg_factorial(100);
  return 0;
}
#endif
