package lab06;

import java.util.Iterator;
import java.util.NoSuchElementException;


public class DoublyLinkedList<E> implements List<E>, Iterable<E> {
	int size;      
    @SuppressWarnings({ "rawtypes" })
	LinkedNode head;     
    @SuppressWarnings({ "rawtypes" })
	LinkedNode tail;    

	public DoublyLinkedList() {
		head = null;
		tail = null;
		size = 0;
	}
	
  /**
   * Inserts the specified element at the beginning of the list. O(1) for a
   * doubly-linked list.
   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public void addFirst(Object element) {
        if (isEmpty()) {
            head = new LinkedNode(element);
            tail = head;
		}
        else {
        	LinkedNode temp = head;
            head = new LinkedNode(element, temp, null);
            head.next.previous = head;
            
        }
        size++;
	}
	
  /**
   * Inserts the specified element at the end of the list. O(1) for a
   * doubly-linked list.
   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public void addLast(Object o) {
        if (isEmpty()) {
            head = new LinkedNode(o);
            tail = head;
        }
        else {
        	LinkedNode temp = tail;
            tail = new LinkedNode(o, null, temp);
            tail.previous.next = tail;
        }
        size++;
	}
	
	/**
   * Inserts the specified element at the specified position in the list. Throws
   * IndexOutOfBoundsException if index is out of range (index < 0 || index >
   * size()) O(N) for a doubly-linked list.
   */

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Override
	public void add(int index, Object element) throws IndexOutOfBoundsException {
		if(index < 0 || index >= size) {
			throw new IndexOutOfBoundsException("Out of Bounds");
		}
		if(index == 0) {
			addFirst(element);
		}
		LinkedNode current = head;

		for (int i = 0; i < index; i++) {
			current = current.next;
		}
		LinkedNode toBeAdded = new LinkedNode(element, current, current.previous);
		
		current.previous.next = toBeAdded;
		current.previous = toBeAdded;
		
		size++;
	}
	
  /**
   * Returns the first element in the list. Throws NoSuchElementException if the
   * list is empty. O(1) for a doubly-linked list.
   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public E getFirst() throws NoSuchElementException {
		if(isEmpty()) {
			throw new NoSuchElementException("Element not found");
		}
		LinkedNode toGet = head;
		E toReturn = (E) toGet.getObject();
		return (E) toReturn;
	}

   /**
   * Returns the last element in the list. Throws NoSuchElementException if the
   * list is empty. O(1) for a doubly-linked list.
   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public E getLast() throws NoSuchElementException {
		if(isEmpty()) {
			throw new NoSuchElementException("Element not found");
		}
		LinkedNode toGet = tail;
		E toReturn = (E) toGet.getObject();
		return (E) toReturn;
	}

  /**
   * Returns the element at the specified position in the list. Throws
   * IndexOutOfBoundsException if index is out of range (index < 0 || index >=
   * size()) O(N) for a doubly-linked list.
   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public E get(int index) throws IndexOutOfBoundsException {
		if(index >= size || index < 0) {
			throw new IndexOutOfBoundsException("Out of bounds Exception");
		}
		LinkedNode findPrevious = head;
		for (int i = 0; i < index -1; i++) {
			findPrevious.getNext();
		}
		LinkedNode toGet = findPrevious.next;
		E toReturn = (E) toGet.getObject();
		return toReturn;
	}

  /**
   * Removes and returns the first element from the list. Throws
   * NoSuchElementException if the list is empty. O(1) for a doubly-linked list.
   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public E removeFirst() throws NoSuchElementException {
		if(isEmpty()) {
			throw new NoSuchElementException("Element not found");
		}
		LinkedNode toReturn = head;
		head = toReturn.next;
		head.previous = null;
		size--;
		return (E) toReturn;
	}

   /**
   * Removes and returns the last element from the list. Throws
   * NoSuchElementException if the list is empty. O(1) for a doubly-linked list.
   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public E removeLast() throws NoSuchElementException {
		if(isEmpty()) {
			throw new NoSuchElementException("Element not found");
		}
		LinkedNode toReturn = tail;
		tail = toReturn.previous;
		tail.next = null;
		size--;
		return (E) toReturn;
	}

   /**
   * Removes and returns the element at the specified position in the list. Throws
   * IndexOutOfBoundsException if index is out of range (index < 0 || index >=
   * size()) O(N) for a doubly-linked list.
   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public E remove(int index) throws IndexOutOfBoundsException {
		LinkedNode current = head;
		if(index == 0) {
			removeFirst();
		}
		else if(index == size-1) {
			removeLast();
		}
		else if(index >= size || index < 0) {
			throw new IndexOutOfBoundsException("Out of bounds Exception");
		}else {
			for (int i = 0; i < index; i++) {
				current = current.next;
			}
			current.previous.next = current.next;
			current.next.previous = current.previous;
		}
		
		size--;
		
		return (E) current;
	}
	
  /**
   * Returns the index of the first occurrence of the specified element in the
   * list, or -1 if this list does not contain the element. O(N) for a
   * doubly-linked list.
   */
	@SuppressWarnings("rawtypes")
	@Override
	public int indexOf(Object element) {
		LinkedNode current = head;
		for(int i = 0; i < size; i++) {
			if(current.getObject() == element) {
				return i;
			}
			current = current.next;
		}
		return -1;
	}

   /**
   * Returns the index of the last occurrence of the specified element in this
   * list, or -1 if this list does not contain the element. O(N) for a
   * doubly-linked list.
   */
	@SuppressWarnings("rawtypes")
	@Override
	public int lastIndexOf(Object element) {
		LinkedNode current = tail;
		for(int i = size-1; i >= 0; i--) {
			if(current.getObject() == element) {
				return i;
			}
			current = current.previous;
		}
		return -1;
	}

	/**
   * Returns the number of elements in this list. O(1) for a doubly-linked list.
   */
	@Override
	public int size() {
		return size;
	}

   /**
   * Returns true if this collection contains no elements. O(1) for a
   * doubly-linked list.
   */
	@Override
	public boolean isEmpty() {
		if(this.size > 0) {
			return false;
		}
		return true;
	}

   /**
   * Removes all of the elements from this list. O(1) for a doubly-linked list.
   */
	@Override
	public void clear() {
		head = null;
		tail = null;
		size = 0;
	}

  /**
   * Returns an array containing all of the elements in this list in proper
   * sequence (from first to last element). O(N) for a doubly-linked list.
   */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@Override
	public E[] toArray() {
		LinkedNode toIncrement = head;
		E[] array = (E[])new Object[size];
		for (int i = 0; i < size; i++) {
			array[i] = (E) toIncrement.getNext();
		}
		return array;
	}

	/**
	 * Returns an iterator.
	 */
	@SuppressWarnings("unchecked")
	@Override
	public Iterator<E> iterator() {
		return new DataSetIterator();
	}
	
	/**
	 * @return an iterator that determines if collection has next and returns the next
	 */
	@SuppressWarnings("rawtypes")
	private class DataSetIterator implements Iterator {
        private int position = 0;
 
        public boolean hasNext() {
            if (position < size)
                return true;
            else
                return false;
        }
 
        public E next() {
            if (this.hasNext())
                return next();
            else
                return null;
        }
 
        @Override
        public void remove() {
        	this.remove();
        	size--;
        }
    }

}
