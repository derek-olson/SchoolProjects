package assignment06;

import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;


public class ChainingHashTable implements Set<String> {
	private LinkedList<String>[] storage;
	private int size;
	private int capacity;
	HashFunctor functor;
	private int collisions;
	
	@SuppressWarnings("unchecked")
	public ChainingHashTable(int capacity, HashFunctor functor) {
		storage = (LinkedList<String>[]) new LinkedList[capacity];
		this.functor = functor;
		this.capacity = capacity;
	}

	/**
	   * Ensures that this set contains the specified item.
	   * 
	   * @param item
	   *          - the item whose presence is ensured in this set
	   * @return true if this set changed as a result of this method call (that is, if
	   *         the input item was actually inserted); otherwise, returns false
	   */
	  public boolean add(String item) {
		  if(contains(item)) {
			  return false;
		  }
		  int index = functor.hash(item)%capacity;
		  if(storage[index] == null) {
			  LinkedList ll = new LinkedList();
			  storage[index] = ll;
			  return true;
		  }
		  storage[index].add(item);
		  size++;
		  collisions++;
		  return true;
	  }

	  /**
	   * Ensures that this set contains all items in the specified collection.
	   * 
	   * @param items
	   *          - the collection of items whose presence is ensured in this set
	   * @return true if this set changed as a result of this method call (that is, if
	   *         any item in the input collection was actually inserted); otherwise,
	   *         returns false
	   */
	  public boolean addAll(Collection<? extends String> items) {
		  for(String item : items) {
			  if(item == null) {
				  return false;
			  }
			  add(item);
		  }
		  return true;
	  }

	  /**
	   * Removes all items from this set. The set will be empty after this method
	   * call.
	   */
	  public void clear() {
		  for(LinkedList ll : storage) {
			  ll.clear();
		  }
		  size = 0;
	  }

	  /**
	   * Determines if there is an item in this set that is equal to the specified
	   * item.
	   * 
	   * @param item
	   *          - the item sought in this set
	   * @return true if there is an item in this set that is equal to the input item;
	   *         otherwise, returns false
	   */
	  public boolean contains(String item) {
		  int index = functor.hash(item)%capacity;
		  if(storage[index] == null) {
			  return false;
		  }
		  else if(storage[index].contains(item)) {
			  return true;
		  }
		  else{
			  return false;
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
	   */

	  public boolean containsAll(Collection<? extends String> items) {
		  for(String item : items) {
			 if(!contains(item)) {
				 return false;
			 }
		  }
		  return true;
	  }

	  /**
	   * Returns true if this set contains no items.
	   */
	  public boolean isEmpty() {
		  if(size > 0) {
			  return false;
		  }
		  return true;
	  }

	  /**
	   * Ensures that this set does not contain the specified item.
	   * 
	   * @param item
	   *          - the item whose absence is ensured in this set
	   * @return true if this set changed as a result of this method call (that is, if
	   *         the input item was actually removed); otherwise, returns false
	   */
	  public boolean remove(String item) {
		  if(!contains(item)) {
			  return false;
		  }
		  int index = functor.hash(item)%capacity;
		  storage[index].remove(item);
		  size--;
		  return true;
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
	   */
	  public boolean removeAll(Collection<? extends String> items) {
		  for(String item : items) {
			  if(!contains(item)) {
				  return false;
			  }
			  remove(item);
		  }
		  return true;
	  }

	  /**
	   * Returns the number of items in this set.
	   */
	  public int size(){
		  return size;
	  }
	  
	  public int listSize(int index) {
		  if(!(storage[index]  == null)){
			  if(storage[index].size() <= 1) {
				  return 0;
			  }
			  return storage[index].size()-1;
		  }
		  return 0;
	  }
	  
	  public int getCollisions() {
		  return collisions;
	  }
}
