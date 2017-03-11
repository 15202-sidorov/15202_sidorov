package Lab1;

import java.util.Stack;

public class MachineState implements ProgramProperties {
	public MachineState(String src_filename) throws Exception {
		stack = new Stack<Integer>();
		flow = new Flow(src_filename);
	}

	public Flow getFlow() {
		return flow;
	}

	public Stack<Integer> getStack() {
		return stack;
	}

	public void assignInputValue( Object value ) {
		inputValue = value;
	}

	public Object getInputValue() {
		return inputValue;
	}

	private Stack<Integer> stack;
	private Flow flow;
	private Object inputValue;
}