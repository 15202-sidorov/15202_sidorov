package Map_Items;

/**
 * Created by ilia on 01.04.17.
 */
public abstract class Still extends MapItem {
    public Still(int x, int y, int xm, int ym) {
        super(x,y,xm,ym);
    }

    @Override
    public void changeDirection(Direction d) {
        moves = Direction.STILL;
    }
}
