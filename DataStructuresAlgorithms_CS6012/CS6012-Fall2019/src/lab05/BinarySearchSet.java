package lab05;

import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * A set that provides a total ordering on its elements. The elements are
 * ordered using their natural ordering (i.e., using compareTo() from the
 * Comparable interface), or by a Comparator provided at sorted set creation
 * time. Thus, all elements inserted into a sorted set must implement the
 * Comparable interface or be accepted by the specified Comparator. The set's
 * iterator will traverse the set in ascending element order.
 * 
 * @param <E>
 *          the type of elements maintained by this set
 */


public class BinarySearchSet<E> implements SortedSet<E>, Iterable<E> {
	public E[] searchSet;
	public int setLength;
	public int numberOfItemsInSet;
	Comparator<E> comparator;
	
	@SuppressWarnings("unchecked")
	public BinarySearchSet() {
		searchSet = (E[])new Object[1000];
		setLength = 1000;
		numberOfItemsInSet = 0;
		comparator = (Comparator<E>) Comparator.naturalOrder();
	}
	
	@SuppressWarnings("unchecked")
	public BinarySearchSet(Comparator<? super E> comparator) {
		this.comparator = (Comparator<E>) comparator;
		searchSet = (E[])new Object[1000];
		setLength = 1000;
		numberOfItemsInSet = 0;
	}

	/**
	 * @return The comparator used to order the elements in this set, or null if
	 *         this set uses the natural ordering of its elements (i.e., uses
	 *         Comparable).
	 */
	@Override
	public Comparator<? super E> comparator() {
		return this.comparator;
	}

	/**
	 * @return the first (lowest, smallest) element currently in this set
	 * @throws NoSuchElementException if the set is empty
	 */
	@Override
	public E first() throws NoSuchElementException {
		if(numberOfItemsInSet == 0) {
			throw new NoSuchElementException();
		}
		return searchSet[0];
	}

	/**
	 * @return the last (highest, largest) element currently in this set
	 * @throws NoSuchElementException if the set is empty
	 */
	@Override
	public E last() throws NoSuchElementException {
		if(numberOfItemsInSet == 0) {
			throw new NoSuchElementException();
		}
		return searchSet[numberOfItemsInSet-1];
	}
	
	public int binarySearch(E target, int start, int end) {
		int mid = (start+end)/2;
			if(start > end) {return -1;}
			if(comparator.compare(target, this.searchSet[mid]) < 0) {
				return binarySearch(target, start, mid-1);
			}
			if(comparator.compare(target, this.searchSet[mid]) > 0) {
				return binarySearch(target, mid+1, end);
			}
			if(comparator.compare(target, this.searchSet[mid]) == 0) {
				return mid;
			}
		return mid;
	}
	
	public boolean binarySearchBool(E target, int start, int end) {
		int mid = (start+end)/2;
		if(start > end) {return false;}

		if(comparator.compare(target, this.searchSet[mid]) < 0) {
			return binarySearchBool(target, start, mid-1);
		}
		if(comparator.compare(target, this.searchSet[mid]) > 0) {
			return binarySearchBool(target, mid+1, end);
		}
		if(comparator.compare(target, this.searchSet[mid]) == 0) {
			return true;
		}
		return false;
	}
	
	//a method used for adding items to set for simple program tests.
	@SuppressWarnings("unchecked")
	public void testAdd() {
		E[] testArray = (E[])new Object[] {0,1,2,3,4,5,6,7,8,9};
		for (int i = 0; i < 10; i++) {
			this.searchSet[i] = testArray[i];
		}
	}
		
	/**
	 * Adds the specified element to this set if it is not already present and
	 * not set to null.
	 * 
	 * @param o element to be added to this set
	 * @return true if this set did not already contain the specified element
	 */

	@Override
	public boolean add(E element) {
		//if the set is empty just add the element to the first index. Return true.
		if (numberOfItemsInSet == 0) {
			searchSet[0] = element;
			numberOfItemsInSet = 1;
			return true;
		}
		//check to see if element is duplicate. If it is return false.
		if (this.contains(element)) {
			return false;
		}
		//check the current size of the set and increase it if necessary
		increaseSize();
		//if the element is not already in the set add it to the correct location and return true.
		insertElement(element);
		numberOfItemsInSet += 1;
		
		return true;
	}
	
	// compare items in the set
	private void insertElement(E element) {
		int i;
		for (i = numberOfItemsInSet - 1; (i >= 0 && comparator.compare(searchSet[i], element) > 0); i--) { 
	    	searchSet[i + 1] = searchSet[i]; 
		}
	    searchSet[i + 1] = element; 
	}
	
