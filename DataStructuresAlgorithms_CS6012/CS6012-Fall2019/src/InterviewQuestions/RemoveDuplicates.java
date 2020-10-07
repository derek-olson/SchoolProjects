package InterviewQuestions;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

public class RemoveDuplicates {

	public static void main(String[] args) {
		LinkedList<Integer> ll = new LinkedList<Integer>();
		
		Set<Integer> set = new HashSet<Integer>();
		
		for(int i =0; i < ll.size(); i++) 
		{
			//set.add(ll.get(i));
			set.addAll(ll);
		}
		for(int i = 0; i < set.size(); i++)
		{
			ll.addAll(set);
		}
		//with no buffer
		for(int j=0; j<ll.size(); j++) 
		{
			for(int k=j+1; k<ll.size(); k++)
			{
				if(ll.get(j)==ll.get(k))
				{
					ll.remove(k);
				}
			}
		}

	}

}
