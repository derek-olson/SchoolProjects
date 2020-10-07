package assignment06;

import java.util.ArrayList;
import java.util.Arrays;

public class QuadProbingTests {

	public static void main(String[] args) {
		/**
		 * Initialize new hash functors
		 */
		MediocreHashFunctor mhf = new MediocreHashFunctor();
		
		/**
		 * Initialize new chaining hash table
		 */
		QuadProbeHashTable cht = new QuadProbeHashTable(10, mhf);
		
		/**
		 * Add string to the chaining hash table and check the add method with other methods
		 */
		cht.add("test");
		if(cht.size() != 1) {
			System.err.println("ERROR TEST 1: Check the add method, size should be 1 but is "+cht.size());
		}
		if(cht.isEmpty()) {
			System.err.println("ERROR TEST 2: Check the add method or isEmpty method. The set is empty but should have 1");
		}
		if(!cht.contains("test")) {
			System.err.println("ERROR TEST 3: Chek the add method or contains method. The set should contain test, but does not");
		}
		
		/**
		 * Check the remove function with other methods
		 */
		cht.remove("test");
		if(cht.size() != 0) {
			System.err.println("ERROR TEST 4: Check the remove method, size should be 0");
		}
		if(!cht.isEmpty()) {
			System.err.println("ERROR TEST 5: Check the remove method or isEmpty method. Should be empty, but is not");
		}
		if(cht.contains("test")) {
			System.err.println("ERROR TEST 6: Chek the remove method or contains method. Should not contain test, but does.");
		}
		
		/**
		 * Add strings to the chaining hash table and check the add all method with other methods
		 */
		ArrayList<String> al = new ArrayList<String>(Arrays.asList("apple", "Bank", "Cattle", "cobwebs","drive", "teacher", "pie", "dogs", "syrup", "whale", "garbage", "front", "weather", "Snow", "rare", "park", "quite", "cats"));
		cht.addAll(al);
		if(cht.size() != 18) {
			System.err.println("ERROR TEST 7: Check the add method, size should be 1 but is "+cht.size());
		}
		if(cht.isEmpty()) {
			System.err.println("ERROR TEST 8: Check the add method or isEmpty method. The set is empty but should have 1");
		}
		if(!cht.containsAll(al)) {
			System.err.println("ERROR TEST 9: Check the add method or contains method. The set should contain test, but does not");
		}
		
		/**
		 * Check the remove all function with other methods
		 */
		cht.removeAll(al);
		if(cht.size() != 0) {
			System.err.println("ERROR TEST 10: Check the remove method, size should be 0");
		}
		if(!cht.isEmpty()) {
			System.err.println("ERROR TEST 11: Check the remove method or isEmpty method. Should be empty, but is not");
		}
		if(cht.containsAll(al)) {
			System.err.println("ERROR TEST 12: Chek the remove method or contains method. Should not contain test, but does.");
		}

	}

}
