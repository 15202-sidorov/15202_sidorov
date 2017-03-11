package Lab1.commands.StackCom;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class PopChar implements Command {

	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		System.out.print((char)stack.pop());
	}
}