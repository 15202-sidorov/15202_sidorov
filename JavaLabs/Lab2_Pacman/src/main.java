
import Map_Items.*;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;

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
        setPacman(mainField);
        setMap(mainField);
    }

    private void setPacman(FieldPanel mainField) {

        try{
            UnitPanel pacman = new UnitPanel(resourcePath+"pacmanright.png");
            UnitPanel ghost1 = new UnitPanel(resourcePath+"slyde1.png");
            handleSize(mainField,width,height);
            mainField.add(pacman);
            mainField.add(ghost1);
            pacman.setLocation(pacmanLocation);
            ghost1.setLocation(ghostLocation);
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
                        WallPanel spacePanel = new WallPanel(cellWidth, cellHeight);
                        mainField.add(spacePanel);
                        spacePanel.setLocation(i * cellWidth, j * cellHeight);
                    }
                }
                catch (Exception e) {
                   System.out.println("Ouuups");
               }
            }
        }
    }

    private void handleSize(JPanel component,int w, int h) {
        Insets insets = component.getInsets();
        component.setSize(insets.right + insets.left + w,insets.top + insets.bottom + h);
    }

    private PlayField logicCore = new PlayField();

    private final int width = 900;
    private final int height = 600;

    private int cellWidth = width / logicCore.getWidth();
    private int cellHeight = height / logicCore.getHeight();

    private Point pacmanLocation = new Point(logicCore.getPacman().getX_coordinate() * cellWidth,
                                            logicCore.getPacman().getY_coordinate() * cellHeight);
    private Point ghostLocation =  new Point(logicCore.getGhosts()[0].getX_coordinate() * cellWidth,
                                            logicCore.getGhosts()[0].getY_coordinate() * cellHeight);

    private String resourcePath = "/home/ilia/Proga/15202_sidorov/JavaLabs/Lab2_Pacman/resource/";
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
    UnitPanel(String filename) throws Exception {
        image = ImageIO.read(new File (filename));
        handleSize(image.getWidth(),image.getHeight());
        setBackground(Color.BLACK);
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image,2,2,null);
    }

    private void handleSize(int w, int h) {
        Insets insets = getInsets();
        setSize(insets.right + insets.left + w,insets.top + insets.bottom + h);
    }


    private BufferedImage image;
}

class WallPanel extends JPanel {
    WallPanel(int x, int y) {
        super();
        handleSize(x,y);
    }

    private void handleSize(int w, int h) {
        Insets insets = getInsets();
        setSize(insets.right + insets.left + w,insets.top + insets.bottom + h);
    }

}






