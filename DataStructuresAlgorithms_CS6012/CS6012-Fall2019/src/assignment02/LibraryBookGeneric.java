package assignment02;

import java.util.GregorianCalendar;

public class LibraryBookGeneric<Type> extends Book{
	GregorianCalendar dueDate = null;
	Type holder = null;
	
	public LibraryBookGeneric(long isbn, String author, String title) {
		super(isbn, author, title);
	}
	
	public Type getHolder() {
		return this.holder;
	}
	
	public GregorianCalendar getDueDate() {
		return this.dueDate;
		
	}
	
	public void checkInBook() {
		this.holder = null;
		this.dueDate = null;
	}
	
	public void checkOutBook(Type holder, GregorianCalendar dueDate) {
		this.holder = holder;
		this.dueDate = dueDate;
	}
	
	//Do not override the equals method in Book.

}
