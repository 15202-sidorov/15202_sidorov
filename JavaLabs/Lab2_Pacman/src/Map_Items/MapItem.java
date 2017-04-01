package Map_Items;

/**
 All object on a map inherit this type
 It describes the location of the Item on the map
 It also indicates, where the Item moves(or stays still)
 */

public abstract class MapItem {
    public MapItem(int x, int y, int xm, int ym) {
        X_coordinate = x;
        Y_coordinate = y;
        x_max = xm;
        y_max = ym;
        moves = Direction.STILL;
    }

    public void changeDirection(Direction d) {
        moves = d;
    }

    public enum Direction {
        RIGHT, LEFT,
        UP, DOWN, STILL
    }

    protected void handleCoordinates() {
        X_coordinate %= x_max;
        Y_coordinate %= y_max;
    }

    protected final int x_max;
    protected final int y_max;

    protected Direction moves;
    protected int X_coordinate;
    protected int Y_coordinate;
}
