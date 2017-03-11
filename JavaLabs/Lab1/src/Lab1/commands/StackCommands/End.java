package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class End implements Command {
	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		while ( !stack.empty() ) {
			stack.pop();
		}
	}
}