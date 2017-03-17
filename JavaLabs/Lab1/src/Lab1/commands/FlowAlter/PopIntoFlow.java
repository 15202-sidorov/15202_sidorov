package Lab1.commands.FlowAlter;

import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;
import Lab1.Flow;

public class PopIntoFlow implements Command {
	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		Flow flow = prop.getFlow();
		int x_current = flow.getCurrentX();
		int y_current = flow.getCurrentY();
		int y = stack.pop();
		int x = stack.pop();
		int value = stack.pop();
		flow.changeSymbol(x,y,(char)value);	
	}
}