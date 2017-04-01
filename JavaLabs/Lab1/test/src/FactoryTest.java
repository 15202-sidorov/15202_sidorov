package Lab1.test;

import Lab1.*;
import Lab1.commands.*;
import org.junit.*;

public class FactoryTest {
	@Test
	private void constructorTest() throws FactoryException {
		testFactory = new Factory();

	}
	
	@Test
	private void makeGoodProductTest() throws FactoryException {
		for (int i = 0; i < allGoodProperties.length(); i++) {
			Command c = testFactory.makeProduct(allGoodProperties.charAt(i));
		}
	}

	@Test(expected = FactoryException.class)
	private void makeBadProductTest() throws FactoryException {
		testFactory.makeProduct(badSymbol);
	}

	private char badSymbol = 'q';
	private Factory testFactory = null;
	private final String allGoodProperties = 
		">v<^#+\\/@`&~%*!,.$-\"|_:0123456789gp";
}