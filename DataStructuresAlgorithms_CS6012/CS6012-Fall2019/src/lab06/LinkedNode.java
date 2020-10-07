package lab06;

public class LinkedNode<E> {
	@SuppressWarnings("rawtypes")
	LinkedNode next;
	@SuppressWarnings("rawtypes")
	LinkedNode previous;
	E object;
	
	//root node constructor
	public LinkedNode(E element) {
		next = null;
		previous = null;
		object = element;
	}
	
	@SuppressWarnings("rawtypes")
	public LinkedNode(E element, LinkedNode next, LinkedNode previous) {
		this.next = next;
		this.previous = previous;
		this.object = element;
	}
	
	@SuppressWarnings("rawtypes")
	public LinkedNode getNext() {
		return next;
	}
	
	@SuppressWarnings({ "rawtypes" })
	public void setNext(LinkedNode l) {
		next = l;
	}
	
	@SuppressWarnings("rawtypes")
	public LinkedNode getPrevious() {
		return previous;
	}
	
	@SuppressWarnings("rawtypes")
	public void setPrevious(LinkedNode l) {
		previous = l;
	}
	
	public E getObject() {
		return object;
	}
	

}
