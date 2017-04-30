
import Map_Items.*;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
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
        setSize(width,height);
        setTitle("Pacman");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        FieldPanel mainField = new FieldPanel();
        getContentPane().add(mainField);
        //mainField.startGame();
        setVisible(true);
    }

    private int width = 900;
    private int height = 600;
}

class FieldPanel extends JPanel {
    FieldPanel() {
        setSize(width,height);
        setOpaque(true);
        setLayout(null);
        countPacmanLocation();
        countGhostLocation(0);
        BufferedImage originalPacmanImage;
        BufferedImage originalGhostImage;
        try {
            originalPacmanImage = ImageIO.read(new File(resourcePath + "pacmanright.png"));
            originalGhostImage = ImageIO.read(new File(resourcePath + "slyde1.png"));
        }
        catch(IOException ex){
            System.out.println("IOException caught while reading imagies");
            return;
        }

        int scaledImageSize = 0;
        if (originalPacmanImage.getHeight() > originalPacmanImage.getWidth()) {
            scaledImageSize = originalPacmanImage.getWidth();
        }
        else {
            scaledImageSize = originalPacmanImage.getHeight();
        }

        workingPacmanImage = originalPacmanImage.getScaledInstance(scaledImageSize,scaledImageSize,Image.SCALE_DEFAULT);
        workingGhostsImage[0] = originalGhostImage.getScaledInstance(scaledImageSize,scaledImageSize,Image.SCALE_DEFAULT);

    }

    public void paintComponent(Graphics g) {
        setMap(g);
        setUnits(g);
    }

    private void setMap(Graphics g) {
        StillItem[][] stillItemsFromGame = logicCore.getMap();
        g.setColor(Color.DARK_GRAY);
        for (int i = 0; i < logicCore.getWidth(); i++) {
            for (int j = 0; j < logicCore.getHeight(); j++) {
                try {
                    if (stillItemsFromGame[i][j].getClass() != Class.forName("Map_Items.EmptyField")) {
                        g.fillRect(i*cellWidth, j*cellHeight, cellWidth, cellHeight);
                    }
                }
                catch (ClassNotFoundException ex) {
                    System.out.println("Class not found exception");
                }
            }
        }
    }

    private void setUnits(Graphics g) {
        g.drawImage(workingPacmanImage,pacmanLocation.x,pacmanLocation.y,null);
        g.drawImage(workingGhostsImage[0],ghostLocation[0].x,ghostLocation[0].y,null);
    }

    private class KeyHandler extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            switch(e.getKeyCode()) {
                case KeyEvent.VK_DOWN :
                    logicCore.getPacman().changeDirection(Movable.Direction.DOWN);
                    break;
                case KeyEvent.VK_UP :
                    logicCore.getPacman().changeDirection(Movable.Direction.UP);
                    break;
                case KeyEvent.VK_RIGHT :
                    logicCore.getPacman().changeDirection(Movable.Direction.RIGHT);
                    break;
                case KeyEvent.VK_LEFT :
                    logicCore.getPacman().changeDirection(Movable.Direction.LEFT);
                    break;
            }
        }
    }

    private void countPacmanLocation() {
        pacmanLocation = new Point(logicCore.getPacman().getX_coordinate() * cellWidth,
                logicCore.getPacman().getY_coordinate() * cellHeight);
    }

    private void countGhostLocation(int i) {
        ghostLocation[i] = new Point(logicCore.getGhosts()[i].getX_coordinate() * cellWidth,
                logicCore.getGhosts()[i].getY_coordinate() * cellHeight);
    }

    private PlayField logicCore = new PlayField();
    private GameRunner logicRunner = new GameRunner(logicCore);

    private final int width = 900;
    private final int height = 600;

    private int cellWidth = width / logicCore.getWidth();
    private int cellHeight = height / logicCore.getHeight();
    private Timer mainTimer = new Timer();

    private Point pacmanLocation = new Point();
    private Point[] ghostLocation =  new Point[GHOST_COUNT];

    private Image workingPacmanImage;
    private Image[] workingGhostsImage = new Image[GHOST_COUNT];

    final private static int MSEC_PER_ITARATION = 1000;
    final private static int GHOST_COUNT = 4;
    final private static String resourcePath = "/home/ilia/15202_sidorov/JavaLabs/Lab2_Pacman/resource/";
}






