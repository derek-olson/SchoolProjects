package assignment04;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Comparator;

public class assignment04_timing {
	
	static ArrayList<Integer> bestCase = new ArrayList<>();
	static ArrayList<Integer> averageCase = new ArrayList<>();
	static ArrayList<Integer> worstCase = new ArrayList<>();

	@SuppressWarnings({ "static-access", "unchecked" })
	public static <T> void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
		PrintWriter writer = new PrintWriter("merge_threshold_compare.txt", "UTF-8"); 
		writer.println("Test,"+"Threshold,"+"Size,"+"Time");
		@SuppressWarnings("rawtypes")
		SortUtil sort = new SortUtil();
		
		@SuppressWarnings({ "rawtypes" })
		Comparator comparator = (Comparator<T>) Comparator.naturalOrder();
		
		// test mergesort threshold 
		int threshold1 = 10;
		int merge_size1 = 200000;
		for (int l = 0; l <= 51000; l+=10000) {
			averageCase = sort.generateAverageCase(merge_size1);
			long start_time_average = System.nanoTime();
			sort.mergesortDriver(averageCase, comparator);
			long total_time_average = System.nanoTime() - start_time_average;
			writer.println("Threshold Test - 10,"+threshold1+","+merge_size1+","+total_time_average);
			merge_size1 += l;
		}
		int threshold2 = 100;
		int merge_size2 = 200000;
		for (int l = 0; l <= 51000; l+=10000) {
			averageCase = sort.generateAverageCase(merge_size2);
			long start_time_average = System.nanoTime();
			sort.mergesortDriver(averageCase, comparator);
			long total_time_average = System.nanoTime() - start_time_average;
			writer.println("Threshold Test - 100,"+threshold2+","+merge_size2+","+total_time_average);
			merge_size2 += l;
		}
		int threshold3 = 1000;
		int merge_size3 = 200000;
		for (int l = 0; l <= 51000; l+=10000) {
			averageCase = sort.generateAverageCase(merge_size3);
			long start_time_average = System.nanoTime();
			sort.mergesortDriver(averageCase, comparator);
			long total_time_average = System.nanoTime() - start_time_average;
			writer.println("Threshold Test - 1000,"+threshold3+","+merge_size3+","+total_time_average);
			merge_size3 += l;
		}
		int threshold4 = 10000;
		int merge_size4 = 200000;
		for (int l = 0; l <= 51000; l+=10000) {
			averageCase = sort.generateAverageCase(merge_size4);
			long start_time_average = System.nanoTime();
			sort.mergesortDriver(averageCase, comparator);
			long total_time_average = System.nanoTime() - start_time_average;
			writer.println("Threshold Test - 10000,"+threshold4+","+merge_size4+","+total_time_average);
			merge_size4+=l;
		}
		int threshold5 = 100000;
		int merge_size5 = 200000;
		for (int l = 0; l <= 51000; l+=10000) {
			averageCase = sort.generateAverageCase(merge_size5);
			long start_time_average = System.nanoTime();
			sort.mergesortDriver(averageCase, comparator);
			long total_time_average = System.nanoTime() - start_time_average;
			writer.println("Threshold Test - 100000,"+threshold5+","+merge_size5+","+total_time_average);
			merge_size5+=l;
		}
		
		
//		int size = 100;
//		for (int k = 0; k <= 100000; k++) {
//
//			worstCase = sort.generateWorstCase(size);
//			
//			//time quick sort worst case
//			long start_time_worst2 = System.nanoTime();
//			sort.quickSort(worstCase, comparator, 0, size-1);
//			long total_time_worst2 = System.nanoTime() - start_time_worst2;
//			writer.println("Middle Pivot - Worst Case,"+size+","+total_time_worst2);
//			
//			long start_time_worst3 = System.nanoTime();
//			sort.quickSortRandom(worstCase, comparator, 0, size-1);
//			long total_time_worst3 = System.nanoTime() - start_time_worst3;
//			writer.println("Random Pivot - Worst Case,"+size+","+total_time_worst3);
//			
//			long start_time_worst = System.nanoTime();
//			sort.quickSortEnd(worstCase, comparator, 0, size-1);
//			long total_time_worst = System.nanoTime() - start_time_worst;
//			writer.println("End Pivot - Worst Case,"+size+","+total_time_worst);
//			
//			size += 1000;
//		}
//		int threshold = 10000;
//		int size = 100;
//		for (int k = 0; k <= 500000; k++) {
//
//			bestCase = sort.generateBestCase(size);
//			averageCase = sort.generateAverageCase(size);
//			worstCase = sort.generateWorstCase(size);
//			
//			//time quick sort worst case
//			long start_time_worst2 = System.nanoTime();
//			sort.quickSortRandom(bestCase, comparator, 0, size-1);
//			long total_time_worst2 = System.nanoTime() - start_time_worst2;
//			writer.println("Middle Pivot - Worst Case,"+size+","+total_time_worst2);
//			
//			long start_time_worst3 = System.nanoTime();
//			sort.quickSortRandom(averageCase, comparator, 0, size-1);
//			long total_time_worst3 = System.nanoTime() - start_time_worst3;
//			writer.println("Random Pivot - Worst Case,"+size+","+total_time_worst3);
//			
//			long start_time_worst = System.nanoTime();
//			sort.quickSortRandom(worstCase, comparator, 0, size-1);
//			long total_time_worst = System.nanoTime() - start_time_worst;
//			writer.println("End Pivot - Worst Case,"+size+","+total_time_worst);
//			
//			
//			//time merge sort 
//			long start_time_worst4 = System.nanoTime();
//			sort.mergesortDriver(bestCase, comparator, threshold);
//			long total_time_worst4 = System.nanoTime() - start_time_worst4;
//			writer.println("Mergesort - Best Case,"+size+","+total_time_worst4);
//			
//			long start_time_worst5 = System.nanoTime();
//			sort.mergesortDriver(averageCase, comparator, threshold);
//			long total_time_worst5 = System.nanoTime() - start_time_worst5;
//			writer.println("Mergesort - Average Case,"+size+","+total_time_worst5);
//			
//			long start_time_worst6 = System.nanoTime();
//			sort.mergesortDriver(worstCase, comparator, threshold);
//			long total_time_worst6 = System.nanoTime() - start_time_worst6;
//			writer.println("Mergesort - Worst Case,"+size+","+total_time_worst6);
//			
//			size += 50000;
//		}
		
		
		writer.close();

	}
	
	
	

}
