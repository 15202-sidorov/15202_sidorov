package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class Add implements Command {

	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		if (stack.empty()) {
			System.out.println("The stack is empty");
		}
		int arg1 = stack.pop();
		int arg2 = stack.pop();
		stack.push(arg1 + arg2);
	}
}