package Lab1.commands.FlowCommand;

import Lab1.Flow;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class UP implements Command {
	public void execute( ProgramProperties prop ) {
		prop.getFlow().up();
	}
}