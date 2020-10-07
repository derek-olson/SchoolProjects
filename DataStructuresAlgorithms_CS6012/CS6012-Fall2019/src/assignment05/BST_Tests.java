package assignment05;

import java.util.ArrayList;
import java.util.Arrays;

public class BST_Tests {

	public static void main(String[] args) {
		BinarySearchTree<Integer> ints = new BinarySearchTree<Integer>();
		
		/**
		 * test adding all to the bst
		 */
		ArrayList<Integer> toAdd = new ArrayList<>(Arrays.asList(30, 25, 29, 32, 31, 10, 50, 5, 12, 21));
		ints.addAll(toAdd);
		
		/**
		 * test the to array method
		 */
		ArrayList<Integer> arr = ints.toArrayList();
		System.out.println(arr);

		/**
		 * test the remove method
		 */
		ints.remove(29);
		ArrayList<Integer> arr2 = ints.toArrayList();
		System.out.println(arr2);
		
		/**
		 * test removing the root
		 */
		ints.remove(30);
		ArrayList<Integer> arr3 = ints.toArrayList();
		System.out.println(arr3);
		
		/**
		 * test remove all function
		 */
		ArrayList<Integer> toRemove = new ArrayList<>(Arrays.asList(32, 10, 50, 5, 12));
		ints.removeAll(toRemove);
		ArrayList<Integer> arr4 = ints.toArrayList();
		System.out.println(arr4);
		
		/**
		 * test clear, size, and isEmpty functions
		 */
		ints.clear();
		ArrayList<Integer> arr5 = ints.toArrayList();
		System.out.println(arr5);
		if(!ints.isEmpty()) {
			System.err.println("ERROR: Clear function malfunction - isEmpty");
		}
		if(ints.size() != 0) {
			System.err.println("ERROR: Clear function malfunction- size");
		}
		
		/**
		 * test get first and get last functions
		 */
		ints.addAll(toAdd);
		if(ints.first() != 5) {
			System.err.println("ERROR: first function");
		}
		if(ints.last() != 50) {
			System.err.println("ERROR: last function - "+ints.last());
		}
	}

}
