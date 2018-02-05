import java.net.DatagramPacket;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

/*

    Each connection has its own status.
    Status consists of :
        -- Buffer ( Buffer of messages with wrong sequence numbers )
        -- Internet address
        -- Connection status ( see wikipedia )
        -- Bytes ( received / send )

 */

public class ConnectionStatus {
    public ConnectionStatus( InetSocketAddress statusFor ) {
        address = statusFor;
        sessionStatus = Status.CLOSED;
        packetsToHandle = new ArrayBlockingQueue<DatagramPacket>(20);
        isAlive = true;
        sequenceNumber = 0;
    }

    public int getSeq() {
        return sequenceNumber;
    }

    public void incSeq() {
        sequenceNumber++;
    }

    public void setStatus( Status newStatus ) {
        sessionStatus = newStatus;
    }

    public Status getStatus() {
        return sessionStatus;
    }

    public InetSocketAddress getAddress() {
        return address;
    }

    public boolean queueIsEmpty() {
        return packetsToHandle.isEmpty();
    }

    public DatagramPacket pollPacket() throws InterruptedException {
        return packetsToHandle.take();
    }

    public void packetReceived(DatagramPacket packet) {
        isAlive = true;
        packetsToHandle.offer(packet);
    }

    /*
        Returns true if limit is exceeded
    */
    public boolean packetIsLost() {
        packetLostCount++;
        if ( packetLostCount < PACKET_LOSS_MAX_COUNTER ) {
            return false;
        }
        else {
            packetLostCount = 0;
            return true;
        }
    }

    public boolean isAlive;
    private int packetLostCount = 0;

    private InetSocketAddress address;
    private BlockingQueue<DatagramPacket> packetsToHandle;
    private int sequenceNumber;

    private Status sessionStatus;

    public static final int PACKET_LOSS_MAX_COUNTER = 3;
}
