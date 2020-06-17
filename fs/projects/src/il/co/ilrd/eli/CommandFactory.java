package il.co.ilrd.eli;

import com.google.gson.JsonObject;

import il.co.ilrd.design_patterns.Factory;


public class CommandFactory extends Factory<String, Command, JsonObject> {
	private static final CommandFactory factory = new CommandFactory();
	
	private CommandFactory() {
		add("CR", CRCommand::new);
		add("PR", PRCommand::new);
		add("EUR", EURCommand::new);
		add("IOT", IOTCommand::new);
	}
	
	public static CommandFactory getInstance() {
		return factory;
	}
}
