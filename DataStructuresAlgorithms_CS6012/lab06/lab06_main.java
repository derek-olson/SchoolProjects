package lab06;

public class lab06_main {

	@SuppressWarnings({ "rawtypes", "unchecked" })
	public static void main(String[] args) {
		
		// initialize a new doubly linked list
		DoublyLinkedList dll = new DoublyLinkedList();
		
		//make sure it is empty
		if (dll.isEmpty()) {
			System.out.println("True");
			}
		else {
			System.err.println("FALSE");
			}

		
		// add a node to the list
		dll.addFirst(1);
		System.out.println("SIZE 1: "+dll.size());
		
		//make sure the size is correct and the size method works
		if (dll.size() == 1) {
			System.out.println("True");
			}
		else {
			System.err.println("FALSE");
			}
		
		//add a node to the tail
		dll.addLast(2);
		System.out.println("SIZE 2: "+dll.size());
		
		//make sure the size is correct and the size method works
		if (dll.size() == 2) {
			System.out.println("True");
			}
		else {
			System.err.println("FALSE");
			}
		
		//check the getFirst method
		LinkedNode first = (LinkedNode) dll.getFirst();
		System.out.println("FIRST: "+first.getObject());
		
		//check the getLast method
		LinkedNode last = (LinkedNode) dll.getLast();
		System.out.println("LAST: "+last.getObject());
		
		
		//test the add and get methods
		dll.add(1, 3);
		if (dll.size() != 3) {
			System.err.println("FALSE: Error with add method");
		}
		int getTest = (int) dll.get(1);
		if (getTest != 3) {
			System.err.println("FALSE: Error with get method");
		}
		

		//test the remove first method
		LinkedNode returnFirst = (LinkedNode) dll.removeFirst();
		int toPrint = (int) returnFirst.getObject();
		System.out.println("first return: "+toPrint);
		if((int) returnFirst.getObject() != 1) {
			System.err.println("FALSE: Error with remove first method");
		}
		
		//test the remove last method
		LinkedNode returnLast = (LinkedNode) dll.removeLast();
		int toPrint2= (int) returnLast.getObject();
		System.out.println("last return: "+toPrint2);
		if((int) returnLast.getObject() != 2) {
			System.err.println("FALSE: Error with remove last method");
		}
		
		// test if size updated correctly
		if(dll.size != 1) {
			System.err.println("Error: Incorrect Size");
		}
		
		//test remove
		dll.addFirst(1);
		dll.addFirst(2);
		LinkedNode remove = (LinkedNode) dll.remove(1);
		System.out.println("here: "+ remove.getObject());
		if((int) remove.getObject() != 1) {
			System.err.println("FALSE: Error with remove method");
		}
		
		System.out.println("Size after remove: "+dll.size);
		
		//test index of
		int indexof = dll.indexOf(2);
		System.out.println("index of: "+indexof);
		if(indexof != 0) {
			System.err.println("FALSE: Error with index of method");
		}
		
		//test last index of
		dll.addFirst(3);
		int lastindexof = dll.lastIndexOf(3);
		System.out.println("last index of: "+lastindexof);
		if(lastindexof != 2) {
			System.err.println("FALSE: Error with last index of method");
		}
		
		//test clear
		dll.clear();
		if(dll.size != 0) {
			System.out.println("Size: "+dll.size);
			System.err.println("FALSE: Error with clear method");
		}
		
	}

}
