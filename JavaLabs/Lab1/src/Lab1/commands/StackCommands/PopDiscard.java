package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class PopDiscard implements Command {

	public void execute( ProgramProperties prop ) {
		prop.getStack().pop();
	}
}