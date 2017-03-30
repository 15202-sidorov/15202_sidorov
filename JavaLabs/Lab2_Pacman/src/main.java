/**
 * Created by ilia on 30.03.17.
 */

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;

public class main {
    public static void main(String args[]) {
        EventQueue.invokeLater(new Runnable(){

            public void run() {
                Pacman driver = new Pacman();
            }
        });


    }
}

class Pacman extends JFrame {
    public Pacman() {
        setContentPane(new DrawPane());
        setTitle(name);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500,500);
        setVisible(true);
    }

    class DrawPane extends JPanel {
        public void paintComponent(Graphics g) {
            g.drawRect(50,50,50,50);
        }
    }

    private final String name = "Pacman";
    private final int X_size = 500;
    private final int Y_size = 500;
}


