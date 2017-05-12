import javax.swing.*;
import java.awt.*;


public class Menu extends JPanel{
    public Menu() {
        setSize(200,200);
    }

    @Override
    public void paintComponent(Graphics g) {

    }
    private JLabel StartGameLabel = new JLabel("Play");
    private JLabel ExitGame = new JLabel("Exit");
    private int height = 200;
    private int width = 200;
}
