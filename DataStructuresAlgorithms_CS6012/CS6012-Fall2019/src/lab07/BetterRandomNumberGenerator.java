package lab07;

public class BetterRandomNumberGenerator implements RandomNumberGenerator {
	   private static int A = 25173;
	   private static int C = 13849;
	   //private static int M = 65536;
	   private static int L = (int) System.nanoTime();

	/**
	   * This function returns a random integer between [0,max)
	   * 
	   * @param max
	   *          the upper bound for the range of the random number, non-inclusive.
	   * @return an integer between [0, max).
	   */
	  public int nextInt(int max) {
	      L=(A*L+C)%max;
	        return L;
	  }

	  /**
	   * This function sets a seed for the random number generator. A random number
	   * generator should return the same sequence of numbers for the same seed.
	   * 
	   * @param seed
	   *          the seed parameter used to initialize the random number generator.
	   */
	  @SuppressWarnings("static-access")
	public void setSeed(long seed) {
		  this.L = (int)seed;
	  }

	  /**
	   * This function sets the two constants for use with the random generator (see
	   * your textbook for more information). If your generator does not use such
	   * constants then you are free to ignore the input from this function.
	   */
	  @SuppressWarnings("static-access")
	public void setConstants(long const1, long const2) {
		  this.C= (int) const1;
		  this.A = (int) const2;
	  }



}
