package Lab1.commands.StackCom;

import StackCommand;

public class Not extends StackCommand {
	public Not(Stack<Object> s) {
		super(s);
	}

	public void execute() {
		int arg1 = stack.pop();
		if (arg1 > 0) {
			stack.push(1);
		}
		else {
			stack.push(0);
		}
	}

	private Not() {}
}