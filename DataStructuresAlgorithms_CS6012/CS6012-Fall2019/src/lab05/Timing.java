package lab05;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Random;

public class Timing {
	

	public static void main(String[] args) {
//		try {
//			timeContains();
//		} catch (FileNotFoundException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		} catch (UnsupportedEncodingException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		
		try {
			timeAdd();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}


	}
	
	public static void timeContains() throws FileNotFoundException, UnsupportedEncodingException{
		@SuppressWarnings("rawtypes")
		BinarySearchSet bSS = new BinarySearchSet();
		Random random = new Random();
		PrintWriter writer = new PrintWriter("timesContains.txt", "UTF-8"); 
		for (int i = 1; i <= 10000; i++) {
			long sum = 0;
			long avg = 0;
			bSS.add(i);
			int c = random.nextInt(i);
			for (int j = 0; j < 100; j++) {
				long start = System.nanoTime();
				bSS.contains(c);
				long end = System.nanoTime();
				long totalTime = end - start;
				sum += totalTime;
				System.out.println(i+","+totalTime);
			}
			avg = sum/100;
			writer.println(i+","+avg);
		}
		writer.close();
	}
	
	public static void timeAdd() throws FileNotFoundException, UnsupportedEncodingException {
		@SuppressWarnings("rawtypes")
		BinarySearchSet bSS = new BinarySearchSet();
		PrintWriter writer = new PrintWriter("timesAdd.txt", "UTF-8"); 
		long sum = 0;
		long avg = 0;
		for (int i = 1; i <= 10000; i++) {
			bSS.add(i);
			for (int j = i+10001; j < i+10101; j++) {
				long start = System.nanoTime();
				bSS.add(j);
				long end = System.nanoTime();
				long totalTime = end - start;
				sum += totalTime;
				System.out.println(i+","+totalTime);
				bSS.remove(i);
			}
			avg = sum/100;
			writer.println(i+","+avg);
		}
		writer.close();
	}
}
