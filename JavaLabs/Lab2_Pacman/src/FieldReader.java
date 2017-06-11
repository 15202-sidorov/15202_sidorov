
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Scanner;

/**

 */
public class FieldReader {
    public FieldReader( String filePath ) throws IOException {
        Scanner textScanner = new Scanner( new FileInputStream(filePath) );

        width = textScanner.nextInt();
        height = textScanner.nextInt();
        fieldItems = new boolean[width][height];
        int heightCounter = 0;
        String currentLine = textScanner.nextLine();
        char currentToken;
        int ghostsFound = 0;
        while  ((heightCounter < height) && (textScanner.hasNextLine())) {
            currentLine = textScanner.nextLine();
            for (int i = 0; i < width; i++) {
               currentToken =  currentLine.charAt(i);
                switch (currentToken) {
                    case pacmanSymbol :
                        pacmanX = i;
                        pacmanY = heightCounter;
                        break;
                    case ghostSymbol :
                        ghostsCoordsX[ghostsFound] = i;
                        ghostsCoordsY[ghostsFound] = heightCounter;
                        ghostsFound++;
                        break;
                    case wallSymbol :
                        fieldItems[i][heightCounter] = true;
                        break;
                    case emptySpaceSymbol :
                        fieldItems[i][heightCounter] = false;
                        break;
                    default :
                        throw new IOException();
                }
            }
            heightCounter++;
        }
    }

    public int getHieght() {
        return height;
    }

    public int getWidth() {
        return width;
    }

    public int getPacmanX() {
        return pacmanX;
    }

    public int getPacmanY() {
        return pacmanY;
    }

    public boolean[][] getField() {
        return fieldItems;
    }

    public int[] getGhostsCoordsX() {
        return ghostsCoordsX;
    }

    public int[] getGhostsCoordsY() {
        return ghostsCoordsY;
    }

    private final char pacmanSymbol = '(';
    private final char wallSymbol = '*';
    private final char emptySpaceSymbol = '-';
    private final char ghostSymbol = 'x';

    private int pacmanX = 0;
    private int pacmanY = 0;
    private int height = 0;
    private int width = 0;
    private boolean[][] fieldItems;
    private int[] ghostsCoordsX = new int[4];
    private int[] ghostsCoordsY = new int[4];
}
