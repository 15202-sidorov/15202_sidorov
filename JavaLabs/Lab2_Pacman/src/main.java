
import Map_Items.*;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.Timer;
import java.util.TimerTask;

public class main {
    public static void main(String args[])  {
        EventQueue.invokeLater( new Runnable() {
            public void run() {
                PacmanGame driver = new PacmanGame();
                driver.startGame();
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
        setUnits(mainField);
        setMap(mainField);
    }

    public void startGame() {
        Timer t = new Timer();
        t.scheduleAtFixedRate(new doEachItaration(),1000,1000);
        repaint();

    }

    private class doEachItaration extends TimerTask {
        @Override
        public void run() {
            countPacmanLocation();
            countGhostLocation(0);
            try {
                logicRunner.nextItaration();
            } catch (Exception ex) {
                System.out.println("Exception caught while itarating");
                return;
            }
            pacman.setLocation(pacmanLocation);
            ghost[0].setLocation(ghostLocation[0]);
        }
    }

    private class KeyHandler extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            if (e.getKeyCode() == KeyEvent.VK_KP_DOWN) {
                logicRunner.changePacmanDirection(Movable.Direction.DOWN);
            }
        }

    }

    private void setUnits(FieldPanel mainField) {

        try{
            pacman = new UnitPanel(resourcePath+"pacmanright.png",cellWidth,cellHeight);
            ghost[0] = new UnitPanel(resourcePath+"slyde1.png",cellWidth,cellHeight);
            mainField.setSize(width,height);
            mainField.add(pacman);
            mainField.add(ghost[0]);
            countPacmanLocation();
            countGhostLocation(0);
            pacman.setLocation(pacmanLocation);
            ghost[0].setLocation(ghostLocation[0]);
            setVisible(true);
        }
        catch(Exception e){
            System.out.println("UUUps");
        }
    }

    private void setMap(FieldPanel mainField) {
        StillItem[][] stillItemsFromGame = logicCore.getMap();
        for (int i = 0; i < logicCore.getWidth(); i++) {
            for (int j = 0; j < logicCore.getHeight(); j++) {
                try {
                    if (stillItemsFromGame[i][j].getClass() != Class.forName("Map_Items.EmptyField")) {
                        WallPanel wall = new WallPanel(cellWidth, cellHeight);
                        mainField.add(wall);
                        wall.setLocation(new Point(i * cellWidth, j * cellHeight));
                    }
                }
                catch (Exception e) {
                   System.out.println("Ouuups");
               }
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
    private UnitPanel pacman;
    private UnitPanel[] ghost = new UnitPanel[GHOST_COUNT];

    private PlayField logicCore = new PlayField();
    private GameRunner logicRunner = new GameRunner(logicCore);

    private final int width = 900;
    private final int height = 600;

    private int cellWidth = width / logicCore.getWidth();
    private int cellHeight = height / logicCore.getHeight();

    private Point pacmanLocation = new Point();
    private Point[] ghostLocation =  new Point[GHOST_COUNT];

    final private static int GHOST_COUNT = 4;

    final private static String resourcePath = "/home/ilia/Proga/15202_sidorov/JavaLabs/Lab2_Pacman/resource/";
}

class FieldPanel extends JPanel {
    FieldPanel() {
        super(true);
        setOpaque(true);
        setBackground(Color.BLACK);
        setLayout(null);
    }
}

class UnitPanel extends JPanel {
    UnitPanel(String filename,int sizex, int sizey) throws Exception {
        int scalex = sizex;
        int scaley = sizey;
        if (scalex > scaley) {
            scalex = scaley;
        }
        else {
            scaley = scalex;
        }
        BufferedImage imageOriginal = ImageIO.read(new File (filename));
        image = imageOriginal.getScaledInstance(scalex,scaley,Image.SCALE_DEFAULT);
        setBackground(Color.BLACK);
        setSize(sizex,sizey);
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image,2,2,null);
    }

    private Image image;
}

class WallPanel extends JPanel {
    WallPanel(int x, int y) {
        super();
        setSize(x,y);
    }
}






