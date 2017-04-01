package Map_Items;

/**
 * Created by ilia on 01.04.17.
 */
public class GhostUnit extends Movable {
    public GhostUnit(int x, int y, int xm, int ym) {
        super(x,y,xm,ym);
    }

    public void changeState() {
        if (state == State.ALIVE) {
            state = State.DEAD;
        }
        else {
            state = State.ALIVE;
        }
    }

    public State getState() {
        return state;
    }

    public enum State {
        DEAD, ALIVE
    }

    public void replaceOnBirthSpot(int x, int y) {
        X_coordinate = x;
        Y_coordinate = y;
        handleCoordinates();
    }

    private State state;
}
