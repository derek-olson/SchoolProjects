package assignment07;

public class Graph {
	public Node[][] arr;
	
	public Graph(int rows, int cols) {
		setArr(new Node[rows][cols]);
	}

	public Node[][] getArr() {
		return arr;
	}

	public void setArr(Node[][] arr) {
		this.arr = arr;
	}
	
	public void setRowCol(int row, int col, Node node) {
		arr[row][col] = node;
	}
}
