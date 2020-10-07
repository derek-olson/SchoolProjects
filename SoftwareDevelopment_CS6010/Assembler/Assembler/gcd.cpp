/*
 * This is the source code used to compile "gcd.s".
 * This won't compile as a standalone program, since there is no main(),
 * but this should help you understand the gcd assembly.
 * This is Euclid's original algorithm for computing the greatest common divisor
 * of two positive integers.
 * The assembly program prompts for two inputs: (a) and (b).
 */

int GCD(int a, int b)
{
  while(a != b)
  {
    if(a > b)
      a = a - b;
    else
      b = b - a;
  }
  return a;
}
