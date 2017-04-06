import Map_Items.*;

public class GameRunner {
    public GameRunner() {
        field = new PlayField();
    }

    public int nextItaration() throws Exception {
        PacmanUnit pacman = field.getPacman();
        GhostUnit[] ghosts = field.getGhosts();
        if ( possibleToMove(pacman) ) {
            pacman.moveForward();
        }
        for (GhostUnit g : ghosts) {
            if (possibleToMove(g)) {
                g.moveForward();
            }
            if (g.getX_coordinate() == pacman.getX_coordinate() ||
                g.getY_coordinate() == pacman.getY_coordinate()) {
                pacman.kill();
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
        int nextX = unit.getX_coordinate() + 1;
        int nextY = unit.getY_coordinate() + 1;
        StillItem[][] map = field.getMap();
        if (map[nextX][nextY].getClass() == Class.forName("Wall")) {
            return false;
        }
        else if (map[nextX][nextY].getClass() == Class.forName("EmptyField")) {
            return true;
        }
        else {
            throw new Exception();
        }
    }
    private PlayField field;
}
