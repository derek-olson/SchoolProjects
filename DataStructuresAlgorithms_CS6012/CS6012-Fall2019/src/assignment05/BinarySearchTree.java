package assignment05;

import java.util.ArrayList;
import java.util.Collection;
import java.util.NoSuchElementException;


public class BinarySearchTree<T extends Comparable<? super T>> implements SortedSet<T> {
	private int size;
	public BinarySearchNode<T> root; 
	
	/**
	 * Constructor
	 */
	public BinarySearchTree() {
		size = 0;
		root = null;
	}
	
	  /**
	   * Ensures that this set contains the specified item.
	   * 
	   * @param item
	   *          - the item whose presence is ensured in this set
	   * @return true if this set changed as a result of this method call (that is, if
	   *         the input item was actually inserted); otherwise, returns false
	   * @throws NullPointerException
	   *           if the item is null
	   */
	@Override
	public boolean add(T item) {
		if(root == null) {
			root = new BinarySearchNode<T>(item);
			size++;
			return true;
		}
		if(contains(item)) {
			return false;
		}
		else {
			addRecursive(item, root);
			return true;
		}
	}
	
	/**
	 * Helper function to add items to the BST
	 * @param item - the item to add to the BST
	 * @param node - the node to begin search from
	 */
	private void addRecursive(T item, BinarySearchNode<T> node) {
		if(node.data.compareTo(item) > 0){
			if(node.left == null) {
				node.left = new BinarySearchNode<T>(item);
				size++;
			}
			else {
				addRecursive(item, node.left);
			}
		}
		else {
			if(node.right == null) {
				node.right = new BinarySearchNode<T>(item);
				size++;
			}
			else {
				addRecursive(item, node.right);
				}
			}
		}

	  /**
	   * Ensures that this set contains all items in the specified collection.
	   * 
	   * @param items
	   *          - the collection of items whose presence is ensured in this set
	   * @return true if this set changed as a result of this method call (that is, if
	   *         any item in the input collection was actually inserted); otherwise,
	   *         returns false
	   * @throws NullPointerException
	   *           if any of the items is null
	   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public boolean addAll(Collection<? extends T>  items) {
		for (int i = 0; i < items.size(); i++) {
			add((T) ((ArrayList) items).get(i));
		}
		return false;
	}

	  /**
	   * Determines if there is an item in this set that is equal to the specified
	   * item.
	   * 
	   * @param item
	   *          - the item sought in this set
	   * @return true if there is an item in this set that is equal to the input item;
	   *         otherwise, returns false
	   * @throws NullPointerException
	   *           if the item is null
	   */
	@Override
	public boolean contains(T item) {
		if (item == null) {
			throw new NullPointerException();
		}
		if (binarySearch(item, root)) {
			return true;
		}
		return false;
	}

	/**
	 * Helper function to search for an item
	 * @param item - the item to search for
	 * @param node - the node to begin searching from
	 * @return - returns true if item is found
	 */
	private boolean binarySearch(T item, BinarySearchNode<T> node) {
		if(node == null) {
			return false;
		}
		else if (node.data.compareTo(item) == 0) {
			return true;
		}
		else if(node.data.compareTo(item) > 0) {
			return binarySearch(item, node.left);
			
		}
		else {
			return binarySearch(item, node.right);
		}
		
	}
	
	  /**
	   * Determines if for each item in the specified collection, there is an item in
	   * this set that is equal to it.
	   * 
	   * @param items
	   *          - the collection of items sought in this set
	   * @return true if for each item in the specified collection, there is an item
	   *         in this set that is equal to it; otherwise, returns false
	   * @throws NullPointerException
	   *           if any of the items is null
	   */
	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Override
	public boolean containsAll(Collection<? extends T> items) {
		for(int i=0; i<items.size(); i++) {
			if(!contains((T) ((ArrayList) items).get(i))){
				return false;
			}
		}
		return true;
	}
	 /**
	   * Returns the first (i.e., smallest) item in this set.
	   * 
	   * @throws NoSuchElementException
	   *           if the set is empty
	   */
	@Override
	public T first() throws NoSuchElementException {
		return getFirst(root);
	}

	@Override
	public T last() throws NoSuchElementException {
		return getLast(root);
	}
	/**
	 * Helper method to find the minimum element 
	 * @param node The node to start searching from
	 * @return The data to return from the node
	 */
	private T getFirst(BinarySearchNode<T> node) {
		if(node == null) {
			throw new NoSuchElementException();
		}
		if(node.left == null) {
			return (T) node.getObject();
		}
		return getFirst(node.left);
	}
	
	/**
	 * Helper method to find the maximum element
	 * @param node - The node to start searching from
	 * @return - Returns the data element of the max value
	 */
	private T getLast(BinarySearchNode<T> node) {
		if(node == null) {
			throw new NoSuchElementException();
		}
		if(node.right == null) {
			return (T) node.getObject();
		}
		return getLast(node.right);
	}

