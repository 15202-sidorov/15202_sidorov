import Map_Items.*;
import static java.lang.Math.abs;


public class GameRunner {
    public GameRunner(PlayField field_v) {
        field = field_v;
    }

    public int nextItaration() throws Exception {
        PacmanUnit pacman = field.getPacman();
        GhostUnit[] ghosts = field.getGhosts();
        EmptyField currentPacmanField = (EmptyField)field.getMap()[pacman.getX_coordinate()][pacman.getY_coordinate()];
        if (currentPacmanField.hasCoin()) {
            currentPacmanField.takeCoin();
        }

        if ( possibleToMove(pacman) ) {
            pacman.moveForward();
        }
        for (int i = 0; i < 3; i++) {
            while (!possibleToMove(ghosts[i])) {
                dx = ghosts[i].getX_coordinate() - pacman.getX_coordinate();
                dy = ghosts[i].getY_coordinate() - pacman.getY_coordinate();
                if ((ghosts[i].getDirection() == Movable.Direction.LEFT) ||
                    (ghosts[i].getDirection() == Movable.Direction.RIGHT)) {
                    if (abs(dy) < abs(dx)) {
                        if (dy > 0) {
                            ghosts[i].changeDirection(Movable.Direction.UP);
                        }
                        else {
                            ghosts[i].changeDirection(Movable.Direction.DOWN);
                        }
                    }
                    else if (ghosts[i].getDirection() == Movable.Direction.RIGHT) {
                        ghosts[i].changeDirection(Movable.Direction.LEFT);
                    }
                    else {
                        ghosts[i].changeDirection(Movable.Direction.RIGHT);
                    }
                }
                else {
                    if (abs(dx) < abs(dy)) {
                        if (dx > 0) {
                            ghosts[i].changeDirection(Movable.Direction.RIGHT);
                        }
                        else {
                            ghosts[i].changeDirection(Movable.Direction.LEFT);
                        }
                    }
                    else if (ghosts[i].getDirection() == Movable.Direction.UP) {
                        ghosts[i].changeDirection(Movable.Direction.DOWN);
                    }
                    else {
                        ghosts[i].changeDirection(Movable.Direction.UP);
                    }
                }
            }
            ghosts[i].moveForward();
            if (ghosts[i].getX_coordinate() == pacman.getX_coordinate() &&
                    ghosts[i].getY_coordinate() == pacman.getY_coordinate()) {
                pacman.kill();
                System.out.println(pacman.getHP());
            } else if ((ghosts[i].getX_coordinate() + dx == pacman.getX_coordinate()) &&
                    ghosts[i].getY_coordinate() + dy == pacman.getY_coordinate()) {
                if (ghosts[i].getDirection() != pacman.getDirection()) {
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

        int nextX = (unit.getX_coordinate() + dx) % field.getWidth();
        int nextY = (unit.getY_coordinate() + dy) % field.getHeight();
        if (nextX < 0) {
            nextX = field.getWidth() - 1;
        }
        if (nextY < 0) {
            nextY = field.getHeight() - 1;
        }
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
