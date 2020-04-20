package il.co.ilrd.pair;

import java.util.Comparator;
import java.util.Map;

public class Pair<K, V> implements Map.Entry<K, V>{

	private K key;
	private V value;
	
	private Pair(K key, V value) {
		this.key = key;
		this.value = value;
	}
	
	public static<K, V> Pair<K, V> of(K key, V value) {
		return new Pair<K, V>(key, value);
	}

	public static<K, V> Pair<V, K> swap(Pair<K, V> pair) {
		return new Pair<V, K>(pair.value, pair.key);
	}

	@Override
	public V getValue() {
		return value;
	}

	@Override
	public K getKey() {
		return key;
	}

	@Override
	public V setValue(V value) {
		V ret = this.value;
		this.value = value;
		
		return ret;
	}
/*	***unsafe function***
	public K setKey(K key) {
		K ret = this.key;
		this.key = key;
		
		return ret;
	}
*/
	@Override
	public String toString() {
		return "Pair [key=" + key + ", value=" + value + "]";
	}
	

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((key == null) ? 0 : key.hashCode());
		result = prime * result + ((value == null) ? 0 : value.hashCode());
		return result;
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if(obj instanceof Pair){
			return false;
		}
		Pair<K, V> other = (Pair) obj;
		if (key == null) {
			if (other.key != null)
				return false;
		}if (value == null) {
			if (other.value != null)
				return false; 
		}else if (!key.equals(other.key) || !value.equals(other.value))
			return false;
		return true;
	}

	public static <T extends Comparable<T>> Pair<T, T> minMax(T[] array) {
		comparableToComparator<T> comp = new comparableToComparator<T>();
		
		return minMax(array, comp);
	}
	
	private static class comparableToComparator<T extends Comparable<T>> implements Comparator<T>{
		@Override
		public int compare(T arg0, T arg1) {
			return arg0.compareTo(arg1);
		}
	}
	
	public static <T> Pair<T, T> minMax(T[] arr, Comparator<T> comparator) {
		if (arr == null || arr.length < 1)
			return null;
	 
		T min = arr[0], max = arr[0];
		T tempMin, tempMax;
		
		for(int i = arr.length % 2; i < arr.length; i += 2) {
			if(comparator.compare(arr[i], arr[i + 1]) > 0) {
				tempMax = arr[i];
				tempMin = arr[i + 1];
			}
			else {
				tempMax = arr[i + 1];
				tempMin = arr[i];
			}
			if(comparator.compare(tempMax, max) > 0) {
				max = tempMax;
			}
			if(comparator.compare(tempMin, min) < 0) {
				min = tempMin;
			}
		}
		
		return Pair.of(min, max);
	}	
}
