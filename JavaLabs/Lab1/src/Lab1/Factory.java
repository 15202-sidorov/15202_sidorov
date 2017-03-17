package Lab1;

import Lab1.commands.*;

import java.lang.reflect.*;
import java.util.Properties;
import java.util.*;
import java.io.*;

public final class Factory {
	public Factory() throws FactoryException {
		try {
			commands = new HashMap<Character,Class>();
			inputStream = getClass().getClassLoader().getResourceAsStream("configfile.properties");
			inputReader = new InputStreamReader(inputStream);
			property = new Properties();
			property.load(inputReader);
		}
		catch(Exception e) {
			throw new FactoryException(e);
		}
		finally {
			try {
				inputStream.close();
			}
			catch(IOException e){
				throw new FactoryException(e);
			}
		}
	}

	public Command makeProduct(char sign) throws FactoryException {
		try {
			if ( !commands.containsKey(sign) ) {
				commands.put(sign,
						 	Class.forName(property.getProperty(sign+"")));
			}
			return (Command)commands.get(sign).newInstance();
		} 
		catch(Exception e) {
			throw new FactoryException(e);
		}	
	}

	private Map<Character,Class> commands;
	private InputStream inputStream;
	private InputStreamReader inputReader;
	private Properties property;
}