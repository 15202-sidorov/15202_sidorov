package Lab1.commands.StackCom;

import StackCommand;

public class Pop extends StackCommand {
	public Pop(Stack<Object> s, Class c) {
		super(s);
		outputClass = c;

	}

	public void execute() {
		if ( outputClass == Class.forName("Character") ) {
			System.out.println((char)stack.pop());
		}
		else if ( outputClass == Class.forName("Interger") ) {
			System.out.println((int)stack.pop());
		}
		else {
			stack.pop();
		}
	}

	private Class outputClass;
}