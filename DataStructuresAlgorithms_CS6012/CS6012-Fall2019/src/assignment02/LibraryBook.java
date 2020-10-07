package assignment02;

import java.util.GregorianCalendar;

public class LibraryBook extends Book{
	GregorianCalendar dueDate = null;
	String holder = null;
	
	public LibraryBook(long isbn, String author, String title) {
		super(isbn, author, title);
	}
	
	public String getHolder() {
		return this.holder;
	}
	
	public GregorianCalendar getDueDate() {
		return this.dueDate;
		
	}
	
	public void checkInBook() {
		this.holder = null;
		this.dueDate = null;
	}
	
	public void checkOutBook(String holder, GregorianCalendar dueDate) {
		this.holder = holder;
		this.dueDate = dueDate;
	}
	
	//Do not override the equals method in Book.

}
