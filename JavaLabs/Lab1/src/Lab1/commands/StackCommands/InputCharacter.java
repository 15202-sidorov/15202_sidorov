package Lab1.commands.StackCommands;

import java.util.Scanner;
import java.util.Stack;
import Lab1.commands.Command;
import Lab1.ProgramProperties;

public class InputCharacter implements Command {

	public void execute( ProgramProperties prop ) {
		Stack<Integer> stack = prop.getStack();
		Scanner input = new Scanner(System.in);
		int value = (int)input.next().charAt(0);
		stack.push(value);
	}
}