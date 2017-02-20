package Lab1.flow;

import java.io.*

public class Flow {
	public Flow(String filename) {
		in = new FileInputStream(filename);
		out = new FileOutputStream(filename);
	}

	public int getCurrentX() {
		return x;
	}

	public int getCurrentY() {
		return y;
	}

	public void setX(int v) {
		x = v;
	}

	public void setY(int v) {
		y = v;
	}

	//returns symbol of the next operation
	public char getCurrentChar() {

	}

//flow control
	public void down() {

	}

	public void up() {

	}

	public void left() {

	}

	public void right() {

	}

	private FileOutputStream out;
	private FileInputStream in;
	private static final int x_max = ;
	private static final int y_max = ;
	private int x = 0;
	private int y = 0;
}
