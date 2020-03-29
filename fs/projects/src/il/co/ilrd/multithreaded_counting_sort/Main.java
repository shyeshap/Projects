package il.co.ilrd.multithreaded_counting_sort;

public class Main {
	
	public static void main(String[] args) throws InterruptedException {
        
		char[] arr = FileToArray.fileToArray("/home/ol81-21/Documents/words");
		int times = 1;
		for (int numOfThreads = 1 ;numOfThreads < 100; ++numOfThreads) {
		long stopWatch = 0;
			for (int i = 0; i < times; ++i) {
				Shuffle.shuffleArray(arr);
				long startTime = System.nanoTime();
				new MultithreadedCountingSort(arr).start(numOfThreads);
				long stopTime = System.nanoTime();
				
				stopWatch += (stopTime - startTime);
			}
			
			System.out.println(numOfThreads + " threads: time = " + (stopWatch / times));
		}

      /*  int[] histograma = MultithreadedCountingSort.histograma;
        for (int i = 0; i < 256; ++i) {
            System.out.println((char)i + ": " + histograma[i]);
        }*/
	}
}