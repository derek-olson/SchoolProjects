package assignment03;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

import org.junit.Before;


public class AnagramUtil {

	public AnagramUtil() {
		// TODO Auto-generated constructor stub
	}
	
	//This method returns the sorted version of the input string.
	public static String sort(String string) {
		char[] charArray = string.toCharArray();
		for (int i = 1; i < charArray.length; i++) {
			char index = charArray[i];
			int j = i;
			while (j >= 1 && charArray[j-1] > index) {
				charArray[j] = charArray[j - 1];
				j--;
			}
			charArray[j] = index;
		}
		return String.valueOf(charArray);
	}

	//This generic method sorts the input array using an insertion sort and the input Comparator object.
	public static <T> void insertionSort(T[] array, Comparator<? super T> comparator) {
		long startTime = System.nanoTime();
		for (int i = 1; i < array.length; i++) {
			T index = array[i];
			int j = i;
			while(j  > 0 && comparator.compare(array[j-1] , index) > 0) {
				array[j] = array [j-1];
				j--;
			}
			array[j] = index;
		}
	}
	
	//This method returns true if the two input strings are anagrams of each other, otherwise returns false.
	public static boolean areAnagrams(String string1, String string2) {
		String string1ToLowerCase = string1.toLowerCase();
		String string2ToLowerCase = string2.toLowerCase();
		String string1Sorted = sort(string1ToLowerCase);
		String string2Sorted = sort(string2ToLowerCase);
		char[] charArrayLS = string1Sorted.toCharArray();
		char[] charArrayRS = string2Sorted.toCharArray();
		if (charArrayLS.length != charArrayRS.length) {
			return false;
		}
		for (int i = 0; i < charArrayLS.length; i++) {
			if (charArrayLS[i] != charArrayRS[i]) {
				return false;
			}
		}
		return true;
	}
	
	//This method returns the largest group of anagrams in the input array of words, in no particular order. It returns an empty array if there are no anagrams in the input array.
	public static String[] getLargestAnagramGroup(String[] stringArray) {
		// initialize some variables to keep track of counts and anagrams
		int count = 0;
		int maxVal = 0;
		String maxAnagram = "";
		String[] anagrams = null; 
		String[] tempArray = new String[stringArray.length];
		// sort the characters of each string in the array
		for (int k = 0; k < stringArray.length; k++) {
			tempArray[k] = sort(stringArray[k].toLowerCase());
			}
		
		// sort the sorted words in the array alphabetically
		OrderByString comparator = new OrderByString();
		insertionSort(tempArray, comparator);
		
		for(int i = 1; i < tempArray.length; i++) {
			if (areAnagrams(tempArray[i], tempArray[i-1])) {
				count +=1;
			}
			if(!areAnagrams(tempArray[i], tempArray[i-1]) && maxVal < count) {
				maxVal = count;
				count = 0;
				maxAnagram = tempArray[i-1];
			}
			if(!areAnagrams(tempArray[i], tempArray[i-1]) && maxVal > count) {
				count = 0;
			}
		}
		if (maxVal == 0) {
			return new String[0];
		}
		anagrams = new String[maxVal+1];
		int index = 0;
		for (int j = 0; j < stringArray.length; j++) {
			if (areAnagrams(maxAnagram, stringArray[j])) {
				anagrams[index] = stringArray[j];
				index += 1;
			}
		}
		return anagrams;
	}
	
	
	//Behaves the same as the previous method, but reads the list of words from the input filename. It is assumed that the file contains one word per line. If the file does not exist or is empty, the method returns an empty array because there are no anagrams.
	public static String[] getLargestAnagramGroup(String filename) throws FileNotFoundException {
		Scanner scanner = new Scanner(new File(filename));
		List<String> lines = new ArrayList<String>();
		while (scanner.hasNextLine()) {
		  lines.add(scanner.nextLine());
		}
		scanner.close();
		String[] arr = lines.toArray(new String[0]);
		
		return getLargestAnagramGroup(arr);
		
	}
	
