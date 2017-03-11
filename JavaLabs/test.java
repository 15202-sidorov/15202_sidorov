import java.lang.reflect.*;
import java.util.*;
import java.io.*;

public class test {
	public static void main(String[] args) throws Exception {
		File inputFile = new File("testfile.txt");
		FileInputStream inputStream = new FileInputStream(inputFile);
		InputStreamReader inputReader = new InputStreamReader(inputStream);
		
		Properties properties = new Properties();
		properties.load(inputReader);
		inputStream.close();
		System.out.println(properties.getProperty("Property1"));
	}

}
