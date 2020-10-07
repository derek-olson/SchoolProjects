package assignment02;

import java.util.ArrayList;
import java.util.GregorianCalendar;

/**
 * Testing class for LibraryGeneric.
 *
 */
public class LibraryGenericTest {

  public static void main(String[] args) {

    // test a library that uses names (String) to id patrons
    LibraryGeneric<String> lib1 = new LibraryGeneric<String>();
    lib1.add(9780374292799L, "Thomas L. Friedman", "The World is Flat");
    lib1.add(9780330351690L, "Jon Krakauer", "Into the Wild");
    lib1.add(9780446580342L, "David Baldacci", "Simple Genius");

    String patron1 = "Jane Doe";

    if (!lib1.checkout(9780330351690L, patron1, 1, 1, 2008))
      System.err.println("TEST FAILED: first checkout");
    if (!lib1.checkout(9780374292799L, patron1, 1, 1, 2008))
      System.err.println("TEST FAILED: second checkout");
    ArrayList<LibraryBookGeneric<String>> booksCheckedOut1 = lib1.lookup(patron1);
    if (booksCheckedOut1 == null || booksCheckedOut1.size() != 2
        || !booksCheckedOut1.contains(new Book(9780330351690L, "Jon Krakauer", "Into the Wild"))
        || !booksCheckedOut1.contains(new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat"))
        || !booksCheckedOut1.get(0).getHolder().equals(patron1)
        || !booksCheckedOut1.get(0).getDueDate().equals(new GregorianCalendar(2008, 1, 1))
        || !booksCheckedOut1.get(1).getHolder().equals(patron1)
        || !booksCheckedOut1.get(1).getDueDate().equals(new GregorianCalendar(2008, 1, 1)))
      System.err.println("TEST FAILED: lookup(holder)");
    if (!lib1.checkin(patron1))
      System.err.println("TEST FAILED: checkin(holder)");

    // test a library that uses phone numbers (PhoneNumber) to id patrons
    LibraryGeneric<PhoneNumber> lib2 = new LibraryGeneric<PhoneNumber>();
    lib2.add(9780374292799L, "Thomas L. Friedman", "The World is Flat");
    lib2.add(9780330351690L, "Jon Krakauer", "Into the Wild");
    lib2.add(9780446580342L, "David Baldacci", "Simple Genius");

    PhoneNumber patron2 = new PhoneNumber("801.555.1234");

    if (!lib2.checkout(9780330351690L, patron2, 1, 1, 2008))
      System.err.println("TEST FAILED: first checkout");
    if (!lib2.checkout(9780374292799L, patron2, 1, 1, 2008))
      System.err.println("TEST FAILED: second checkout");
    ArrayList<LibraryBookGeneric<PhoneNumber>> booksCheckedOut2 = lib2.lookup(patron2);
    if (booksCheckedOut2 == null || booksCheckedOut2.size() != 2
        || !booksCheckedOut2.contains(new Book(9780330351690L, "Jon Krakauer", "Into the Wild"))
        || !booksCheckedOut2.contains(new Book(9780374292799L, "Thomas L. Friedman", "The World is Flat"))
        || !booksCheckedOut2.get(0).getHolder().equals(patron2)
        || !booksCheckedOut2.get(0).getDueDate().equals(new GregorianCalendar(2008, 1, 1))
        || !booksCheckedOut2.get(1).getHolder().equals(patron2)
        || !booksCheckedOut2.get(1).getDueDate().equals(new GregorianCalendar(2008, 1, 1)))
      System.err.println("TEST FAILED: lookup(holder)");
    if (!lib2.checkin(patron2))
      System.err.println("TEST FAILED: checkin(holder)");

    // My testing starts here
    
    //Create a library for testing
    LibraryGeneric<String> lib3 = new LibraryGeneric<String>();
    lib3.addAll("Mushroom_Publishing.txt");
    lib3.checkout(9781843193319L, "John A", 9, 1, 2017);
    lib3.checkout(9781843192954L, "John B", 12, 2, 2019);
    lib3.checkout(9781843192701L, "John C", 10, 1, 2016);
    lib3.checkout(9781843192039L, "John D", 11, 14, 2018);
    lib3.checkout(9781843192022L, "John E", 11, 30, 2019);
    lib3.checkout(9781843191230L, "John F", 12, 31, 2015);
    
    // check order by author
    ArrayList<LibraryBookGeneric<String>> byAuthor = lib3.getOrderedByAuthor();
    if(byAuthor.get(0).getIsbn() != 9781843193319L)
    	System.err.println("TEST FAILED: Author list order");
    
    // check order by ISBN
    ArrayList<LibraryBookGeneric<String>> byIsbn = lib3.getInventoryList();
    if(byIsbn.get(0).getIsbn() != 9781843190004L)
    	System.err.println("TEST FAILED: ISBN list order");
    
    //get a list of overdue books
    ArrayList<LibraryBookGeneric<String>> overDueList = lib3.getOverdueList(10, 31, 2019);

    //test if the list is the correct size and the order is correct (oldest first)
    if(overDueList.size()!=4)
    	System.err.println("TEST FAILED: overdue list length");
    if(overDueList.get(0).getIsbn() != 9781843191230L)
    	System.err.println("TEST FAILED: overdue list order");
    
    // check a book back in
    lib3.checkin(9781843191230L);
    
    //get a new list of overdue books
    ArrayList<LibraryBookGeneric<String>> overDueList2 = lib3.getOverdueList(10, 31, 2019);
    
    // check length of new overdue list and make sure books are ordered correctly
    if(overDueList2.size()!=3)
    	System.err.println("TEST FAILED: overdue list length");
    if(overDueList2.get(0).getIsbn() != 9781843192701L)
    	System.err.println("TEST FAILED: overdue list order");
    
    //check in book that is already checked in
    if(lib3.checkin(9781843191230L)) {
    	System.err.println("TEST FAILED: check in a book that is already checked in");
    }
    
    //check out a book that is already checked out
    if(lib3.checkout(9781843192954L, "John B", 12, 2, 2019)) {
    	System.err.println("TEST FAILED: check out a book that is already checked out");
    }
    
    System.out.println("Testing done.");
    
  }
}
