package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class Push implements Command {

	public void execute( ProgramProperties prop, Integer value ) {
		prop.getStack().push(value);
	}
}