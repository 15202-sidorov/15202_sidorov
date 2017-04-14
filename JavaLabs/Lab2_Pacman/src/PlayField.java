import Map_Items.*;

/**
    Interface : can change pacman's direction only
    Playfield holds all the resourses the game will need

 */

public class PlayField {
    public PlayField() {
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
        //just a test field for now
        field = new StillItem[width][height];
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                field[i][j] = new EmptyField(i,j,width,height);
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                field[i][j] = new Wall(i,j,width,height);
            }
        }

        for (int i = 6; i < 12; i++) {
            for (int j = 7; j < 13; j++) {
                field[i][j] = new Wall(i,j,width,height);
            }
        }

        for (int i = 18; i < 20; i++) {
            for (int j = 0; j < 3; j++) {
                field[i][j] = new Wall(i,j,width, height);
            }
        }
    }

    private StillItem[][] field;
    private GhostUnit[] ghosts;
    private PacmanUnit pacman;

    private final int width = 20;
    private final int height = 20;
    private final int ghostsCount = 4;

    private int[] X_Ghost_Birth = { 8, 9,10,11};
    private int[] Y_Ghost_Birth = {14,14,14,14};

    private int X_Pacman_Start = 4;
    private int Y_Pacman_Start = 4;
}
