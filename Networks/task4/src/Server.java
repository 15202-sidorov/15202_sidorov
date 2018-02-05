import java.nio.ByteBuffer;
import java.nio.charset.Charset;

public class Server {
    public static void main( String[] args ) {
        try {
            MYServerSocket socket = new MYServerSocket(8000);
            MYClientSocketOnServerSide clientSocket = socket.accept();
            clientSocket.send("Hello world00000000000000sdf;sdjk;sljd;lkcvjboierjkjxc;lkvjiojsdljkoijwklxcjv;lkj".getBytes());
            clientSocket.send("Another hello there".getBytes());
            byte[] data = clientSocket.receive();
            System.out.println(Charset.defaultCharset().decode(ByteBuffer.wrap(data)));
            clientSocket.send("123543dfs;ljkdf".getBytes());

            clientSocket.close();
        }
        catch ( Exception ex ) {
            ex.printStackTrace();
        }
    }
}
