package Lab1;

public class FactoryException extends Exception {
	public FactoryException() { super(); }
 	public FactoryException(String message) { super(message); }
 	public FactoryException(String message, Throwable cause) { super(message, cause); }
 	public FactoryException(Throwable cause) { super(cause); }
}