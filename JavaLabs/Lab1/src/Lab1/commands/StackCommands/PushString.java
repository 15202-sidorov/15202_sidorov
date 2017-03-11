package Lab1.commands.StackCommands;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class Push implements Command {

	public void execute( ProgramProperties prop) {
		Flow flow = prop.getFlow();
		Stack<Integer> stack = prop.getStack();
		char nextChar = flow.getNextChar();
		while (nextChar != '"') && (nextChar != '@') {
			stack.push((int)nextChar);
			nextChar = flow.getNextChar();
		}
	}
}