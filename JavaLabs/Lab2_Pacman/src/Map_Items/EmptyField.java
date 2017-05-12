package Map_Items;

/**
 * Created by ilia on 01.04.17.
 */

public class EmptyField extends  StillItem {
    public EmptyField(int x, int y,int xm, int ym) {
        super(x,y,xm,ym);
        coin = false;
    }

    public void placeCoin() {
        coin = true;
    }

    public void takeCoin() {
        coin = false;
    }

    public boolean hasCoin() {
        return coin;
    }

    private boolean coin;

}
