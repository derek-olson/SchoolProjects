package lab05;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;

import org.junit.Assert;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class lab05_junit {
	
	@SuppressWarnings("rawtypes")
	BinarySearchSet bSS = new BinarySearchSet();

	@SuppressWarnings("unchecked")
	@BeforeEach
	void setUp() throws Exception {
		for (int i = 0; i < 1000; i++) {
			bSS.add(i);
		}
	}
	
	  @Test
	  public void testFirst() {
		
	    int first = (int) bSS.first();
	    int testFirst = 0;
	    Assert.assertEquals(first, testFirst);
	  }
	  
	  @Test
	  public void testLast() {
	    int last = (int) bSS.last();
	    int testLast = 999;
	    Assert.assertEquals(last, testLast);
	  }
	  
	  @Test
	  public void testBinarySearch() {
	    int target = bSS.binarySearch(8, 0, 999);
	    int testTarget = 8;
	    Assert.assertEquals(target, testTarget);
	  }
//	  
//	  @Test
	  public void testBinarySearchBool() {
	    boolean target = bSS.binarySearchBool(8, 0, 999);
	    boolean testTarget = true;
	    Assert.assertEquals(target, testTarget);
	  }
	  
	  @SuppressWarnings("unchecked")
	@Test
	  public void testAdd() {
	    int toAdd = 1000;
	    bSS.add(toAdd);
	    int last = (int) bSS.last();
	    Assert.assertEquals(last, toAdd);
	  }
	  
	  @SuppressWarnings("unchecked")
	@Test
	  public void testAddAll() {
	    ArrayList<Integer> toAdd = new ArrayList<>();
	    toAdd.add(1001);
	    toAdd.add(1002);
	    bSS.addAll(toAdd);
	    int last = (int) bSS.last();
	    Assert.assertEquals(last, 1002);
	  }
	  
	  @Test
	  public void testClear() {
		bSS.clear();
		int items = bSS.numberOfItemsInSet;
	    Assert.assertEquals(items, 0);
	  }
	  
	  @Test
	  public void testContains() {
		for (int i = 0; i < 1000; i++) {
			bSS.add(i);
		}
		boolean test = bSS.contains(55);

	    Assert.assertEquals(test, true);
	  }
	  
	  @SuppressWarnings("unchecked")
	@Test
	  public void testContainsAllTrue() {
		  ArrayList<Integer> testContains1 = new ArrayList<>();
		  testContains1.add(78);
		  testContains1.add(108);
		  Assert.assertTrue(bSS.containsAll(testContains1));
	  }
	  
	  @SuppressWarnings("unchecked")
	@Test
	  public void testContainsAllFalse() {
		  ArrayList<Integer> testContains2 = new ArrayList<>();
		  testContains2.add(78);
		  testContains2.add(108);
		  testContains2.add(1108);
		  Assert.assertFalse(bSS.containsAll(testContains2));
	  }
	  
	  @Test
	  public void testIsEmpty() {
	    Assert.assertFalse(bSS.isEmpty());
	  }
	  
//	  @Test
//	  public void testIterator() {
//	  }
	  
	  @Test
	  public void testRemove() {
	    int toRemove = 2;
	    bSS.remove(toRemove);
	    Assert.assertFalse(bSS.contains(2));
	  }
  
	  @SuppressWarnings("unchecked")
	@Test
	  public void testRemoveAll() {
		ArrayList<Integer> toRemove = new ArrayList<>();
		toRemove.add(1);
		toRemove.add(3);
		bSS.removeAll(toRemove);
	    Assert.assertFalse(bSS.contains(1));
	  }
	  


	@AfterEach
	void tearDown() throws Exception {
	}



}
