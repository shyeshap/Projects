package il.co.ilrd.quizzes;

/*
 * given a matrix of numbers N/N. Find the maximum size of Identity matrix (Identity Matrix is a
 * square matrix in which all the elements of the main diagonal are 1’s and all other elements are
 * zeros) in the lower right corner.
 * 
 * Example:
 * for given matrix
 * 2 3 4 5
 * 6 7 8 9
 * 2 3 4 0
 * 3 3 3 1
 * Output 1
 * 
 * for given matrix
 * 2 3 4 5
 * 3 3 3 3
 * 6 7 1 0
 * 2 3 0 1
 * Output 2
 * 
 * for given matrix
 * 2 3 4 5
 * 3 1 0 0
 * 6 0 1 0
 * 2 0 0 1
 * Output 3
 * 
 */
public class Matrix {
	//Brute force solution:
	public static int maxIdentifyMatrix(int[][] matrix) {
		int cnt = 0;
		int n = matrix.length;

		for (int i = n - 1; i >= 0; --i){
			if (matrix[i][i] == 1){
				for (int j = i + 1; j < n; ++j) {
					if (matrix[i][j] == 0 && matrix[j][i] == 0) {
						continue;
					} else {
						return cnt;
					}
				}
				++cnt;
			} else {
				return cnt;
			}
		}
		return cnt;
	}

	public static void main(String[] args) {
		int[][] m = {{2, 3, 4, 5}, {3, 3, 3, 3}, {6, 7, 8, 9}, {3, 3, 3, 1}};
		int[][] m1 = {{2, 3, 4, 5}, {3, 3, 3, 3}, {6, 7, 1, 0}, {3, 3, 0, 1}};
		int[][] m2 =  {{2, 3, 4, 5}, {3, 1, 0, 1}, {6, 0, 1, 0}, {3, 0, 0, 1}};
		int[][] m3 =  {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
		int[][] m4 = {{2, 3, 4, 5}, {3, 3, 3, 3}, {6, 7, 8, 9}, {3, 3, 3, 5}};
		System.out.println(maxIdentifyMatrix(m) == 1);
		System.out.println(maxIdentifyMatrix(m1) == 2);
		System.out.println(maxIdentifyMatrix(m2) == 2);
		System.out.println(maxIdentifyMatrix(m3) == 4);
		System.out.println(maxIdentifyMatrix(m4) == 0);
	}
}
