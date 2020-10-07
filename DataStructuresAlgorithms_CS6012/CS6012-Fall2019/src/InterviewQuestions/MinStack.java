package InterviewQuestions;


public class MinStack {
	int min;
	int minIndex=0;
	int[] minStack = new int[100];
	
	public void push(int n) 
	{
		if(n < min)
		{
			min = n;
			minStack[minStack.length]=n;
			minIndex = minStack.length;
		}
		else
		{
			minStack[minStack.length]=n;
		}
	}
	
	
	
	


}
