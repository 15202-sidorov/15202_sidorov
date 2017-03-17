package Lab1.commands.DecisionMaking;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;
import Lab1.Flow;

public class HorisontalIf implements Command {
	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		Flow flow = prop.getFlow();
		if (stack.pop() != 0) {
			flow.left();
		}
		else {
			flow.right();
		}
	}
}
