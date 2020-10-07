package assignment06;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class assignment06_timing {
	
	public static int collisions(int size, ChainingHashTable cht) {
		int collisions = 0;
		for (int i=0; i<size; i++) {
			collisions += cht.listSize(i);
		}
		return collisions;
	}
	
	public static ArrayList<String> generateRandomWords(int numberOfWords){
		ArrayList<String>  randomStrings = new ArrayList<String>(numberOfWords) ;
	    Random random = new Random();
	    for(int i = 0; i < numberOfWords; i++)
	    {
	        char[] word = new char[random.nextInt(8)+3]; 
	        for(int j = 0; j < word.length; j++)
	        {
	            word[j] = (char)('a' + random.nextInt(26));
	        }
	        randomStrings.add(new String(word));
	    }
	    return randomStrings;
	}

	public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
		
		/**
		 * Initialize new hash functors
		 */
		ReallyBadHashFunctor bhf = new ReallyBadHashFunctor();
		MediocreHashFunctor mhf = new MediocreHashFunctor();
		GoodHashFunctor ghf = new GoodHashFunctor();
		
		PrintWriter writer = new PrintWriter("hash_functor_timing_collisions.txt", "UTF-8");
		writer.println("Test,"+"Method,"+"Size,"+"Time,"+"Collisions");
		
		/**
		 * Initialize new chaining hash table
		 */
		ChainingHashTable cht_b_10 = new ChainingHashTable(10, bhf);
		ChainingHashTable cht_m_10 = new ChainingHashTable(10, mhf);
		ChainingHashTable cht_g_10 = new ChainingHashTable(10, ghf);
		
		ChainingHashTable cht_b_100 = new ChainingHashTable(100, bhf);
		ChainingHashTable cht_m_100 = new ChainingHashTable(100, mhf);
		ChainingHashTable cht_g_100 = new ChainingHashTable(100, ghf);
		
		ChainingHashTable cht_b_1000 = new ChainingHashTable(1000, bhf);
		ChainingHashTable cht_m_1000 = new ChainingHashTable(1000, mhf);
		ChainingHashTable cht_g_1000 = new ChainingHashTable(1000, ghf);
		
		ChainingHashTable cht_b_10000 = new ChainingHashTable(10000, bhf);
		ChainingHashTable cht_m_10000 = new ChainingHashTable(10000, mhf);
		ChainingHashTable cht_g_10000 = new ChainingHashTable(10000, ghf);
		
		ChainingHashTable cht_b_100000 = new ChainingHashTable(100000, bhf);
		ChainingHashTable cht_m_100000 = new ChainingHashTable(100000, mhf);
		ChainingHashTable cht_g_100000 = new ChainingHashTable(100000, ghf);
		
		ArrayList<String> strings = generateRandomWords(100000);
		
		long start_time_1 = System.nanoTime();
		cht_b_10.addAll(strings);
		int c1 = cht_b_10.getCollisions();
		long total_time_1 = System.nanoTime() - start_time_1;
		writer.println("addAll,"+"bad,"+"10,"+total_time_1+","+c1);
		
		long start_time_2 = System.nanoTime();
		cht_m_10.addAll(strings);
		int c2 = cht_m_10.getCollisions();
		long total_time_2 = System.nanoTime() - start_time_2;
		writer.println("addAll,"+"med,"+"10,"+total_time_2+","+c2);
		
		long start_time_3 = System.nanoTime();
		cht_g_10.addAll(strings);
		int c3 = cht_g_10.getCollisions();
		long total_time_3 = System.nanoTime() - start_time_3;
		writer.println("addAll,"+"good,"+"10,"+total_time_3+","+c3);
		
		long start_time_4 = System.nanoTime();
		cht_b_100.addAll(strings);
		int c4 = cht_b_100.getCollisions();
		long total_time_4 = System.nanoTime() - start_time_4;
		writer.println("addAll,"+"bad,"+"100,"+total_time_4+","+c4);
		
		long start_time_5 = System.nanoTime();
		cht_m_100.addAll(strings);
		int c5 = cht_m_100.getCollisions();
		long total_time_5 = System.nanoTime() - start_time_5;
		writer.println("addAll,"+"med,"+"100,"+total_time_5+","+c5);
		
		long start_time_6 = System.nanoTime();
		cht_g_100.addAll(strings);
		int c6 = cht_g_100.getCollisions();
		long total_time_6 = System.nanoTime() - start_time_6;
		writer.println("addAll,"+"good,"+"100,"+total_time_6+","+c6);
		
		long start_time_7 = System.nanoTime();
		cht_b_1000.addAll(strings);
		int c7 = cht_b_1000.getCollisions();
		long total_time_7 = System.nanoTime() - start_time_7;
		writer.println("addAll,"+"bad,"+"1000,"+total_time_7+","+c7);
		
		long start_time_8 = System.nanoTime();
		cht_m_1000.addAll(strings);
		int c8 = cht_m_1000.getCollisions();
		long total_time_8 = System.nanoTime() - start_time_8;
		writer.println("addAll,"+"med,"+"1000,"+total_time_8+","+c8);
		
		long start_time_9 = System.nanoTime();
		cht_g_1000.addAll(strings);
		int c9 = cht_g_1000.getCollisions();
		long total_time_9 = System.nanoTime() - start_time_9;
		writer.println("addAll,"+"good,"+"1000,"+total_time_9+","+c9);
		
		long start_time_10 = System.nanoTime();
		cht_b_10000.addAll(strings);
		int c10 = cht_b_10000.getCollisions();
		long total_time_10 = System.nanoTime() - start_time_10;
		writer.println("addAll,"+"bad,"+"10000,"+total_time_10+","+c10);
		
		long start_time_11 = System.nanoTime();
		cht_m_10000.addAll(strings);
		int c11 = cht_m_10000.getCollisions();
		long total_time_11 = System.nanoTime() - start_time_11;
		writer.println("addAll,"+"med,"+"10000,"+total_time_11+","+c11);
		
		long start_time_12 = System.nanoTime();
		cht_g_10000.addAll(strings);
		int c12 = cht_g_10000.getCollisions();
		long total_time_12 = System.nanoTime() - start_time_12;
		writer.println("addAll,"+"good,"+"10000,"+total_time_12+","+c12);
		
		long start_time_13 = System.nanoTime();
		cht_b_100000.addAll(strings);
		int c13 = cht_b_100000.getCollisions();
		long total_time_13 = System.nanoTime() - start_time_13;
		writer.println("addAll,"+"bad,"+"100000,"+total_time_13+","+c13);
		
		long start_time_14 = System.nanoTime();
		cht_m_100000.addAll(strings);
		int c14 = cht_m_100000.getCollisions();
		long total_time_14 = System.nanoTime() - start_time_14;
		writer.println("addAll,"+"med,"+"100000,"+total_time_14+","+c14);
		
		long start_time_15 = System.nanoTime();
		cht_g_100000.addAll(strings);
		int c15 = cht_g_100000.getCollisions();
		long total_time_15 = System.nanoTime() - start_time_15;
		writer.println("addAll,"+"good,"+"100000,"+total_time_15+","+c15);
		
		writer.close();
	}

}
