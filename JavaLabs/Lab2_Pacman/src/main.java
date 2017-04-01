/**
 * Created by ilia on 30.03.17.
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class main {
    public static void main(String args[]) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                Pacman driver = new Pacman();
            }
        });
    }
}

class Pacman extends JFrame {
    Pacman() {
        setContentPane(new DrawPane());
        setTitle(name);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(X_size,Y_size);
        setVisible(true);
    }

    class DrawPane extends JPanel {
        DrawPane() {
            setDoubleBuffered(true);
            this.addMouseListener(new PacmanMouseAdapter());
        }

        public void paintComponent(Graphics g) {
            g.setColor(rectColor);
            g.fillRect(50,50,50,50);
        }
    }

    class PacmanMouseAdapter extends MouseAdapter {
        public void mouseClicked(MouseEvent e) {
            if (Color.BLUE == rectColor) {
                rectColor = Color.BLACK;
            }
            else {
                rectColor = Color.BLUE;
            }
            repaint();
        }
    }

    private final String name = "Pacman";
    private final int X_size = 500;
    private final int Y_size = 500;
    private Color rectColor = Color.BLACK;

}


