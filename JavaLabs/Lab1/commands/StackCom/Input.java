package Lab1.commands.StackCom;

import StackCommand;
import java.util.Scanner;

public class Input extends StackCommand {
	public Input(Stack<Object> s) {
		super(s);
	}

	public void execute() {
		Scanner input = new Scanner(System.in);
		stack.push(input.nextInt());
	}
}