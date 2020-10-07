package assignment06;

import java.util.Arrays;
import java.util.Collection;

public class QuadProbeHashTable implements Set<String> {
	private int capacity;
	private int size;
	private HashFunctor functor;
	private String[] storage;
	private Boolean[] available;
	
	  /** Constructs a hash table of the given capacity that uses the hashing function
     * specified by the given functor.
     */
   public QuadProbeHashTable(int capacity, HashFunctor functor) {
	   this.capacity = capacity;
	   this.functor = functor;
	   if(isPrime(capacity)) {
		   storage = new String[capacity];
		   available = new Boolean[capacity];
		   Arrays.fill(available, Boolean.TRUE);
	   }
	   else {
		   capacity = nextPrime(capacity);
		   storage = new String[capacity];
		   available = new Boolean[capacity];
		   Arrays.fill(available, Boolean.TRUE);
	   }
   }

	@Override
	public boolean add(String item) {
	  if(contains(item)) {
		  return false;
	  }
	  if(size>=capacity/2) {
		  capacity = nextPrime(capacity*2);
		  String[] tempStor = new String[capacity];
		  Boolean[] tempAvail = new Boolean[capacity];
		  Arrays.fill(tempAvail, Boolean.TRUE);
		  for(int i=0; i<capacity/2; i++) {
			  if(storage[i]!=null) {
				  int index = functor.hash(storage[i])%capacity;
				  while(tempAvail[index] != true) {
					  int exp = 1;
					  index = (int) ((index+Math.pow(exp, 2))%capacity);
					  exp++;
				  }
				  tempStor[index] = storage[i];
				  tempAvail[index] = false;
			  }
		  }
		  storage = tempStor;
		  available = tempAvail;
	  }
	  int index = functor.hash(item)%capacity;
	  if(available[index] == true) {
		  storage[index] = item;
		  available[index] = false;
		  size++;
	  }
	  else {
		  while(!available[index]) {
			  int exp = 1;
			  index = (int) ((index+Math.pow(exp, 2))%capacity);
			  exp++;
		  }
		  storage[index] = item;
		  available[index] = false;
		  size++;
	  }
	  return true;
	}

	@Override
	public boolean addAll(Collection<? extends String> items) {
		  for(String item : items) {
			  if(item == null) {
				  return false;
			  }
			  add(item);
		  }
		  return true;
	}

	@Override
	public void clear() {
		for(int i=0; i<capacity; i++) {
			storage[i] = null;
			available[i] = true;
		}
		
	}

	@Override
	public boolean contains(String item) {
		if(isEmpty()) {
			return false;
		}
		int index = functor.hash(item)%capacity;
		if(storage[index] == item) {
			return true;
		}
		if(storage[index]!=null){
			if(storage[index] != item) {
				int i = 1;
				while(i<=capacity) {
					index = (int) ((index+Math.pow(i, 2))%capacity);
					if(storage[index] == item) {
						return true;
					}
					i++;
				}
			}
		}
		return false;
	}

	@Override
	public boolean containsAll(Collection<? extends String> items) {
		  for(String item : items) {
			 if(!contains(item)) {
				 return false;
			 }
		  }
		  return true;
	}

	@Override
	public boolean isEmpty() {
		if(size > 0) {
			return false;
		}
		return true;
	}

	@Override
	public boolean remove(String item) {
		if(!contains(item)) {
			return false;
		}
		if(item == null) {
			return false;
		}
		int index = functor.hash(item)%capacity;
		if(storage[index]==item) {
			storage[index]=null;
			available[index]=true;
			size--;
			return true;
		}
		if(!(storage[index] == item)) {
			int i = 1;
			while(i<capacity) {
				index = (int) ((index+Math.pow(i, 2))%capacity);
				if(storage[index] == item) {
					storage[index]=null;
					available[index]=true;
					size--;
					return true;
				}
				i++;
			}
		}
		return true;
	}

	@Override
	public boolean removeAll(Collection<? extends String> items) {
		  for(String item : items) {
			  if(!contains(item)) {
				  return false;
			  }
			  remove(item);
		  }
		  return true;
	}

	@Override
	public int size() {
		return size;

	}
	
	public boolean isPrime(int capacity) {
		boolean flag = false;
        for(int i = 2; i <capacity/2; ++i)
        {
            if(capacity % i == 0)
            {
                flag = true;
                break;
            }
            flag = false;
        }
        return flag;
	}
	
	public int nextPrime(int capacity) {
		int toReturn = capacity;
		while(!isPrime(toReturn)) {
			toReturn++;
		}
		return toReturn;
	}

}
