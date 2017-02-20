package Lab1.commands.StackCom;

import StackCommand;

public class End extends StackCommand {
	public End(Stack<Object> s) {
		super(s);
	}

	public void execute() {
		while (null != stack.pop()) {
			continue;
		}
	}
}