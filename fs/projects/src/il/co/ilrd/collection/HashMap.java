package il.co.ilrd.collection;

import java.util.AbstractCollection;
import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class HashMap<K,V> implements Map<K, V>{

	private List<List<Pair<K, V>>> hashMap;
	private final int capacity;
	private final static int DEFAULT_VALUE = 16; 
	private int MapModCount = 0;
	
	public HashMap() {
		this(DEFAULT_VALUE);
	}
	
	public HashMap(int capacity) {
		this.capacity = capacity;
		hashMap = new ArrayList<List<Pair<K,V>>>(capacity);
		InitMap();
	}
	
	/************************ Auxiliary Functions *************************************/
	private void InitMap() {
		for (int i = 0; i < capacity; ++i) {
			hashMap.add(i, new LinkedList<Pair<K,V>>());
		}
	}
	
	private List<Pair<K, V>> getBucketIndx(Object key) {
		return hashMap.get(key == null ? 0 : Math.abs(key.hashCode() % capacity));
	}
	
	private Pair<K, V> getEntry(Object key){
		for (Pair<K, V> pair : getBucketIndx(key)) {
			if (pair.getKey().equals(key)) {
				return pair;
			}
		}
		
		return null;
	}
	
	private boolean isMatch(Object obj1, Object obj2) {
		try {
			return obj1.equals(obj2);
		}
		catch(NullPointerException e) {
			return obj1 == obj2;
		}
	}
	/**********************************************************************************/
	
	@Override
	public void clear() {
		for (List<Pair<K,V>> bucket : hashMap) {
			bucket.clear();
		}
		
		++MapModCount;
	}
	
	@Override
	public boolean containsKey(Object key) {
		for (Pair<K, V> pair : getBucketIndx(key)) { 
			if (isMatch(pair.getKey(), key)) {
				return true;
			}
		}
		
		return false;
	}

	@Override
	public boolean containsValue(Object value) {
		for (V v : values()) {
			if (isMatch(v, value)) {
				return true;
			}
		}
		
		return false;
	}

	@Override
	public Set<Entry<K, V>> entrySet() {
		return new EntrySet();
	}

	@Override
	public V get(Object key) {
		Pair<K,V> pair = getEntry(key);
		if(null == pair) {
			return null;
		}
		
		return pair.getValue();
	}

	@Override
	public boolean isEmpty() {
		if (entrySet().iterator().hasNext()) {
			System.out.println("in");
			return false;
		}		
		
		return true;
	}

	@Override
	public Set<K> keySet() {
		return new KeySet();
	}

	@Override
	public V put(K key, V value) {
		Pair<K,V> pair = getEntry(key);
		if(null != pair) {
			return pair.setValue(value);
		}
		
		getBucketIndx(key).add(Pair.of(key, value));
		
		return null;
	}

	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		for(Map.Entry<? extends K, ? extends V> entry : m.entrySet()) {
			this.put(entry.getKey(),entry.getValue());
		}

	}

	@Override
	public V remove(Object key) {
		List<Pair<K, V>> bucket = getBucketIndx(key);
		for (Pair<K, V> pair : bucket) {
			if(isMatch(pair.getKey(), key)) {
				V value = pair.getValue();
				bucket.remove(pair);
				
				return value;
			}
		}

		return null;
	}
	

	@Override
	public int size() {
		int size = 0;
		for (List<Pair<K, V>> bucket : hashMap) {
			size += bucket.size();
		}
		
		return size;
	}

	@Override
	public Collection<V> values() {
		return new ValueCollection();
	}
	
	private class EntrySet extends AbstractSet<Entry<K,V>>{
		
		private int modCount = MapModCount;
		@Override
		public Iterator<Entry<K,V>> iterator() {
			return new EntryIterator();
		}

		@Override
		public int size() {
			return HashMap.this.size();
		}
		
		private class EntryIterator implements Iterator<Entry<K,V>>{
			
			Iterator<List<Pair<K, V>>> bucketIter = hashMap.iterator();
			Iterator<Pair<K, V>> entryIter = bucketIter.next().iterator();
			
			public EntryIterator() {
				while(!entryIter.hasNext() && bucketIter.hasNext()) {
					entryIter = bucketIter.next().iterator();
				}
			}
			
			@Override
			public boolean hasNext() {
				return(entryIter.hasNext() || bucketIter.hasNext());	
			}

			@Override
			public Entry<K,V> next() {
				checkIteratorValidation();
				Map.Entry<K, V> entry = entryIter.next();
				while(!entryIter.hasNext() && bucketIter.hasNext()) {
					entryIter = bucketIter.next().iterator();
				}
				
				return entry;
			}

	
			private void checkIteratorValidation() {
				if (MapModCount != modCount) {
					throw (new ConcurrentModificationException());
				}
			}
		}
	}


	private class KeySet extends AbstractSet<K> implements Iterator<K> {
		
		private Iterator<Map.Entry<K, V>> iter = new EntrySet().iterator();		

		@Override
		public Iterator<K> iterator() {
			return new KeySet();
		}
		
		@Override
		public boolean hasNext() {
			return iter.hasNext();
		}

		@Override
		public K next() {
			return iter.next().getKey();
		}

		@Override
		public int size() {
			return HashMap.this.size();
		}	
	}
	
	private class ValueCollection extends AbstractCollection<V> implements Iterator<V> {
		
		private Iterator<Map.Entry<K, V>> iter = new EntrySet().iterator();		
		
		@Override
		public boolean hasNext() {
			return iter.hasNext();
		}

		@Override
		public V next() {
			return iter.next().getValue();
		}

		@Override
		public Iterator<V> iterator() {
			return new ValueCollection();
		}

		@Override
		public int size() {
			return HashMap.this.size();
		}
		
	}
}