	//if the set size and the number of items are equal than double the size
	private void increaseSize() {
		if(numberOfItemsInSet == setLength) {
			@SuppressWarnings("unchecked")
			E[] temp = (E[])new Object[setLength*1000];
			for (int i = 0; i < setLength; i++){
				temp[i] = searchSet[i];
			}
			searchSet = temp;
		}
	}

	/**
	 * Adds all of the elements in the specified collection to this set if they
	 * are not already present and not set to null.
	 * 
	 * @param c collection containing elements to be added to this set
	 * @return true if this set changed as a result of the call
	 */
	
	@Override
	public boolean addAll(Collection<? extends E> elements) {
		int s = numberOfItemsInSet;
		for(E e : elements){
			this.add(e);
		}
		if(s == numberOfItemsInSet) {
			return false;
		}
		return true;
	}
	
	/**
	 * Removes all of the elements from this set. The set will be empty after
	 * this call returns.
	 */
	
	@Override
	public void clear() {
		for(int i = 0; i < numberOfItemsInSet; i++){
			searchSet[i] = null;
		}
		numberOfItemsInSet = 0;
	}

	/**
	 * @param o element whose presence in this set is to be tested
	 * @return true if this set contains the specified element
	 */
	
	@SuppressWarnings("unchecked")
	@Override
	public boolean contains(Object element) {
		if (binarySearchBool((E) element, 0, numberOfItemsInSet-1)) {
			return true;
		}
		return false;
	}

	/**
	 * @param c collection to be checked for containment in this set
	 * @return true if this set contains all of the elements of the specified
	 *         collection
	 */
	
	@Override
	public boolean containsAll(Collection<?> elements) {
		for(Object e : elements){
			if(!this.contains(e)) {
				return false;
			}
		}
		return true;
	}

	/**
	 * @return true if this set contains no elements and false if elements are present
	 */
	
	@Override
	public boolean isEmpty() {
		for(int i = 0; i < numberOfItemsInSet; i++){
			if(searchSet[i] != null){
				return false;
			}
		}
		return true;
	}
	
	/**
	 * @return an iterator over the elements in this set, where the elements are
	 *         returned in sorted (ascending) order
	 */

	@SuppressWarnings("unchecked")
	@Override
	public Iterator<E> iterator() {
		return new DataSetIterator();
	}

	/**
	 * Removes the specified element from this set if it is present.
	 * 
	 * @param o object to be removed from this set, if present
	 * @return true if this set contained the specified element
	 */
	
	@SuppressWarnings({ "unchecked" })
	@Override
	public boolean remove(Object element) {
		if(!contains(element)) {
			return false;
		}
		int index = this.binarySearch((E) element, 0, numberOfItemsInSet);
		if (index == numberOfItemsInSet-1) {
			searchSet[index] = null;
			numberOfItemsInSet--;
			return true;
		}
		else {
			for (int i = index; i < numberOfItemsInSet-1; i++) { 
		    	searchSet[i] = searchSet[i+1]; 
			}
			numberOfItemsInSet--;
		}
		return true;
	}
	
	/**
	 * Removes from this set all of its elements that are contained in the
	 * specified collection.
	 * 
	 * @param c collection containing elements to be removed from this set
	 * @return true if this set changed as a result of the call
	 */

	@Override
	public boolean removeAll(Collection<?> elements) {
		for(Object e : elements){
			this.remove(e);
		}
		return true;
	}
	
	/**
	 * @return the number of elements in this set
	 */
	@Override
	public int size() {
		return numberOfItemsInSet;
	}
	
	/**
	 * @return an array containing all of the elements in this set, in sorted
	 *         (ascending) order.
	 */
	@Override
	public Object[] toArray() {
		Object[] outArray = new Object[numberOfItemsInSet];
		for(int i = 0; i < numberOfItemsInSet; i++){
			outArray[i] = searchSet[i];
		}
		return outArray;
	}
	
	/**
	 * @return an iterator that determines if collection has next and returns the next
	 */
	
	@SuppressWarnings("rawtypes")
	private class DataSetIterator implements Iterator {
        private int position = 0;
        private boolean canRemove = false;
 
        @Override
        public boolean hasNext() {
            if (position < numberOfItemsInSet)
                return true;
            else
                return false;
        }
        @Override
        public E next() {
            if (this.hasNext()) {
            	canRemove = true;
                return searchSet[position++];
            }
            else {
                return null;
            }
        }
 
        @Override
        public void remove() {
        	if(!canRemove) {
        		throw new IllegalStateException();
        	}
        	canRemove = false;
        	BinarySearchSet.this.remove(searchSet[position-1]);
        	position -= 1;
        }
    }

}
