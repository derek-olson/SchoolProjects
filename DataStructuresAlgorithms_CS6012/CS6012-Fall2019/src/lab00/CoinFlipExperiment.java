package lab00;

public class CoinFlipExperiment {

	public static void main(String[] args) {	
		int[] counts = new int[201];
		int j = 0;
		while (j < 10000) {
			int amount = coinFlipExperiment();
			counts[amount+100] = counts[amount+100] + 1;
			System.out.println ("Win/loss amount: " + amount);
			j++;
		}
		
		
		
		System.out.println ("Likelihood of win/loss amount after 100 flips:");

		  System.out.print ("Amount");
		  System.out.print ("\t"); // A tab character
		  System.out.print ("Probability");
		  System.out.println ();

		  // Loop through amounts

		  double attempts = 10000.0;
		  for (int i = 0; i <= 200; i++)
		  {
		    System.out.print (i - 100);
		    System.out.print ("\t");
		    System.out.print (counts[i] / attempts);
		    System.out.println ();
		  }
	}
	
	  /** Returns the amount of money you'd win or lose
	  * by flipping an unbalanced coin 100 times.
	  *
	  * @return the amount of money won/lost
	  */
	  static public int coinFlipExperiment () {
			int winnings = 0;
			int i = 0;
			while (i < 100) {
			  double flip = Math.random();
			  if (flip < 0.505) {
			    System.out.println ("Heads");
			    winnings += 1;
			  } else {
			    System.out.println ("Tails");
			    winnings -= 1;
			  }
			  
			  i++;
			}
			return winnings;
	  }

}
