package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class Greater implements Command {
	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		int arg1 = stack.pop();
		int arg2 = stack.pop();
		if (arg1 > arg2) {
			stack.push(arg1);
		}
		else {
			stack.push(arg2);
		}
	}
}