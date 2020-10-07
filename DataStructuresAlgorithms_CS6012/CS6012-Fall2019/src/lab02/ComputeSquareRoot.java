package lab02;

public class ComputeSquareRoot {

	public static void main(String[] args) {
		for (int j = 0; j < 100; j++) {
			int i = 0;
			long[] times = new long[11];
			while (i < 11) {
				long startTime = System.nanoTime();
				Math.sqrt(i);
				times[i] = System.nanoTime() - startTime;
				i++;
			}
			long sum = 0;
			for (long time : times) {
				sum += time;
				System.out.println(time);
			}
			System.out.println("SUM: "+sum);
	
		}
	}
}
