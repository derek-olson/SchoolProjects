/*
 * This is the source code used to compile "factorial.s".
 * This won't compile as a standalone program, since there is no main(),
 * but this should help you understand the factorial assembly.
 * The assembly program prompts for the input (i)
 */

int Factorial(int i)
{
  int f = 1;
  while(i > 1)
  {
    f *= i;
    i--;
  }
  return f;
}
