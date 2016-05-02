// Testing the limits of different types of variables 
// http://www.tutorialspoint.com/c_standard_library/limits_h.htm 
// https://en.wikipedia.org/wiki/C_data_types

// CS 265 Project 
// 05/01/2016

#include <stdio.h>
#include <limits.h>

int main() {

   printf("The number of bits in a byte %d\n", CHAR_BIT);

   printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
   printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
   printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

   printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
   printf("The maximum value of SHORT INT = %d\n", SHRT_MAX); 

   printf("The minimum value of INT = %d\n", INT_MIN);
   printf("The maximum value of INT = %d\n", INT_MAX);

   printf("The minimum value of CHAR = %d\n", CHAR_MIN);
   printf("The maximum value of CHAR = %d\n", CHAR_MAX);

   printf("The minimum value of LONG = %ld\n", LONG_MIN);
   printf("The maximum value of LONG = %ld\n", LONG_MAX);
  
   int test_integer;
   long test_long;

   // Assigning a huge value to an integer
   // test_integer = 12312341234;
   test_integer = 123;
   printf("A huge integer! %d \n", test_integer);

   // Assigning a huge value to a long
   printf("A huge long integer! %ld \n", test_long = 12312341234);   

   return(0);
}