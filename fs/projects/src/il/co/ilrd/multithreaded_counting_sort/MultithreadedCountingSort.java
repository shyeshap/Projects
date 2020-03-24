package il.co.ilrd.multithreaded_counting_sort;

public class MultithreadedCountingSort {
	private static char[] arr;
	private static int ascii = 256;
	private static int[] histograma = new int[ascii];
	private int[] threadHhistogram = new int[ascii];
	
	public MultithreadedCountingSort(char[] arr) {
		MultithreadedCountingSort.arr = arr;
	}
	
	public String startMultiThreadedCountingSort(int numOfThreads) throws InterruptedException {
		int len = arr.length;
		Thread[] threadArr= new Thread[numOfThreads];
		int chunk = len/numOfThreads; 

		for (int i = 0; i < numOfThreads; ++i) {
			threadArr[i] = new Thread(new MultithreadedCountingSort(arr).new Counting(i * chunk, (i * chunk) + chunk -1, numOfThreads));
        	threadArr[i].start();
		}
		
		for (int i = 0; i < numOfThreads; ++i) {
			threadArr[i].join();
		}

        int[] histograma = MultithreadedCountingSort.getHistograma();
        for (int i = 0; i < 256; ++i) {
            System.out.println((char)i + ": " + histograma[i]);
        }
        
        return MultithreadedCountingSort.sort();
	}
	
	public static int[] getHistograma() {
		return histograma;
	}
	
	private static String sort() {
		String str = new String();
		
		for (int i = 0; i < ascii; ++i) {
			for (int j = histograma[i]; j > 0 ; --j)
			{
				str = str + (char)i;
			}
		}
			
		return str;
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
