package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class PopInteger implements Command {

	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		System.out.print((int)stack.pop());
		System.out.print("\n");
	}
}