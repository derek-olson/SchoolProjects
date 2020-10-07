package assignment06;

public class ReallyBadHashFunctor implements HashFunctor{
   
	public int hash(String item) { 
		int n = item.length();
		int sum = 0;
		char[] charArr = new char[n]; 
	    for (int i = 0; i < n; i++) { 
	        charArr[i] = item.charAt(i); 
	    }
	    for(int j = 0; j<n; j++) {
	    	sum+=charArr[j]*Math.pow(31, n-j);
	    }
	    return sum;
  } 
}
