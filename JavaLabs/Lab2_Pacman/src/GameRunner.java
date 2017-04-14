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

            if ( possibleToMove(ghosts[0]) ) {
                ghosts[0].moveForward();
            }
            else {
                ghosts[0].changeDirectionToAnother();
            }
            if (ghosts[0].getX_coordinate() == pacman.getX_coordinate() &&
                ghosts[0].getY_coordinate() == pacman.getY_coordinate()) {
                System.out.println("Ou");
            pacman.kill();
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
        byte dx = 0;
        byte dy = 0;
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

    private PlayField field;
}