	public static String[] getLargestAnagramGroupJavaSort(String[] stringArray) {
		// initialize some variables to keep track of counts and anagrams
		int count = 0;
		int maxVal = 0;
		String maxAnagram = "";
		String[] anagrams = null; 
		String[] tempArray = new String[stringArray.length];
		// sort the characters of each string in the array
		for (int k = 0; k < stringArray.length; k++) {
			tempArray[k] = sort(stringArray[k]);
			}
		
		// sort the sorted words in the array alphabetically
		Arrays.sort(tempArray);
		
		for(int i = 1; i < tempArray.length; i++) {
			if (tempArray[i] == tempArray[i-1]) {
				count +=1;
			}
			if(tempArray[i] != tempArray[i-1] && maxVal < count) {
				maxVal = count;
				count = 0;
				maxAnagram = tempArray[i-1];
			}
			if(tempArray[i] != tempArray[i-1] && maxVal > count) {
				count = 0;
			}
		}
		if (maxVal == 0) {
			return new String[0];
		}
		anagrams = new String[maxVal+1];
		int index = 0;
		for (int j = 0; j < stringArray.length; j++) {
			if (areAnagrams(maxAnagram, stringArray[j])) {
				anagrams[index] = stringArray[j];
				index += 1;
			}
		}
		return anagrams;
	}

