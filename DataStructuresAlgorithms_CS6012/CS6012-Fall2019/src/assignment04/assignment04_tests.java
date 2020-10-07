package assignment04;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class assignment04_tests<T> {
	int size = 100000;
	ArrayList<Integer> bestCase = new ArrayList<>();
	ArrayList<Integer> averageCase = new ArrayList<>();
	ArrayList<Integer> worstCase = new ArrayList<>();
	
	@SuppressWarnings("rawtypes")
	SortUtil sort = new SortUtil();
	
	@SuppressWarnings("static-access")
	@BeforeEach
	void setUp() throws Exception {
		bestCase = sort.generateBestCase(size);
		averageCase = sort.generateAverageCase(size);
		worstCase = sort.generateWorstCase(size);
		
	}

	@AfterEach
	void tearDown() throws Exception {
	}

	@SuppressWarnings({ "unchecked", "static-access" })
	@Test
	void testBestCaseMergeSort() {
		int threshold = 100;
		ArrayList<Integer> testArray = new ArrayList<>();
		for (int i = 0; i < size; i++) {
			testArray.add(i);
		}
		sort.mergesortDriver(bestCase, new IntComparator());
		assertEquals(testArray, bestCase);
	}
	
	@SuppressWarnings({ "unchecked", "static-access" })
	@Test
	void testAverageCaseMergeSort() {
		int threshold = 100;
		ArrayList<Integer> testArray = new ArrayList<>(Arrays.asList(0,1,1,3,4,5,7,8,9,9));
		sort.mergesortDriver(averageCase, new IntComparator());
		assertEquals(testArray, averageCase);
	}
	
	@SuppressWarnings({ "unchecked", "static-access" })
	@Test
	void testWorstCaseMergeSort() {
		int threshold = 100;
		ArrayList<Integer> testArray = new ArrayList<>();
		for (int i = 1; i < size+1; i++) {
			testArray.add(i);
		}
		sort.mergesortDriver(worstCase, new IntComparator());
		assertEquals(testArray, worstCase);
	}
	
	@SuppressWarnings({ "unchecked", "static-access" })
	@Test
	void testBestCaseQuickSort() {
		ArrayList<Integer> testArray = new ArrayList<>();
		for (int i = 0; i < size; i++) {
			testArray.add(i);
		}
		sort.quicksort(bestCase, new IntComparator());
		assertEquals(testArray, bestCase);
	}
	
	@SuppressWarnings({ "unchecked", "static-access" })
	@Test
	void testAverageCaseQuickSort() {
		ArrayList<Integer> testArray = new ArrayList<>(Arrays.asList(0,1,1,3,4,5,7,8,9,9));
		sort.quicksort(averageCase, new IntComparator());
		assertEquals(testArray, averageCase);
	}
	
	@SuppressWarnings({ "unchecked", "static-access" })
	@Test
	void testWorstCaseQuickSort() {
		ArrayList<Integer> testArray = new ArrayList<>();
		for (int i = 1; i < size+1; i++) {
			testArray.add(i);
		}
		sort.quicksort(worstCase, new IntComparator());
		assertEquals(testArray, worstCase);
	}
	
	@SuppressWarnings({ "unchecked", "static-access" })
	@Test
	void testWorstCaseQuickSort2() {
		ArrayList<Integer> testArray = new ArrayList<>();
		for (int i = 1; i < size+1; i++) {
			testArray.add(i);
		}
		sort.quickSort(worstCase, new IntComparator(), 0, size-1);
		assertEquals(testArray, worstCase);
	}
	
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	Comparator comparator = (Comparator<T>) Comparator.naturalOrder();
	
	@SuppressWarnings("rawtypes")
	class IntComparator implements Comparator{  
		public int compare(Object o1,Object o2){  
			int int1 = (int)o1;  
			int int2 = (int)o2;  
			return int1-int2;
		} 
	}

}
