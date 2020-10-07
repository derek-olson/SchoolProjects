package InterviewQuestions;

public class Fib {

	public static void main(String[] args) {
		fib(3);
		fib2(3);

	}

	public static int fib(int n)
	{		
		if(n==0)
		{
			return 0;
		}
		if(n==1)
		{
			return 1;
		}
		return fib(n-1)+fib(n-2);
	}
	
	public static void fib2(int n) 
	{
		int i = 0;
		int a = 0;
		int b = 1;
		int c = a+b;
		
		while(i<n)
		{
			if(n==0) 
			{
				System.out.println(0);
			}
			if(n==1)
			{
				System.out.println(1);
			}
			a = b;
			b = c;
			c = a+b;
			i++;
		}
		System.out.println(a);
	}
}
