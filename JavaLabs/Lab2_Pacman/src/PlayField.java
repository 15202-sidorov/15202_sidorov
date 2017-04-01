import Map_Items.*;

import java.io.File;

/**
    Interface : can change pacman's direction only
    What playfield does :
        -- Controls the game
        -- Controls ghosts
        -- Counts HP and so forth
 */

public class PlayField {
    public PlayField() {
        //ghosts are born in the center of the map (find awailable place)
        //pacman is on the (0,0) coordinate or right ...

    }

    public void changePacmanDirection(MapItem.Direction d) {
        pacman.changeDirection(d);
    }



    private void setField(File file) {

    }

    private MapItem[] field;
    private int HP;
    private GhostUnit[] ghosts;
    private PacmanUnit pacman;

    private final int width = 20;
    private final int height = 20;
    private final int ghostsCount = 4;

    private final int X_Ghost_Birth;
    private final int Y_Ghost_Birth;

    private final int X_Pacman_Start;
    private final int Y_Pacman_Start;
}
