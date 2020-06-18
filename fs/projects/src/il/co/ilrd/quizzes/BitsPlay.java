package il.co.ilrd.quizzes;

public class BitsPlay {
	int turnOffKthBit(int n, int k) {
		return n & ~(1 << k);
	}

	void swap(int x, int y) {
		x = x ^ y;
		y = x ^ y;
		x = x ^ y;
		
		System.out.println("x = " + x + " | y = " + y);
	}

	int toggleKthBit(int n, int k) {
		return n ^ (1 << k);
	}

	static int leftRotate(int n, int d) {
		return (n << d) | n >> (32 - d);
	}

	int mirrorBits(int a) {
		int ans = 0;
		for (int i = 0; i < 16; ++i) {
			int mask = (int)Math.pow(1, i);
			ans ^= ((a & mask) << (32 - i)) ^ ((a & (int)Math.pow(1, 31 - i)) >> i);
		}
		
		return ans;
	}
	
	int reverse(int x)
	{
	    x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1); 
	    x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2); 
	    x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4); 
	    x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8); 
	    x = ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16);
	    return x ;
	}
	
	public static void main(String[] args) {
		BitsPlay b = new BitsPlay();
		System.out.println(b.turnOffKthBit(2, 1) == 0);
		System.out.println(b.turnOffKthBit(3, 0) == 2);
		
		b.swap(3, 4);
		
		System.out.println(b.toggleKthBit(1, 0) == 0);
		System.out.println(b.toggleKthBit(6, 2) == 2);
		System.out.println(b.toggleKthBit(6, 0) == 7);
		
		System.out.println(leftRotate(1, 3) == 8);
		System.out.println(b.mirrorBits((int)(Math.pow(2, 25))) == b.reverse((int)(Math.pow(2, 25))));
		System.out.println(b.mirrorBits((int)(Math.pow(2, 26))) == b.reverse((int)(Math.pow(2, 26))));
	}

}
