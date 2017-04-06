package Map_Items;

public class PacmanUnit extends Movable {
    public PacmanUnit(int x, int y, int xm, int ym) {
        super(x,y, xm, ym);
    }

    public int getHP() {
        return HP;
    }

    public void kill() {
        HP--;
    }

    private int HP = 4;

}
