package Map_Items;

/**
 * Created by ilia on 01.04.17.
 */

public abstract class Movable extends MapItem {
    public Movable(int x, int y, int xm, int ym) {
        super(x,y,xm,ym);
    }

    public void moveForward() {
        switch (moves) {
            case DOWN:
                Y_coordinate++;
                break;
            case LEFT:
                X_coordinate--;
                break;
            case RIGHT:
                X_coordinate++;
                break;
            case UP:
                Y_coordinate--;
                break;
        }

        handleCoordinates();
    }

    public void changeDirection( Direction d ) {
        moves = d;
    }

    public void changeDirectionToAnother() {
        switch (moves) {
            case RIGHT :
                moves = Direction.UP;
                break;
            case LEFT :
                moves = Direction.DOWN;
                break;
            case UP :
                moves = Direction.RIGHT;
                break;
            case DOWN :
                moves = Direction.LEFT;
                break;
        }
    }

    public Direction getDirection() {
        return moves;
    }

    public enum Direction {
        RIGHT, LEFT, UP, DOWN
    }

    private Direction moves = Direction.RIGHT;

}
