package il.co.ilrd.yoav_monitor;

import java.io.Serializable;

public interface GenericCrud<T extends Serializable, K extends Serializable> extends AutoCloseable {
	K create(T obj);
	T read(K key);
	void update(K key, T obj);
	T delete(K key);
}

