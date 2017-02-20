package Lab1.commands.StackCom;

import StackCommand;

public class Divide extends StackCommand {
	public Divide(Stack<Object> s) {
		super(s);
	}

	public void execute() {
		int arg1 = stack.pop();
		int arg2 = stack.pop();
		stack.push(arg1 / arg2);
	}

	private Divide() {}
}