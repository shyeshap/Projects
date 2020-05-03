package il.co.ilrd.design_patterns;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class Factory <K, T, D> {
	private Map<K, Function<D, ? extends T>> map_types = new HashMap<>();
	
	public void add(K key, Function<D, ? extends T> ctorFunc) {
		map_types.put(key, ctorFunc);
	}
	
	public T create(K key, D data) {
		return map_types.get(key).apply(data);
	}

}
