package il.co.ilrd.hashmap;

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

import il.co.ilrd.pair.Pair;

public class HashMap<K,V> implements Map<K, V>{

	private List<List<Pair<K, V>>> hashMap;
	private final int capacity;
	private final static int DEFAULT_VALUE = 16; 
	private Set<Map.Entry<K, V>> entrySet;
	private Set<K> keySet;
	private Collection<V> valueCollection;
	private int mapModCount = 0;
	
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
	
	private int getBucket(Object key) {
		if (key == null) {
			return 0;
		}
		
		return key.hashCode() % capacity;
	}
	
	private Pair<K, V> getEntry(Object key){
		for (Pair<K, V> pair : hashMap.get(getBucket(key))) {
			if (pair.getKey().equals(key)) {
				return pair;
			}
		}
		
		return null;
	}
	
	/**********************************************************************************/
	
	@Override
	public void clear() {
		for (List<Pair<K,V>> bucket : hashMap) {
			bucket.clear();
		}
		
		++mapModCount;
	}
	
	@Override
	public boolean containsKey(Object key) {
		for (Pair<K, V> pair : hashMap.get(getBucket(key))) {
			if(pair.getKey().equals(key)) {
				return true;
			}
		}
		
		return false;
	}

	@Override
	public boolean containsValue(Object value) {
		for (V v : values()) {
			if (v.equals(value)) {
				return true;
			}
		}
		
		return false;
	}

	@Override
	public Set<Entry<K, V>> entrySet() {
		if(null == entrySet) {
			entrySet = new EntrySet();
		}
		
		return entrySet;
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
		for (List<Pair<K,V>> bucket : hashMap) {
			if (!bucket.isEmpty()) {
				return false;
			}
		}
		
		return true;
	}

	@Override
	public Set<K> keySet() {
		if(null == keySet) {
			keySet = new KeySet();
		}
		
		return keySet;
	}

	@Override
	public V put(K key, V value) {
		Pair<K,V> pair = getEntry(key);
		if(null != pair) {
			return pair.setValue(value);
		}
		
		hashMap.get(getBucket(key)).add(Pair.of(key, value));
		
		return null;
	}

	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		for(Map.Entry<? extends K, ? extends V> entry : m.entrySet()) {
			this.put(entry.getKey(),entry.getValue());
		}
		
		++mapModCount;
	}

	@Override
	public V remove(Object key) {
		Pair<K, V> pair = getEntry(key);
		if (pair == null) {
			return null;
		}
		
		hashMap.get(getBucket(key)).remove(pair);
		++mapModCount;

		return pair.getValue();
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
		if (valueCollection == null) {
			valueCollection = new ValueCollection();
		}
		
		return valueCollection;
	}
	
	private class EntrySet extends AbstractSet<Entry<K,V>>{
		
		private int modCount = mapModCount;
		@Override
		public Iterator<Entry<K,V>> iterator() {
			return new EntryIterator();
		}

		@Override
		public int size() {
			return HashMap.this.size();
		}
		
		private class EntryIterator implements Iterator<Entry<K,V>>{
			
			Iterator<List<Pair<K, V>>> externalIter = hashMap.iterator();
			Iterator<Pair<K, V>> internalIter = externalIter.next().iterator();
			
			public EntryIterator() {
				while(!internalIter.hasNext() && externalIter.hasNext()) {
					internalIter = externalIter.next().iterator();
				}
			}
			
			@Override
			public boolean hasNext() {
				return(internalIter.hasNext() || externalIter.hasNext());	
			}

			@Override
			public Entry<K,V> next() {
				checkIteratorValidation();
				Map.Entry<K, V> entry = internalIter.next();
				while(!internalIter.hasNext() && externalIter.hasNext()) {
					internalIter = externalIter.next().iterator();
				}
				
				return entry;
			}

	
			private void checkIteratorValidation() {
				if (mapModCount != modCount) {
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