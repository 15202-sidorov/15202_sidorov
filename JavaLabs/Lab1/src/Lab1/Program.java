package Lab1;

import java.util.Stack;
import java.lang.reflect.*;

import Lab1.commands.Command;
import Lab1.commands.StackCommands.*;
import Lab1.commands.FlowCommand.*;

public class Program {

	public static void execute() throws Exception {
		ProgramProperties machine = new MachineState("srccode.bfng");
		Factory factory = new Factory();

		char nextChar = 0;
		Command nextCommand = null;
		Flow flow = machine.getFlow();
		Stack<Integer> stack = machine.getStack();

		while ( nextChar != '@' ) {
			nextChar = flow.getNextChar();
			System.out.println("Next char is : " + nextChar);
			if ((nextChar <= '9') && (nextChar >= '0')) {
				stack.push(nextChar - '0');
			}
			else{
				nextCommand = factory.makeProduct(nextChar);
				nextCommand.execute(machine);
			}
		}
	}
}
