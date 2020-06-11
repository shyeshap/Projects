package il.co.ilrd.quizzes;

public class Palindrome {
	
	static int longestPalSubstr(String str) { 
		int cnt = 1;
		int total = 0;
		
		if (str.length() == 1) {
			return 1;
		}
	
		for (int i = 1; i < str.length() - 1; ++i) {
			if (str.charAt(i) == str.charAt(i - 1)) {
				cnt = 2;
				for (int j = 1; i - j - 1 >= 0 && i + j < str.length(); ++j) {
					if (str.charAt(i - j - 1) == str.charAt(i + j)) {
						cnt += 2;
					}
					else {
						break;
					}
				}
	
			}
			
			else if (str.charAt(i - 1) == str.charAt(i + 1)) {
				cnt = 3;
				for (int j = 2; i - j >= 0 && i + j < str.length(); ++j) {
					if (str.charAt(i - j) == str.charAt(i + j)) {
						cnt += 2;
					}
					else {
						break;
					}
				}
			}
			
			if (cnt > total) {
				total = cnt;
			}
		}
		
		return total;
	}

	public static void main(String[] args) {
		System.out.println(longestPalSubstr("babad"));
		System.out.println(longestPalSubstr("cbbd"));
		System.out.println(longestPalSubstr("aaaa"));
		System.out.println(longestPalSubstr("abababbbabcdcba"));
	}
}
