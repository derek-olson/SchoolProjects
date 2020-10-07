package assignment07;

public class Node {
	private char element;
	public boolean visited = false;
	public Node prev;
	public int row;
	public int col;
	
	public Node(char element) 
	{
		this.element = element;
	}
	
	public char getElement()
	{
		return this.element;
	}
	
	public void setElement(char c) 
	{
		this.element = c;
	}
	
}
