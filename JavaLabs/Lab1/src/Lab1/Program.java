package Lab1;

import java.util.Stack;
import java.lang.reflect.*;

import Lab1.commands.Command;
import Lab1.commands.StackCommands.*;
import Lab1.commands.FlowCommand.*;

public class Program {

	public static void execute() {
		Factory factory = null;
		ProgramProperties machine = null;
		try {
			factory = new Factory();
			machine = new MachineState("srccode.bfng");
		}
		catch(FactoryException exc) {
			System.out.println("Could not load properties.");
			return;
		}
		catch(Exception exc) {
			System.out.println("Properties failed to be created.");
			return;
		}

		char nextChar = 0;
		Command nextCommand = null;
		Flow flow = machine.getFlow();
		Stack<Integer> stack = machine.getStack();

		while ( nextChar != '@' ) {
			try {
				nextChar = flow.getNextChar();
				machine.assignInputValue(nextChar);
				nextCommand = factory.makeProduct(nextChar);
				nextCommand.execute(machine);
			}
			catch(FactoryException exc) {
				System.out.println("Could not find symbol.");
				return;
			}
		}
	}
}
