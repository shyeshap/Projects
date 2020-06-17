package il.co.ilrd.generic_iot_infrastructure;

import il.co.ilrd.generic_iot_infrastructure.command.*;

public class CommandLoader {
	SingletonCommandFactory factory;
	
	public CommandLoader() {
		// handle unsupported commands
		factory = SingletonCommandFactory.getInstance();
		factory.add("CR", CRCommand::new);
		factory.add("PR", PRCommand::new);
		factory.add("EUR", EURCommand::new);
		factory.add("IOT", IOTCommand::new);
	}
}
