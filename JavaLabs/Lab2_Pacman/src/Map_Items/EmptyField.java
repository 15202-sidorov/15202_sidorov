package Map_Items;

/**
 * Created by ilia on 01.04.17.
 */

public class EmptyField extends  Still {
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

    private boolean coin;

}
