package il.co.ilrd.generic_iot_infrastructure;

import il.co.ilrd.design_patterns.Factory;
import il.co.ilrd.generic_iot_infrastructure.command.Command;
import il.co.ilrd.generic_iot_infrastructure.msg.Data;

public class SingletonCommandFactory extends Factory<String, Command, Data> {
	private static final SingletonCommandFactory instance = new SingletonCommandFactory();
	
	private SingletonCommandFactory() {}
	
	public static SingletonCommandFactory getInstance() {
		return instance;
	}
}
