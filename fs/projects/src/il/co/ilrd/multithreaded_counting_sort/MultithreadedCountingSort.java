package il.co.ilrd.multithreaded_counting_sort;

public class MultithreadedCountingSort {
	private static char[] arr;
	private static final int ascii = 256;
	static int[] histograma = new int[ascii];
	private int[] threadHhistogram = new int[ascii];
	
	public MultithreadedCountingSort(char[] arr) {
		MultithreadedCountingSort.arr = arr;
	}
	
	public char[] start(int numOfThreads) throws InterruptedException {
		int len = arr.length;
		Thread[] threadArr= new Thread[numOfThreads];
		int section = len/numOfThreads; 

		for (int i = 0; i < numOfThreads; ++i) {
			threadArr[i] = new Thread(new MultithreadedCountingSort(arr).
						   new Counting(i * section, (i * section) + section -1, numOfThreads));
        	threadArr[i].start();
		}
		
		for (int i = 0; i < numOfThreads; ++i) {
			threadArr[i].join();
		}
        
        return MultithreadedCountingSort.sort();
	}

	private static char[] sort() {
		char[] output = new char[arr.length];

		for (int i = 0; i < ascii; ++i) {
			for (int j = 0; j < histograma[i]; ++j)
			{
				System.out.println(histograma[i] + j - 1);
				output[histograma[i] + j - 1] = (char)i;
			}
		}
				
		return output;
	}
	
	private class Counting implements Runnable{
		private int startIdx;
		private int endIdx;
		
		private Counting(int startIdx, int endIdx, int row) {
			this.startIdx = startIdx;
			this.endIdx = endIdx;
		}
		
	@Override
	public void run() {
		for (int i = startIdx; i < endIdx; ++i) {
			++threadHhistogram[arr[i]]; 
		}
		
			for (int i = 0; i < ascii; ++i) {
				synchronized(histograma) {
					histograma[i] += threadHhistogram[i];
				}
			}
		}
	}	
}
