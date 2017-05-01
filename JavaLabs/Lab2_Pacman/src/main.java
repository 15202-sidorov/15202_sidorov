
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
        mainField.startGame();
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
        setFocusable(true);
        addKeyListener(new KeyHandler());
        countPacmanLocation();
        countGhostLocation(0);
        currentPacmanLocation = pacmanLocation;
        for (int i = 0; i < GHOST_COUNT; i++) {
            currentGhostLocation[i] = ghostLocation[i];

        }
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
        if (cellHeight > cellWidth) {
            scaledImageSize = cellWidth;
        }
        else {
            scaledImageSize = cellHeight;
        }

        workingPacmanImage = originalPacmanImage.getScaledInstance(scaledImageSize,scaledImageSize,Image.SCALE_DEFAULT);
        workingGhostsImage[0] = originalGhostImage.getScaledInstance(scaledImageSize,scaledImageSize,Image.SCALE_DEFAULT);
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
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
        g.drawImage(workingPacmanImage,currentPacmanLocation.x,currentPacmanLocation.y,null);
        g.drawImage(workingGhostsImage[0],currentGhostLocation[0].x,currentGhostLocation[0].y,null);
    }

    void startGame() {
        synchronized (this) {
           mainTimer.scheduleAtFixedRate(new doEachItartion(), 0, MSEC_PER_ITARATION);
            littleTimer.scheduleAtFixedRate(new doMove(), 0, MSEC_PER_ITARATION / cellWidth);
        }
    }

    private class doEachItartion extends TimerTask {
        public void run() {
            try {
                logicRunner.nextItaration();
            }
            catch(Exception ex) { System.out.println("Exception caught while itarating"); }

            countPacmanLocation();
            for (int i = 0; i < GHOST_COUNT; i++) {
                countGhostLocation(i);
            }
            repaint();
        }
    }

    private class doMove extends TimerTask {
        public void run() {
            if ((pacmanLocation.x == 0) || (pacmanLocation.x == (logicCore.getWidth() - 1)*cellWidth )) {
                currentPacmanLocation.x = pacmanLocation.x;
            }
            else if (pacmanLocation.x > currentPacmanLocation.x) {
                currentPacmanLocation.x++;
            }
            else if (pacmanLocation.x < currentPacmanLocation.x) {
                currentPacmanLocation.x--;
            }

            if ((pacmanLocation.y == 0) || (pacmanLocation.y == (logicCore.getHeight() - 1)*cellHeight )) {
                currentPacmanLocation.y = pacmanLocation.y;
            }
            else if (pacmanLocation.y > currentPacmanLocation.y) {
                currentPacmanLocation.y++;
            }
            else if (pacmanLocation.y < currentPacmanLocation.y) {
                currentPacmanLocation.y--;
            }

            for (int i = 0; i < 1; i++) {
                if ((ghostLocation[i].x == 0) || (ghostLocation[i].x == (logicCore.getWidth() - 1)*cellWidth )) {
                    currentGhostLocation[i].x = ghostLocation[i].x;
                }
                else if (ghostLocation[i].x > currentGhostLocation[i].x) {
                    currentGhostLocation[i].x++;
                }
                else if (ghostLocation[i].x < currentGhostLocation[i].x) {
                    currentGhostLocation[i].x--;
                }

                if ((ghostLocation[i].y == 0) || (ghostLocation[i].y == (logicCore.getHeight() - 1)*cellHeight )) {
                    currentGhostLocation[i].y = ghostLocation[i].y;
                }
                else if (ghostLocation[i].y > currentGhostLocation[i].y) {
                    currentGhostLocation[i].y++;
                }
                else if (ghostLocation[i].y < currentGhostLocation[i].y) {
                    currentGhostLocation[i].y--;
                }
            }
            repaint();
        }
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
    private Timer littleTimer = new Timer();

    private Point pacmanLocation = new Point();
    private Point[] ghostLocation =  new Point[GHOST_COUNT];

    private Point currentPacmanLocation = new Point();
    private Point[] currentGhostLocation = new Point[GHOST_COUNT];

    private Image workingPacmanImage;
    private Image[] workingGhostsImage = new Image[GHOST_COUNT];

    final private static int MSEC_PER_ITARATION = 450;
    final private static int GHOST_COUNT = 4;
    final private static String resourcePath = "/home/ilia/15202_sidorov/JavaLabs/Lab2_Pacman/resource/";
}