	public static void main(String[] args) throws IOException {
		
		//test the string sort function
		String sorted = sort("football");
		if (!sorted.contentEquals("abflloot")) {
			System.err.println("SORT ERROR: all lower case");
		}
		
		//test with upper case letters
		String sorted2 = sort("FOOTBALL");
		if (!sorted2.contentEquals("ABFLLOOT")) {
			System.err.println("SORT ERROR: all upper case");
		}
		
		// test the getLargestAnagramGroup function
		String[] stringArray = new String[] {"hi", "ih", "breath", "was", "saw", "aws", "breadth"};
		String[] test = getLargestAnagramGroup(stringArray);
		for (String item : test) {System.out.println(item);}
		if (test.equals(new String[] {"was", "saw", "aws"})){
			System.err.println("Get Largest Anagram Group Error: quick test");
		}
		
		// test with file
		String[] test2 = getLargestAnagramGroup("sample_word_list.txt");
		if (test2.equals(new String[] {"carets", "Caters", "caster", "crates", "Reacts", "recast", "traces"})){
			System.err.println("Get Largest Anagram Group Error: moderate test");
		}
		

		// Test the insertion sort
		OrderByString comparator = new OrderByString();
		insertionSort(stringArray, comparator);
		for (String item : stringArray) {
			System.out.println(String.valueOf(item));
		}
		
//		String word10 = getRandomWord(10);
//		String word100 = getRandomWord(100);
//		String word1000 = getRandomWord(1000);
//		String word10000 = getRandomWord(10000);
//		String word20000 = getRandomWord(20000);
//		String word30000 = getRandomWord(30000);
//		String word40000 = getRandomWord(40000);
//		String word50000 = getRandomWord(50000);
//		String word60000 = getRandomWord(60000);
//		String word70000 = getRandomWord(70000);
//		String word80000 = getRandomWord(80000);
//		String word90000 = getRandomWord(90000);
//		String word100000 = getRandomWord(100000);
//		System.out.println("SORT WORDS:");
//		long startTime1 = System.nanoTime();
//		sort(word10);
//		long endTime1 = System.nanoTime();
//		long totalTime1 = endTime1 - startTime1;
//		System.out.println("10 "+totalTime1);
//		
//		long startTime2 = System.nanoTime();
//		sort(word100);
//		long endTime2 = System.nanoTime();
//		long totalTime2 = endTime2 - startTime2;
//		System.out.println("100 "+totalTime2);
//		
//		long startTime3 = System.nanoTime();
//		sort(word1000);
//		long endTime3 = System.nanoTime();
//		long totalTime3 = endTime3 - startTime3;
//		System.out.println("1000 "+totalTime3);
//		
//		long startTime4 = System.nanoTime();
//		sort(word10000);
//		long endTime4 = System.nanoTime();
//		long totalTime4 = endTime4 - startTime4;
//		System.out.println( "10000 "+totalTime4);
//		
//		long startTime5 = System.nanoTime();
//		sort(word20000);
//		long endTime5 = System.nanoTime();
//		long totalTime5 = endTime5 - startTime5;
//		System.out.println( "20000 "+totalTime5);
//		
//		long startTime7 = System.nanoTime();
//		sort(word30000);
//		long endTime7 = System.nanoTime();
//		long totalTime7 = endTime7 - startTime7;
//		System.out.println( "30000 "+totalTime7);
//		
//		long startTime8 = System.nanoTime();
//		sort(word40000);
//		long endTime8 = System.nanoTime();
//		long totalTime8 = endTime8 - startTime8;
//		System.out.println( "40000 "+totalTime8);
//		
//		long startTime9 = System.nanoTime();
//		sort(word50000);
//		long endTime9 = System.nanoTime();
//		long totalTime9 = endTime9 - startTime9;
//		System.out.println( "50000 "+totalTime9);
//		
//		long startTime10 = System.nanoTime();
//		sort(word60000);
//		long endTime10 = System.nanoTime();
//		long totalTime10 = endTime10 - startTime10;
//		System.out.println( "60000 "+totalTime10);
//		
//		long startTime11 = System.nanoTime();
//		sort(word70000);
//		long endTime11 = System.nanoTime();
//		long totalTime11 = endTime11 - startTime11;
//		System.out.println( "70000 "+totalTime11);
//		
//		long startTime12 = System.nanoTime();
//		sort(word80000);
//		long endTime12 = System.nanoTime();
//		long totalTime12 = endTime12 - startTime12;
//		System.out.println( "80000 "+totalTime12);
//		
//		long startTime13 = System.nanoTime();
//		sort(word90000);
//		long endTime13 = System.nanoTime();
//		long totalTime13 = endTime13 - startTime13;
//		System.out.println( "90000 "+totalTime13);
//		
//		long startTime14 = System.nanoTime();
//		sort(word100000);
//		long endTime14 = System.nanoTime();
//		long totalTime14 = endTime14 - startTime14;
//		System.out.println( "100000 "+totalTime14);
		
		

		// Get times for getting largest anagram group
//		String[] stringArray10 = generateRandomWords(10);
//		String[] stringArray100 = generateRandomWords(100);
//		String[] stringArray1000 = generateRandomWords(1000);
//		String[] stringArray10000 = generateRandomWords(10000);
//		String[] stringArray20000 = generateRandomWords(20000);
//		String[] stringArray30000 = generateRandomWords(30000);
//		String[] stringArray40000 = generateRandomWords(40000);
//		String[] stringArray50000 = generateRandomWords(50000);
//		String[] stringArray100000 = generateRandomWords(100000);
//		
//		
//		System.out.println("GET LARGEST ANAGRAM GROUP:");
//		long startTime5 = System.nanoTime();
//		String[] largestAnagramGroup10 = getLargestAnagramGroup(stringArray10);
//		long endTime5 = System.nanoTime();
//		long totalTime5 = endTime5 - startTime5;
//		System.out.println( "10 "+totalTime5);
//		
//		long startTime6 = System.nanoTime();
//		String[] largestAnagramGroup100 = getLargestAnagramGroup(stringArray100);
//		long endTime6 = System.nanoTime();
//		long totalTime6 = endTime6 - startTime6;
//		System.out.println( "100 "+totalTime6);
//		
//		long startTime7 = System.nanoTime();
//		String[] largestAnagramGroup1000 = getLargestAnagramGroup(stringArray1000);
//		long endTime7 = System.nanoTime();
//		long totalTime7 = endTime7 - startTime7;
//		System.out.println( "1000 "+totalTime7);
//		
//		long startTime8 = System.nanoTime();
//		String[] largestAnagramGroup10000 = getLargestAnagramGroup(stringArray10000);
//		long endTime8 = System.nanoTime();
//		long totalTime8 = endTime8 - startTime8;
//		System.out.println( "10000 "+totalTime8);
//		
//		long startTime13 = System.nanoTime();
//		String[] largestAnagramGroup20000 = getLargestAnagramGroup(stringArray20000);
//		long endTime13 = System.nanoTime();
//		long totalTime13 = endTime13 - startTime13;
//		System.out.println( "20000 "+totalTime13);
//		
//		long startTime12 = System.nanoTime();
//		String[] largestAnagramGroup30000 = getLargestAnagramGroup(stringArray30000);
//		long endTime12 = System.nanoTime();
//		long totalTime12 = endTime12 - startTime12;
//		System.out.println( "30000 "+totalTime12);
//		
//		long startTime10 = System.nanoTime();
//		String[] largestAnagramGroup40000 = getLargestAnagramGroup(stringArray40000);
//		long endTime10 = System.nanoTime();
//		long totalTime10 = endTime10 - startTime10;
//		System.out.println( "40000 "+totalTime10);
//		
//		long startTime11 = System.nanoTime();
//		String[] largestAnagramGroup50000 = getLargestAnagramGroup(stringArray50000);
//		long endTime11 = System.nanoTime();
//		long totalTime11 = endTime11 - startTime11;
//		System.out.println( "50000 "+totalTime11);
//		
//		long startTime9 = System.nanoTime();
//		String[] largestAnagramGroup100000 = getLargestAnagramGroup(stringArray100000);
//		long endTime9 = System.nanoTime();
//		long totalTime9 = endTime9 - startTime9;
//		System.out.println( "100000 "+totalTime9);
		
		
		// get times for areAnagrams function
		for (int i = 1; i < 100000; i*=5) {
			long startTime = System.nanoTime();
			String word1 = getRandomWord(i);
			String word2 = getRandomWord(i);
			areAnagrams(word1, word2);
			long endTime = System.nanoTime();
			long totalTime = endTime - startTime;
			System.out.println( i+" "+totalTime);
		}
		
		for (int a = 1; a < 5000000; a *= 5) {
			String[] stringArray2 = generateRandomWords(a);
			long startTime = System.nanoTime();
			getLargestAnagramGroupJavaSort(stringArray2);
			long endTime = System.nanoTime();
			long totalTime = endTime - startTime;
			System.out.println( a+" "+totalTime);
		}
		

	}
	
	  /**
	   * Comparator that defines an ordering among strings.
	   * Takes a string as a parameter.
	   */
	  protected static class OrderByString implements Comparator<String> {
	    public int compare(String lhs,String rhs) {
	      return (int) (lhs.compareTo(rhs));
	    }
	  }
	  
	  protected static class OrderByChar implements Comparator<Character> {
		    public int compare(Character lhs, Character rhs) {
		      return (int) (lhs.compareTo(rhs));
		    }
		  }
	  
		public static String[] generateRandomWords(int numberOfWords)
		{
		    String[] randomStrings = new String[numberOfWords];
		    Random random = new Random();
		    for(int i = 0; i < numberOfWords; i++)
		    {
		        char[] word = new char[random.nextInt(8)+3]; 
		        for(int j = 0; j < word.length; j++)
		        {
		            word[j] = (char)('a' + random.nextInt(26));
		        }
		        randomStrings[i] = new String(word);
		    }
		    return randomStrings;
		}
		
		public static String getRandomWord(int length) {
		    String randomWord = "";
		    for(int i = 0; i < length; i++) {
		    	randomWord += (char)(Math.random() * 26 + 97);
		    }
		    return randomWord;
		}
		
		

}


