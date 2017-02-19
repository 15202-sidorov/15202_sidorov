package Lab1;

import commands;
import flow;

public class Game {

	public static void execute(String filename) {
		//open the file
		//while cycle
		//flow.read() --> returns a symbol
		//fabric geerates a command , using the symbol
		//if command is of flow control, then send it to the flow
		//if not, execute it (the program should be able to work with stack)

	}

	private static Stack<int> stack = new Stack<int>(); // stack of the program
	private static Fabric<Command> f = new Fabric<Command>(); // fabric for commands

}