package Lab1;

import java.util.Stack;

public interface ProgramProperties {
	public Flow getFlow();
	public Stack<Integer> getStack();
	public void assignInputValue( Object value );
	public Object getInputValue();
}