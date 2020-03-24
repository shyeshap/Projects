package il.co.ilrd.multithreaded_counting_sort;

public class Main {
	
	public static void main(String[] args) throws InterruptedException {
        
		int numOfThreads = 5;
		char[] arr = FileToArray.fileToArray("/home/ol81-21/Documents/words");
		Shuffle.shuffleArray(arr);
		long stopTime;
		long startTime = System.nanoTime();
		new MultithreadedCountingSort(arr).startMultiThreadedCountingSort(numOfThreads);
		stopTime = System.nanoTime();
		System.out.println(numOfThreads + " threads: time = " + (stopTime - startTime));
	}
}