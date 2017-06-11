import Map_Items.*;

import java.io.IOException;

/**
    Interface : can change pacman's direction only
    Playfield holds all the resourses the game will need

 */

public class PlayField {
    public PlayField() {
        try {
            getDataFromFile();
        }
        catch (IOException ex ){
            System.out.println("Could not download field");
        }
        setField();
        locateGhosts();
        locatePacman();
    }

    public PacmanUnit getPacman() {
        return pacman;
    }

    public GhostUnit[] getGhosts() {
        return ghosts;
    }

    public StillItem[][] getMap() {
        return field;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    private void getDataFromFile() throws IOException {
        FieldReader dataGetter = new FieldReader(resourceFile);
        width = dataGetter.getWidth();
        height = dataGetter.getHieght();
        fieldItemsDesc = dataGetter.getField();
        X_Pacman_Start = dataGetter.getPacmanX();
        Y_Pacman_Start = dataGetter.getPacmanY();
        X_Ghost_Birth = dataGetter.getGhostsCoordsX();
        Y_Ghost_Birth = dataGetter.getGhostsCoordsY();
    }

    private void locatePacman() {
        pacman = new PacmanUnit(X_Pacman_Start,Y_Pacman_Start,width, height);
    }

    private void locateGhosts() {
        ghosts = new GhostUnit[ghostsCount];
        for (int i = 0; i < ghostsCount; i++) {
            ghosts[i] = new GhostUnit(X_Ghost_Birth[i],Y_Ghost_Birth[i],height,width);
        }
    }

    private void setField() {
        field = new StillItem[width][height];
        EmptyField currentEmptyField;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (fieldItemsDesc[i][j]) {
                    field[i][j] = new Wall(i,j,width,height);
                }
                else {
                    field[i][j] = new EmptyField(i,j,width,height);
                    currentEmptyField = (EmptyField)field[i][j];
                    currentEmptyField.placeCoin();
                    coinCounter++;
                }
            }
        }

    }

    public int getCoins() {
        return coinCounter;
    }

    public void decCoin() {
        coinCounter--;
        return;
    }

    private StillItem[][] field;
    private GhostUnit[] ghosts;
    private PacmanUnit pacman;
    private boolean[][] fieldItemsDesc;

    private int coinCounter = 0;

    private int width;
    private int height;
    private final int ghostsCount = 4;

    private int[] X_Ghost_Birth;
    private int[] Y_Ghost_Birth;
    private int X_Pacman_Start;
    private int Y_Pacman_Start;

    private final String resourceFile = "/home/ilia/15202_sidorov/JavaLabs/Lab2_Pacman/resource/field.txt";

}
