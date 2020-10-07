package assignment04;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;

public class SortUtil<T> {
	//private static int threshold = 2;
	Comparator<T> comparator;
	ArrayList<T> arr;
	public static int threshold = 100;
	
	public SortUtil() {
		arr = new ArrayList<>();
	}
	
	public SortUtil(Comparator<T> comparator) {
		this.comparator = comparator;
		arr = new ArrayList<>();
	}
	
	//This method performs a mergesort on the generic ArrayList given as input.
	public static <T> void mergesortDriver(ArrayList<T> arr, Comparator<? super T> comparator){
			ArrayList<T> tempArray = new ArrayList<>(arr.size());
			for (T _ : arr) tempArray.add(null);
			int size = arr.size();
			int start = 0;
			int end = size - 1;
            // Sort first and second halves 
            mergesortRecursive(arr, comparator, start, end, tempArray); 
        } 

	
	public static <T> void mergesortRecursive(ArrayList<T> arr, Comparator<? super T> comparator, int start, int end, ArrayList<T> temp){
		if(end - start <= threshold) { 
			insertionSort(arr, comparator, start, end);
			return;
		}
		if (start < end) { 
            // Find the middle point 
            int mid = (start + end) / 2; 
            
            mergesortRecursive(arr, comparator, start, mid, temp);
            mergesortRecursive(arr, comparator, mid + 1, end, temp);
            
            //Merge the sorted halves 
            merge(arr, comparator, start, mid, end, temp);
        } 
	}
	
	public static <T> void merge(ArrayList<T> arr, Comparator<? super T> comparator, int start, int mid, int end, ArrayList<T> temp){		 
        // Initial indexes to increment 
        int i = start, j = mid+1, k = start; 
		while(i <= mid && j <= end){
			if(comparator.compare(arr.get(i), arr.get(j)) < 0) {
				temp.set(k, arr.get(i));
				i++;
				k++;
			}
			if(comparator.compare(arr.get(i), arr.get(j)) >= 0) {
				temp.set(k, arr.get(j));
				j++;
				k++;
			}			
		}
		while (i <= mid){ 
			temp.set(k, arr.get(i)); 
	        i++; 
	        k++; 
	      }
		while (j <= end){ 
			temp.set(k, arr.get(j)); 
	        j++; 
	        k++; 
	      }
		for (int l = start; l < k; l++) {
			arr.set(l, temp.get(l));
		}
	}
	
	public static <T> void insertionSort(ArrayList<T> arr, Comparator<? super T> comparator, int start, int end) {
		T tempElement;
		for(int i = start+1; i <= end; i++) {
			T key = arr.get(i);
			int j = i-1;
			while(j >=start  && comparator.compare(arr.get(j), key) > 0) {
				tempElement = arr.get(j);
				arr.set(j, arr.get(j+1));
				arr.set(j+1, tempElement);
				j--;
			}
		}
	}
	
	public static <T> void quicksort(ArrayList<T> arr, Comparator<? super T> comparator) {
		 int begin = 0; 
		 int end = arr.size() - 1;
		if(begin >= end) {
			return;
		}
		quicksortRecursive(arr, comparator, begin, end);
		
	}
	
	//This method performs a quicksort on the generic ArrayList given as input.
	public static <T> void quicksortRecursive(ArrayList<T> arr, Comparator<? super T> comparator, int begin, int end) {
		if(begin >= end) {
			return;
		}
		int pivot_index= partition(arr, comparator, begin, end);
		if(pivot_index-1>begin) {
			quicksortRecursive(arr, comparator,begin, pivot_index-1);
		}
		if(pivot_index+1<end) {
			quicksortRecursive(arr, comparator, pivot_index+1, end);
		}
	}
	//this method returns the pivot index used by the quicksort method to split the array.
	private static <T> int partition(ArrayList<T> arr, Comparator<? super T> comparator, int begin, int end) {
		T pivot = arr.get(end);
	 
	    for (int i = begin; i < end; i++) {
	        if (comparator.compare(arr.get(i), pivot) < 0) {
	            T swapTemp = arr.get(begin);
	            arr.set(begin, arr.get(i));
	            arr.set(i, swapTemp);
	            begin++;
	        }
	    }
	    T swapTemp = arr.get(begin);
	    arr.set(begin, arr.get(end));
	    arr.set(end, swapTemp);
	 
	    return begin;
	}
	// These quicksort methods do not have an explicit partition method and thus do not 
	public static <T> void quickSort(ArrayList<T> arr, Comparator<? super T> comparator, int begin, int end) {
        int middle = begin + (end - begin) / 2;
        T pivot = arr.get(middle);
        int i = begin, j = end;
        while (i <= j) {
            while (comparator.compare(arr.get(i), pivot) < 0) {
                i++;
            }
            while (comparator.compare(arr.get(j), pivot) > 0) {
                j--;
            }
            if (i <= j) {
                swap (arr, i, j);
                i++;
                j--;
            }
        }
        if (begin < j){
            quickSort(arr, comparator, begin, j);
        }
        if (end > i){
            quickSort(arr, comparator, i, end);
        }
    }
	
	public static <T> void quickSortRandom(ArrayList<T> arr, Comparator<? super T> comparator, int begin, int end) {
        Random random = new Random(0);
        T pivot = arr.get(random.nextInt(100));
        int i = begin, j = end;
        while (i <= j) {
            while (comparator.compare(arr.get(i), pivot) < 0) {
                i++;
            }
            while (comparator.compare(arr.get(j), pivot) > 0) {
                j--;
            }
            if (i <= j) {
                swap (arr, i, j);
                i++;
                j--;
            }
        }
        if (begin < j){
            quickSort(arr, comparator, begin, j);
        }
        if (end > i){
            quickSort(arr, comparator, i, end);
        }
    }
	
	public static <T> void quickSortEnd(ArrayList<T> arr, Comparator<? super T> comparator, int begin, int end) {
        T pivot = arr.get(end);
        int i = begin, j = end;
        while (i <= j) {
            while (comparator.compare(arr.get(i), pivot) < 0) {
                i++;
            }
            while (comparator.compare(arr.get(j), pivot) > 0) {
                j--;
            }
            if (i <= j) {
                swap (arr, i, j);
                i++;
                j--;
            }
        }
        if (begin < j){
            quickSort(arr, comparator, begin, j);
        }
        if (end > i){
            quickSort(arr, comparator, i, end);
        }
    }
	
	  public static<T> void swap (ArrayList<T> arr, int x, int y){
	        T temp = arr.get(x);
	        arr.set(x,arr.get(y));
	        arr.set(y, temp);
	    }
	
	
	//This method generates and returns an ArrayList of integers 1 to size in ascending order.
	public static ArrayList<Integer> generateBestCase(int size){
		ArrayList<Integer> arr = new ArrayList<>();
		for (int i = 0; i < size; i++) {
			arr.add(i);
		}
		return arr;
	}
	
	//This method generates and returns an ArrayList of integers 1 to size in permuted order 
	//(i,e., randomly ordered). I will show you in class how to permute a list.
	public static ArrayList<Integer> generateAverageCase(int size){
		Random random = new Random(0);
		ArrayList<Integer> arr = new ArrayList<>();
		for (int i = 0; i < size; i++) {
			arr.add(random.nextInt(10));
		}
		return arr;
	}
	
	//This method generates and returns an ArrayList of integers 1 to size in descending order.
	public static ArrayList<Integer> generateWorstCase(int size){
		ArrayList<Integer> arr = new ArrayList<>();
		for (int i = size; i > 0; i--) {
			arr.add(i);
		}
		return arr;
	}

}
