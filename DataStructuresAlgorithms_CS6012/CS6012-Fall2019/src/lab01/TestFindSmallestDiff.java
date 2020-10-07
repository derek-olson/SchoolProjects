package lab01;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class TestFindSmallestDiff {

	@BeforeEach
	void setUp() throws Exception {
		  arr1 = new int[0];
		  arr2 = new int[] { 3, 3, 3 };
		  arr3 = new int[] { 52, 4, -8, 0, -17 };
		  arr4 = new int[] { -1, -2, -3, -4, -5};
	}

	@AfterEach
	void tearDown() throws Exception {
	}

//	@Test
//	void test() {
//		fail("Not yet implemented");
//	}
	
	private int[] arr1, arr2, arr3, arr4;
	@Test
	public void emptyArray() {
		  assertEquals(-1, DiffUtil.findSmallestDiff(arr1));
		}
	@Test
	public void allArrayElementsEqual() {
	  assertEquals(0, DiffUtil.findSmallestDiff(arr2));
	}
	@Test
	public void smallRandomArrayElements() {
	  assertEquals(4, DiffUtil.findSmallestDiff(arr3));
	}
	@Test
	public void negativesSameDifferenceArray() {
		assertEquals(1, DiffUtil.findSmallestDiff(arr4));
	}

}
