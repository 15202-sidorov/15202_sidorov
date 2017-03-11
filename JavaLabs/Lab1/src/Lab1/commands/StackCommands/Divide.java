package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class Divide implements Command {

	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		int arg1 = stack.pop();
		int arg2 = stack.pop();
		stack.push(arg1 / arg2);
	}
}