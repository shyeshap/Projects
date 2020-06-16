package il.co.ilrd.generic_iot_infrastructure;

import il.co.ilrd.generic_iot_infrastructure.command.CRCommand;

public class CommandLoader {
	SingletonCommandFactory factory;
	
	public CommandLoader() {
		factory = SingletonCommandFactory.getInstance();
		factory.add("CR", CRCommand::new);
	}
}
