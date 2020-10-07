package lab05;


import lab05.BinarySearchSet;

public class lab05_tests {


	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		
		@SuppressWarnings("rawtypes")
		BinarySearchSet bSS = new BinarySearchSet();
		
//		for (int i = 0; i < 1000; i++) {
//			bSS.add(i);
//		}
		
		bSS.testAdd();
		System.out.println(bSS.searchSet);
		
		bSS.binarySearchBool(6, 0, 9);
		
	}

}
