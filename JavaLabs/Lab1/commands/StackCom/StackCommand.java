package Lab1.commands.StackCom;

import Lab1.commands.Command;

public abstract class StackCommand implements Command {
	StackCommand(Stack<int> s) {
		stack = s;
	}

	public void execute();

	private StackCommand() {}
	private Stack<int> stack;
}

