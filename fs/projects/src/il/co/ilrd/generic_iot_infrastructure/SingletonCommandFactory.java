package il.co.ilrd.generic_iot_infrastructure;

import com.google.gson.JsonObject;

import il.co.ilrd.design_patterns.Factory;
import il.co.ilrd.generic_iot_infrastructure.command.Command;

public class SingletonCommandFactory extends Factory<String, Command, JsonObject> {
	private static final SingletonCommandFactory instance = new SingletonCommandFactory();
	
	private SingletonCommandFactory() {}
	
	public static SingletonCommandFactory getInstance() {
		return instance;
	}
}
