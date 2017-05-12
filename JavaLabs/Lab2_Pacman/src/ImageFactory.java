import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

/**
    class returns imagees for pacman
 */

public class ImageFactory {
    public ImageFactory() {
    }

    public BufferedImage getImage(String fileName) throws IOException {
        if (!imageStore.containsKey(fileName)) {
            imageStore.put(fileName, ImageIO.read(new File(fileName)));
        }

        return imageStore.get(fileName);
    }

    private Map<String,BufferedImage> imageStore = new HashMap<String, BufferedImage>();

}
