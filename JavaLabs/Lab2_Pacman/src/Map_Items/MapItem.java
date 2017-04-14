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
        handleCoordinates();
    }

    public int getX_coordinate() {
        return X_coordinate;
    }

    public int getY_coordinate() {
        return Y_coordinate;
    }

    protected void handleCoordinates() {
        if (X_coordinate < 0) {
            X_coordinate = x_max - 1 ;
        }
        if (Y_coordinate < 0) {
            Y_coordinate = y_max - 1;
        }
        X_coordinate %= x_max;
        Y_coordinate %= y_max;
    }

    protected final int x_max;
    protected final int y_max;

    protected int X_coordinate;
    protected int Y_coordinate;
}
