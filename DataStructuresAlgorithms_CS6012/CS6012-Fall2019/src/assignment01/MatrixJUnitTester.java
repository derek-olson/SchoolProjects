/*
 * Here is a starting point for your Matrix tester. You will have to fill in the rest with
 * more code to sufficiently test your Matrix class. We will be using our own MatrixTester for grading. 
*/
package assignment01;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class MatrixJUnitTester {

  Matrix threeByTwo, twoByThree, twoByTwoResult, twoByTwoSimple, twoByTwoNegative,twoByTwoPlusResult,
  threeByTwoUnbalanced, twoByThreeUnbalanced, unbalancedResult;
  /* Initialize some matrices we can play with for every test! */

  @Before
  public void setup() {
    threeByTwo = new Matrix(new int[][] { { 1, 2, 3 }, { 2, 5, 6 } });
    twoByThree = new Matrix(new int[][] { { 4, 5 }, { 3, 2 }, { 1, 1 } });
    // this is the known correct result of multiplying M1 by M2
    twoByTwoResult = new Matrix(new int[][] { { 13, 12 }, { 29, 26 } });
    
    twoByTwoSimple = new Matrix(new int[][] { { 1, 1 }, { 1, 1 } });
    twoByTwoNegative = new Matrix(new int[][] { { -1, -1 }, { -1, -1 } });
    twoByTwoPlusResult = new Matrix(new int[][] { { 0, 0 }, { 0, 0 } });
    
    twoByThreeUnbalanced = new Matrix(new int[][] { { 1, 2, 3 }, { 4, 5, 6} });
    threeByTwoUnbalanced = new Matrix(new int[][] { { 7, 8 }, { 9, 10 }, { 11, 12 } });
    unbalancedResult = new Matrix(new int[][] { { 58, 64 }, { 139, 154 } });
  }

  @Test
  public void timesWithBalancedDimensions() {
    Matrix matrixProduct = threeByTwo.times(twoByThree);
    Assert.assertTrue(twoByTwoResult.equals(matrixProduct));
  }

  @Test
  public void timesWithUnbalancedDimensions() {
	    Matrix matrixProduct = twoByThreeUnbalanced.times(threeByTwoUnbalanced);
	    Assert.assertTrue(unbalancedResult.equals(matrixProduct));
  }
  
  @Test
  public void timesWithInvalidDimensions() {
	    Matrix matrixProduct = twoByThree.times(twoByThree);
	    Assert.assertEquals(matrixProduct, null);
  }
  
  @Test
  public void plusWithInvalidDimensions() {
	    Matrix matrixProduct = threeByTwo.plus(twoByTwoResult);
	    Assert.assertEquals(matrixProduct, null);
  }
  
  @Test
  public void plusWithValidDimensions() {
	    Matrix matrixResult = twoByTwoSimple.plus(twoByTwoNegative);
	    Assert.assertTrue(twoByTwoPlusResult.equals(matrixResult));
  }

  @Test
  public void twoByTwoToString() {
    String resultString = "13 12 \n29 26 \n";
    Assert.assertEquals(resultString, twoByTwoResult.toString());
  }
}
