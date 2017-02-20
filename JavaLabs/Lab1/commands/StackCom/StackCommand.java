package Lab1.commands.StackCom;

import Lab1.commands.Command;

public abstract class StackCommand implements Command {
	public StackCommand(Stack<Object> s) {
		stack = s;
	}

	public void execute();

	private StackCommand() {}
	private Stack<?> stack;
}

