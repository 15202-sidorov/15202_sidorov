package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;
import Lab1.Flow;

public class PushString implements Command {

	public void execute( ProgramProperties prop) {
		Flow flow = prop.getFlow();
		Stack<Integer> stack = prop.getStack();
		char nextChar = flow.getNextChar();
		flow.switchMode();
		while ((nextChar != '"')) {
			stack.push((int)nextChar);
			nextChar = flow.getNextChar();
		}
		flow.switchMode();
	}
}