package lab06;

import static org.junit.jupiter.api.Assertions.*;

import java.util.NoSuchElementException;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.MethodOrderer.OrderAnnotation;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
@TestMethodOrder(OrderAnnotation.class)
class lab06_tests<E> {

	@SuppressWarnings("rawtypes")
	
	private static DoublyLinkedList dll;
	

	
	@SuppressWarnings("rawtypes")
	@BeforeEach
	public void setUp() throws Exception {
		dll = new DoublyLinkedList();
	}

	@AfterEach
	void tearDown() throws Exception {
	}
	
	@Test
	@Order(1)
	void testIsEmpty() {
		assertTrue(dll.isEmpty());
	}
	
    @Test
    @Order(2)
    void testIsEmptySizeIsZero() {
        assertEquals(0, dll.size());
    }
	
	@SuppressWarnings("rawtypes")
	@Test
	@Order(3)
	void testAddFirst() {
		LinkedNode ln = new LinkedNode(1);
		dll.addFirst(ln);

	}
	
	@Test
	@Order(4)
	void testSize() {
		assertEquals(dll.size(), 1);
	}
	

//    @Test(expected = NoSuchElementException.class)
//    @Order(5)
//    public void testRemoveNotPresentThrowsException() {
//        list.addFront(1);
//        list.remove(2);
//    }

//	@Test
//	@Order(5)
//	void testGetFirst() {
//		LinkedNode firstNodeTest = new LinkedNode(0);
//		LinkedNode head = (LinkedNode) dll.getFirst();
//		assertEquals(head.object, firstNodeTest.object);
//	}
//	
//	@Test
//	@Order(6)
//	void testGetLast() {
//		LinkedNode last = new LinkedNode(0);
//		assertEquals(dll.getLast(), last);
//	}
//	
//	@Test
//	@Order(7)
//	void testAddLast() {
//		LinkedNode last = new LinkedNode(11);
//		dll.addLast(last);
//		assertEquals(dll.getLast(), last);
//	}
//	
//	@Test
//	@Order(8)
//	void testAddGet() {
//		LinkedNode node = new LinkedNode(66);
//		dll.add(3, node);
//		assertEquals(dll.get(3), node);
//	}
//	
//	@Test
//	@Order(9)
//	void testRemoveFirstObject() {
//		LinkedNode node = new LinkedNode(0);
//		dll.removeFirst();
//		assertEquals(dll.getFirst(), node);
//	}
//
//	@Test
//	@Order(10)
//	void testRemoveFirstSize() {
//		LinkedNode node = new LinkedNode(11);
//		dll.removeLast();
//		assertEquals(dll.getLast(),node);
//	}
	
	
	
	

}