	 /**
	   * Ensures that this set does not contain the specified item.
	   * 
	   * @param item
	   *          - the item whose absence is ensured in this set
	   * @return true if this set changed as a result of this method call (that is, if
	   *         the input item was actually removed); otherwise, returns false
	   * @throws NullPointerException
	   *           if the item is null
	   */
	@Override
	public boolean remove(T item) {
		if(item == null) {
			return false;
		}
		if(!contains(item)) {
			return false;
		}
		replace(item, root);
		
		return true;
	}
	/**
	 * Helper function to replace the node corresponding to the item of interest
	 * @param item - The item to be replaced
	 * @param node - The node to begin searching from
	 */
	private void replace(T item, BinarySearchNode<T> node) {
		if(root.data.compareTo(item) == 0) {
			replaceRoot(item);
		}
		if(node.right != null && node.right.data.compareTo(item) == 0) {
			if(node.right.right == null && node.right.left == null) {
				node.right = null;
				size--;
				return;
			}
			else if(node.right.right == null) {
				node.right = node.right.left;
				size--;
				return;
			}
			else if(node.right.left == null) {
				node.right = node.right.right;
				size--;
				return;
			}
			else if(node.right.right != null && node.right.left != null) {
				BinarySearchNode<T> rightNode = node.right.right;
				node.right = new BinarySearchNode<T>(getFirst(rightNode), node.right.right, node.right.left);
				delete(item, rightNode);
				return;
			}
		}
		else if(node.right != null && node.left.data.compareTo(item) == 0) {
			if(node.left.right == null && node.left.left == null) {
				node.left = null;
				size--;
				return;
			}
			else if(node.left.right == null) {
				node.left = node.left.left;
				size--;
				return;
			}
			else if(node.left.left == null) {
				node.left = node.left.right;
				size--;
				return;
			}
			else if(node.left.right != null && node.left.left != null) {
				BinarySearchNode<T> rightNode = node.left.right;
				node.left = new BinarySearchNode<T>(getFirst(rightNode), node.right.right, node.right.left);
				delete(item, rightNode);
				return;
			}
		}
		else if (node.data.compareTo(item) > 0) {
			replace(item, node.left);
		}
		else if (node.data.compareTo(item) < 0) {
			replace(item, node.right);
		}
	}
	
	/**
	 * Helper function to delete the successor node
	 * @param item - the item to be deleted
	 * @param node - the node to begin searching from
	 */
	private void delete(T item, BinarySearchNode<T> node) {
		if(node.left.data.compareTo(item) == 0) {
			node.left = null;
			return;
		}
		delete(item, node.left);
	}
	
	/**
	 * Helper function to replace the root node
	 * @param item - The item to replace the root with
	 */
	private void replaceRoot(T item) {
		if(root.left == null && root.right == null) {
			root = new BinarySearchNode<T>(item);
		}
		else if(root.right == null) {
			root = root.left;
		}
		else if(root.right == null) {
			root = root.right;
		}else {
			T toDelete = getFirst(root.right);
			root = new BinarySearchNode<T>(toDelete, root.left, root.right);
			delete(toDelete, root.right);
		}
	}

	  /**
	   * Ensures that this set does not contain any of the items in the specified
	   * collection.
	   * 
	   * @param items
	   *          - the collection of items whose absence is ensured in this set
	   * @return true if this set changed as a result of this method call (that is, if
	   *         any item in the input collection was actually removed); otherwise,
	   *         returns false
	   * @throws NullPointerException
	   *           if any of the items is null
	   */
	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Override
	public boolean removeAll(Collection items) {
		for(int i=0; i<items.size(); i++) {
			if(((ArrayList<T>) items).get(i) == null) {
				throw new NullPointerException();
			}
			else {
				remove((T)((ArrayList<T>) items).get(i));
			}
		}
		return false;
	}

	  /**
	   * Removes all items from this set. The set will be empty after this method
	   * call.
	   */
	@Override
	public void clear() {
		root.left = null;
		root.right = null;
		root = null;
		size = 0;
	}

	 /**
	   * Returns true if this set contains no items.
	   */
	@Override
	public boolean isEmpty() {
		if(this.size > 0) {
			return false;
		}
		return true;
	}

	/**
	 * Returns the number of nodes in the tree
	 */
	@Override
	public int size() {
		return this.size;
	}

	/**
	 * Converts the binary search tree to an array in order
	 * @return - returns the in order array
	 */
	@Override
	public ArrayList<T> toArrayList() {
		ArrayList<T> arr = new ArrayList<T>();
		addToArray(root, arr);
		return arr;
	}
	
	/**
	 * Helper function to to fill an array in order
	 * @param node - the node to begin filling the array from
	 * @param arr - The array to fill
	 */
	private void addToArray(BinarySearchNode<T> node, ArrayList<T> arr) {
		if(node == null) {return;}
		addToArray(node.left, arr);
		arr.add(node.getObject());
		addToArray(node.right, arr);
	}
	
	/**
	 * Private class for node objects
	 * @author derekolson
	 *
	 * @param <T>
	 */
	private class BinarySearchNode<T extends Comparable<? super T>> {
		BinarySearchNode<T> left;
		BinarySearchNode<T> right;
		T data;
		
		//root node constructor
		private BinarySearchNode(T element) {
			left = null;
			right = null;
			data = element;
		}
		// second constructor that allows the left and right pointers to be set
		private BinarySearchNode(T element, BinarySearchNode<T> left, BinarySearchNode<T> right) {
			this.left = left;
			this.right = right;
			this.data = element;
		}
		// Method to return the data in the node
		public T getObject() {
			return data;
		}

	}

}

