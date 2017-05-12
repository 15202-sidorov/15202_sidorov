
import Map_Items.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.Timer;
import java.util.TimerTask;

public class main {
    public static void main(String args[])  {
        EventQueue.invokeLater( new Runnable() {
            public void run() {
                PacmanGame driver = new PacmanGame();
            }
        });
    }
}

class PacmanGame extends JFrame{
    public PacmanGame() {
        setTitle("Pacman");
        setResizable(false);
        setLayout(null);
        setSize(width,height);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        FieldPanel mainField = new FieldPanel();
        getContentPane().add(mainField);
        setVisible(true);
        mainField.startGame();

    }

    private int width = 600;
    private int height = 625;
}






