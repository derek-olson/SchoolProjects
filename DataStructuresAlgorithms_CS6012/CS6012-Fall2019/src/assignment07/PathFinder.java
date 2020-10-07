package assignment07;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

public class PathFinder {
	public static Node start = null;
	public static Node goal = null;
	
	/**
	 * default constructor
	 */
	public PathFinder() 
	{
		
	}
	
	/**
	 * A method to solve for the shortest path through a maze
	 * @param inputFile - the input maze
	 * @param outputFile - the name of the output file
	 * @throws FileNotFoundException
	 */
	public static void solveMaze(String inputFile, String outputFile) throws FileNotFoundException 
	{
		Graph graph = createGraph(inputFile);
		if(start == null || goal == null) {
			throw new IllegalStateException();
		}
		breadthFirstSearch(start, goal, graph); 
		writeToFile(graph, outputFile);
	}
	
	/**
	 * This method takes in an input file and turns it into a graph
	 * @param inputFile
	 * @throws FileNotFoundException 
	 */
	public static Graph createGraph(String inputFile) throws FileNotFoundException 
	{
		//get the file and check if it exists
		File file = new File(inputFile);
		if(!file.exists()) 
		{
			System.out.println("File doesn't exist");
		}
		
		// create a scanner
		Scanner scanner = new Scanner(file);

		//get the number of rows and columns
		int rows = scanner.nextInt();
		int cols = scanner.nextInt();
		
		//create a graph
		Graph graph = new Graph(rows, cols);
		
		//fill in the graph with characters from the input file
		String string = scanner.nextLine();
		while(scanner.hasNextLine()) 
		{
			for (int i=0; i<rows; i++)
			{
				string = scanner.nextLine();
				System.out.println(string);
				for(int j=0; j<cols; j++)
				{
					Node node = new Node(string.charAt(j));
					node.row=i;
					node.col=j;
					if(node.getElement() == 'S')
					{
						start=node;
					}
					if(node.getElement() == 'G')
					{
						goal=node;
					}
					if(node.getElement() == 'X')
					{
						node = null;
					}
					graph.setRowCol(i, j, node);
				}
			}
		}
		
		scanner.close();

		return graph;
	}
	
	/**
	 * A method to search for the shortest path
	 * @param start - the start node
	 * @param end - the goal node
	 * @param graph - the 2D array to search through
	 */
	public static void breadthFirstSearch(Node start, Node end, Graph graph) 
	{
		Queue<Node> queue = new LinkedList<>();
        queue.offer(start);
        while (!queue.isEmpty()) 
        {
            Node n = queue.poll();
            n.visited = true;
            if(n.getElement()==goal.getElement()) 
            {
            	while(n.prev.getElement()!='S')
            	{
            		n = n.prev;
            		n.setElement('.');
            	}
            }
            for (Node neighbor: getNeighbors(n, graph)) 
            {
            	queue.offer(neighbor);
            }
        }
        
	}
	
	/**
	 * A method to the the neighbors of a node
	 * @param node - the node for which to search for neighbors
	 * @param graph - the 2D array to search for neighbors in
	 * @returns a list of neighbor nodes
	 */
	public static List<Node> getNeighbors(Node node, Graph graph) 
	{
		List<Node> neighbors = new ArrayList<>();
		Node[][] arr = graph.getArr();
		Node up = arr[node.row-1][node.col];
		if(up != null )
		{
			if(!up.visited) 
			{
				up.prev = node;
				neighbors.add(up);
			}
		}
		Node down = arr[node.row+1][node.col];
		if(down != null)
		{
			if(!down.visited) 
			{
				down.prev = node;
				neighbors.add(down);
			}
		}
		Node left = arr[node.row][node.col-1];
		if(left != null)
		{
			if(!left.visited) 
			{
				left.prev = node;
				neighbors.add(left);
			}
		}
		Node right = arr[node.row][node.col+1];
		if(right != null)
		{
			if(!right.visited) 
			{
				right.prev = node;
				neighbors.add(right);
			}
		}
		return neighbors;
	}
	
	/**
	 * A method to write the solved maze to file
	 * @param graph-the 2D array that will be written to file
	 * @param outputFile - the name of the output file as a string
	 * @throws FileNotFoundException
	 */
	public static void writeToFile(Graph graph, String outputFile) throws FileNotFoundException 
	{
		PrintWriter writer = new PrintWriter(outputFile);
	    int height = graph.getArr().length;
	    int width = graph.getArr()[0].length;
	    writer.println(height+" "+width);
	    //writer.println(width);
		for(int i=0; i<height;i++) 
		{
			for(int j=0; j<width; j++)
			{
				if(graph.arr[i][j] == null)
				{
					Node node = new Node('X');
					graph.arr[i][j]=node;
				}
				writer.print(graph.arr[i][j].getElement());
				System.out.print(graph.getArr()[i][j].getElement());
			}
			writer.println();
			System.out.println();
		}
		writer.close();
	}
}
