package assignment06;
//using the djb2 hash functor for java
public class GoodHashFunctor implements HashFunctor{
    
	public int hash(String item) { 
		 int hash = 5381;
	
	    for(int i=0; i<item.length();i++) {
	    	hash = item.charAt(i) + (hash*33);
	    }

	    return Math.abs(hash);
  } 
    
}

