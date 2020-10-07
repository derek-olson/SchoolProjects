package assignment01;

public class Matrix {
  int numRows;
  int numColumns;
  int data[][];

  // Constructor with data for new matrix (automatically determines dimensions)
  public Matrix(int data[][]) {
    numRows = data.length; // d.length is the number of 1D arrays in the 2D array
    if (numRows == 0) {
      numColumns = 0;
    } else {
      numColumns = data[0].length; // d[0] is the first 1D array
    }
    this.data = new int[numRows][numColumns]; // create a new matrix to hold the data
    // copy the data over
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        this.data[i][j] = data[i][j];
      }
    }
  }

  @Override // instruct the compiler that we do indeed intend for this method to override
            // the superclass' (Object) version
  public boolean equals(Object other) {
    if (!(other instanceof Matrix)) { // make sure the Object we're comparing to is a Matrix
      return false;
    }
    Matrix matrix = (Matrix) other; // if the above was not true, we know it's safe to treat 'o' as a Matrix

    /*
     * TODO: replace the below return statement with the correct code, you must
     * return the correct value after determining if this matrix is equal to the
     * input matrix
     */
      int aRows = this.numRows;
	  int aCols = this.numColumns;
	  int bRows = matrix.numRows;
	  int bCols = matrix.numColumns;
	  
	  if (aCols != bCols | aRows != bRows) {
		  return false;
	  }else {
		  for (int i = 0; i < aRows; i++) {
			  for (int j = 0; j < bCols; j++) {
				  if( this.data[i][j] != matrix.data[i][j]) {
					  return false;
				  }
			  }
		  }
		  return true;
	  }
  }
 

  @Override // instruct the compiler that we do indeed intend for this method to override
            // the superclass' (Object) version
  public String toString() {
    /*
     * TODO: replace the below return statement with the correct code, you must
     * return a String that represents this matrix, as specified on the assignment
     * page
     */
	  int rows = this.numRows;
	  int cols = this.numColumns;
	  String out_string = "";
	  for (int i = 0; i < rows; i++) {
		  for (int j = 0; j < cols; j++) {
			  out_string += String.valueOf(this.data[i][j]);
			  out_string += " ";
		  }
		  out_string += "\n";
	  }
    return out_string;
  }

  public Matrix times(Matrix matrix) {
    /*
     * TODO: replace the below return statement with the correct code, This function
     * must check if the two matrices are compatible for multiplication, if not,
     * return null. If they are compatible, determine the dimensions of the
     * resulting matrix, and fill it in with the correct values for matrix
     * multiplication
     */
	  int aRows = this.numRows;
	  int aCols = this.numColumns;
	  int bRows = matrix.numRows;
	  int bCols = matrix.numColumns;
	  int data[][]= new int [aRows][bCols]; 
	  
	  if (aCols != bRows) {
		  return null;
	  }else {
		  Matrix out_matrix  = new Matrix(data);
		  for (int i = 0; i < aRows; i++) {
			  for (int j = 0; j < bCols; j++) {
				  for (int k = 0; k < aCols; k++) {
					  out_matrix.data[i][j] += this.data[i][k] * matrix.data[k][j];
				  }
			  }
		  }
		  return out_matrix;
	  }
  }

  public Matrix plus(Matrix matrix) {
    /*
     * TODO: replace the below return statement with the correct code, This function
     * must check if the two matrices are compatible for addition, if not, return
     * null. If they are compatible, create a new matrix and fill it in with the
     * correct values for matrix addition
     */
	  int aRows = this.numRows;
	  int aCols = this.numColumns;
	  int bRows = matrix.numRows;
	  int bCols = matrix.numColumns;
	  int data[][] = new int [aRows][aCols]; 
	  
	  if (aCols != bCols | aRows != bRows) {
		  return null;
	  }else {
		  Matrix out_matrix = new Matrix(data);
		  for (int i = 0; i < aRows; i++) {
			  for (int j = 0; j < bCols; j++) {
				  out_matrix.data[i][j] = this.data[i][j] + matrix.data[i][j];
			  }
		  }
		  return out_matrix;
	  }
  }
  
}
