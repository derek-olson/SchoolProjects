package assignment06;

public class MediocreHashFunctor implements HashFunctor{
    
	public int hash(String item) { 
    	int n = item.length();
    	int sum = 0;
    	char[] charArr = new char[n]; 
        for (int i = 0; i < n; i++) { 
            charArr[i] = item.charAt(i); 
        }
    	for(int i = 0; i<n; i++) {
    		sum+=charArr[i];
    	}
    	int hash;
    	hash = sum*n;
        return hash; 
	}
}
