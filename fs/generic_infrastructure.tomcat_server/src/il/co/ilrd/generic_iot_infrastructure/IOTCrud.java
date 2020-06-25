package il.co.ilrd.generic_iot_infrastructure;

import com.google.gson.JsonObject;

public interface IOTCrud {
	public String create(JsonObject msg);

	public JsonObject read(String key);

	public void update(String key, JsonObject obj);

	public JsonObject delete(String key);
}
