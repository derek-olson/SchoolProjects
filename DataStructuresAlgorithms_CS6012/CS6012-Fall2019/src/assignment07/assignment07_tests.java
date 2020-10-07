package assignment07;

import java.io.FileNotFoundException;

public class assignment07_tests {

	public static void main(String[] args) throws FileNotFoundException {
		PathFinder pf = new PathFinder();
		//pf.createGraph("demoMaze.txt");

		pf.solveMaze("demoMaze.txt", "demoMazeOut.txt");
	}

}
