import Map_Items.EmptyField;
import Map_Items.Movable;
import Map_Items.StillItem;

import javax.swing.*;
import javax.swing.Timer;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.*;

public class FieldPanel extends JPanel {
    FieldPanel() {
        setOpaque(true);
        setSize(width, height);
        setLayout(null);
        setFocusable(true);
        setBorder(BorderFactory.createLineBorder(Color.BLACK));
        setBackground(Color.BLACK);
        addKeyListener(new DirectionHandler());
        refreshLogicLocations();
        currentPacmanLocation = pacmanLocation;
        for (int i = 0; i < GHOST_COUNT; i++) {
            currentGhostLocation[i] = ghostLocation[i];
        }

        try {
            getImages();
        }
        catch(IOException ex) {
            System.out.println("could not load properites");
        }
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        setMap(g);
        setUnits(g);
    }

    private void setMap(Graphics g) {
        StillItem[][] stillItemsFromGame = logicCore.getMap();
        EmptyField currentEmptyField;
        g.setColor(Color.BLUE);
        for (int i = 0; i < logicCore.getWidth(); i++) {
            for (int j = 0; j < logicCore.getHeight(); j++) {
                try {
                    if (stillItemsFromGame[i][j].getClass() != Class.forName("Map_Items.EmptyField")) {
                        g.fillRect(i*cellWidth, j*cellHeight, cellWidth, cellHeight);
                    }
                    else {
                        currentEmptyField = (EmptyField) stillItemsFromGame[i][j];
                        if (currentEmptyField.hasCoin()) {
                            g.setColor(Color.CYAN);
                            g.fillOval(i * cellWidth + (cellWidth / 2), j * cellHeight + (cellHeight/2), cellWidth / 10, cellHeight / 10);
                            g.setColor(Color.BLUE);
                        }
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
        for (int i = 0; i < GHOST_COUNT; i++) {
            g.drawImage(workingGhostsImage[i],currentGhostLocation[i].x,currentGhostLocation[i].y,null);

        }
    }

    public void startGame() {
        synchronized (this) {
            mainTimer.scheduleAtFixedRate(new doEachItartion(), 0, MSEC_PER_ITARATION);
            littleTimer.scheduleAtFixedRate(new doMove(), 0, MSEC_PER_ITARATION / cellWidth);
        }
    }

    private void getImages() throws IOException {
        int scaledImageSize = 0;
        if (cellHeight > cellWidth) {
            scaledImageSize = cellWidth;
        }
        else {
            scaledImageSize = cellHeight;
        }

        BufferedImage originalPacmanImage;
        BufferedImage[] originalGhostImage = new BufferedImage[GHOST_COUNT];
        String resultFileName = "pacman";
        switch(logicCore.getPacman().getDirection()) {
            case RIGHT :
                resultFileName += "right";
                break;
            case LEFT :
                resultFileName += "left";
                break;
            case UP :
                resultFileName += "up";
                break;
            case DOWN :
                resultFileName += "down";
                break;
            default:
                resultFileName += "right";
                break;
        }

        switch (pacmanMouth) {
            case OPEN:
                resultFileName += ".png";
                break;
            case CLOSED:
                resultFileName = "pacmanclosed.png";
                break;
        }

        originalPacmanImage = PacmanImageFactory.getImage(resourcePath + resultFileName);

        workingPacmanImage = originalPacmanImage.getScaledInstance(scaledImageSize,scaledImageSize,Image.SCALE_DEFAULT);


        for (int i = 0; i < GHOST_COUNT; i++) {
            switch(logicCore.getGhosts()[i].getDirection()) {
                case RIGHT :
                    resultFileName = "slyde" + (i + 1) + "right.png";
                    break;
                case LEFT :
                    resultFileName =  "slyde" + (i + 1)+ "left.png";
                    break;
                case UP :
                    resultFileName =  "slyde" + (i + 1) + "up.png";
                    break;
                case DOWN :
                    resultFileName = "slyde" + (i + 1) + "down.png";
                    break;
                default:
                    resultFileName = "slyde" + (i + 1) + "right.png";
                    break;
            }
            originalGhostImage[i] = PacmanImageFactory.getImage(resourcePath + resultFileName);
            workingGhostsImage[i] = originalGhostImage[i].getScaledInstance(scaledImageSize,scaledImageSize,Image.SCALE_DEFAULT);
        }
    }

    private void refreshLogicLocations() {
        countPacmanLocation();
        for (int i = 0; i < GHOST_COUNT; i++) {
            countGhostLocation(i);
        }
    }

    private class doEachItartion extends TimerTask {
        public void run() {
            if (pacmankilledFlag) {
                littleTimer.cancel();
                cancel();
            }
            try {
                logicRunner.nextItaration();
                switch(pacmanMouth) {
                    case OPEN:
                        pacmanMouth = PacmanMouthState.CLOSED;
                        break;
                    case CLOSED:
                        pacmanMouth = PacmanMouthState.OPEN;
                        break;
                }
                getImages();
            }
            catch(Exception ex) { System.out.println("Exception caught while itarating"); }
            if (logicCore.getPacman().getHP() < 0) {
                pacmankilledFlag = true;
            }

            refreshLogicLocations();
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

            for (int i = 0; i < GHOST_COUNT; i++) {
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

    private class DirectionHandler extends KeyAdapter {
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

    private final int width = 600;
    private final int height = 600;

    private int cellWidth = width / logicCore.getWidth();
    private int cellHeight = height / logicCore.getHeight();
    private java.util.Timer mainTimer = new java.util.Timer();
    private java.util.Timer littleTimer = new java.util.Timer();
    private java.util.Timer deathAnimationTimer = new java.util.Timer();

    private Point pacmanLocation = new Point();
    private Point[] ghostLocation =  new Point[GHOST_COUNT];

    private Point currentPacmanLocation = new Point();
    private Point[] currentGhostLocation = new Point[GHOST_COUNT];

    private Image workingPacmanImage;
    private Image[] workingGhostsImage = new Image[GHOST_COUNT];
    private enum PacmanMouthState {
        OPEN, CLOSED
    }
    private PacmanMouthState pacmanMouth = PacmanMouthState.OPEN;

    private ImageFactory PacmanImageFactory = new ImageFactory();
    private boolean pacmankilledFlag = false;

    private String resourcePath = "/home/ilia/15202_sidorov/JavaLabs/Lab2_Pacman/resource/";

    final private static int MSEC_PER_ITARATION = 300;
    final private static int GHOST_COUNT = 3;

}