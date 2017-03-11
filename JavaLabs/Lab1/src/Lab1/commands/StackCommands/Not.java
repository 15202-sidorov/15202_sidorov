package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class Not implements Command {
	
	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		int arg1 = stack.pop();
		if (arg1 > 0) {
			stack.push(1);
		}
		else {
			stack.push(0);
		}
	}
}