package Lab1.commands.StackCom;

import StackCommand;

public class Greater extends StackCommand {
	public Greater(Stack<Object> s) {
		super(s);
	}

	public void execute() {
		int arg1 = stack.pop();
		int arg2 = stack.pop();
		if (arg1 > arg2) {
			stack.push(arg1);
		}
		else {
			stack.push(arg2);
		}
	}

	private Greater() {}
}