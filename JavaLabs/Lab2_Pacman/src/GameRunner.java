import Map_Items.*;
import static java.lang.Math.abs;


public class GameRunner {
    public GameRunner(PlayField field_v) {
        field = field_v;
    }

    public int nextItaration() throws Exception {
        PacmanUnit pacman = field.getPacman();
        GhostUnit[] ghosts = field.getGhosts();
        if ( possibleToMove(pacman) ) {
            pacman.moveForward();
        }
        for (int i = 0; i < 3; i++) {
            if (possibleToMove(ghosts[i])) {
                ghosts[i].moveForward();
            } else {
                ghosts[i].changeDirectionToAnother();
            }
            if (ghosts[i].getX_coordinate() == pacman.getX_coordinate() &&
                    ghosts[i].getY_coordinate() == pacman.getY_coordinate()) {
                System.out.println("Ou");
                pacman.kill();
            } else if ((ghosts[i].getX_coordinate() + dx == pacman.getX_coordinate()) &&
                    ghosts[i].getY_coordinate() + dy == pacman.getY_coordinate()) {
                if (ghosts[i].getDirection() != pacman.getDirection()) {
                    System.out.println("Ouuuu");
                    pacman.kill();
                }
            }
        }
        return pacman.getHP();
    }

    public void changePacmanDirection(Movable.Direction d) {
        field.getPacman().changeDirection(d);
    }

    public PlayField getPlayField() {
        return field;
    }

    private boolean possibleToMove(Movable unit) throws Exception {
        Movable.Direction d = unit.getDirection();
        dx = 0;
        dy = 0;
        switch(d) {
            case RIGHT :
                dx = 1;
                break;
            case LEFT :
                dx = -1;
                break;
            case DOWN :
                dy = 1;
                break;
            case UP :
                dy = -1;
                break;
        }

        int nextX = abs((unit.getX_coordinate() + dx) % field.getWidth());
        int nextY = abs((unit.getY_coordinate() + dy) % field.getHeight());
        StillItem[][] map = field.getMap();
        try {
            System.out.println(map[nextX][nextY].getClass().toString());
            if (map[nextX][nextY].getClass() == Class.forName("Map_Items.EmptyField")) {
                return true;
            } else {
                return false;
            }
        } catch (Exception e) {
            System.out.println("Class Not found");
            throw new Exception();
        }
    }

    //direction in which unit is movin'
    private int dy = 0;
    private int dx = 0;
    private PlayField field;
}
