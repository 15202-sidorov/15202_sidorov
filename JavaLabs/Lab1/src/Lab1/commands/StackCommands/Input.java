package Lab1.commands.StackCommands;

import java.util.Scanner;
import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class Input implements Command {

	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		Scanner input = new Scanner(System.in);
		stack.push(input.nextInt());
	}
}