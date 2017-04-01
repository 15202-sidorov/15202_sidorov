package Map_Items;

/**
 Wall is the part of the map through which no units can go
 */

public class Wall extends MapItem {
    public Wall(int x, int y, int xm, int ym) {
        super(x,y,xm,ym);
    }

    @Override
    public void changeDirection(Direction d) {
        moves = Direction.STILL;
    }

}
