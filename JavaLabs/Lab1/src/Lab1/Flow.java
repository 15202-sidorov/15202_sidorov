package Lab1;

import java.io.*;

public class Flow {

	public Flow(String filename) throws FileNotFoundException,
								        IOException {
		in = new FileInputStream(filename);
		x = 0;
		y = 0;
		charArray = new char[x_max][y_max];

		readFromFile();
		in.close();
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

	public char getNextChar() {
		char result = ' ';
		while (result == ' ') {
			result = charArray[x][y];
			//System.out.println("Getting char at"+x+" "+y);
			moveForward();
		}
		return result;
	}

	private void handleXCoordinate() {
		if ( x >= x_max ) {
			x = 0;
		}
		else if ( x < 0 ) {
			x = x_max;
		}
	}

	private void handleYCoordinate() {
		if ( y >= y_max ) {
			y = 0;
		}
		else if (y < 0) {
			y = y_max;
		}
	}

//flow control
	public void down() {
		moveBack();
		nextByte = Direction.DOWN;
		moveForward();
	}

	public void up() {
		moveBack();
		nextByte = Direction.UP;
		moveForward();
	}

	public void left() {
		moveBack();
		nextByte = Direction.LEFT;
		moveForward();
	}

	public void right() {
		moveBack();
		nextByte = Direction.RIGHT;
		moveForward();
	}

	private void moveForward() {
		switch( nextByte ) {
				case RIGHT :
					x++;
					break;
				case LEFT :
					x--;
					break;
				case UP : 
					y--;
					break;
				case DOWN :
					y++;
					break;
			}
			handleXCoordinate();
			handleYCoordinate();
	}

	private void moveBack() {
		switch( nextByte ) {
				case RIGHT :
					x--;
					break;
				case LEFT :
					x++;
					break;
				case UP : 
					y++;
					break;
				case DOWN :
					y--;
					break;
			}
			handleXCoordinate();
			handleYCoordinate();
	}

	private void readFromFile() throws IOException {
		int next = 0;
		int i = 0;
		int j = 0;
		while(( 0 != in.available() )  && (i < y_max)){
			j = 0;
			while (( 0 != in.available() )){
				next = in.read();
				if (next != (int)'\n') {
					charArray[j][i] = (char)next;
					//System.out.println("Reading char "+j+" "+i+" "+(char)next);
				}
				else {
					break;
				}
				j++;
			}
			i++;
		}
		/*
		System.out.println("Reading is done, printing the file");
		for ( char[] arr : charArray ) {
			for ( char elem : arr ) {
				System.out.println(elem);
			}
		}*/
	}

	private static final int x_max = 13;
	private static final int y_max = 13;
	
	private FileInputStream in;
	private int x;
	private int y;
	private char[][] charArray;
	private enum Direction {
		RIGHT, LEFT, UP, DOWN
	}

	private Direction nextByte = Direction.RIGHT;
}
