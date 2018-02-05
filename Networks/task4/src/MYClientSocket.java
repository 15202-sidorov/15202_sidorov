
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.nio.ByteBuffer;
import java.util.Timer;
import java.util.TimerTask;

public abstract class MYClientSocket {
    public MYClientSocket( DatagramSocket serverUDPSocket,
                           ConnectionStatus inputStatus ) {
        currentStatus = inputStatus;
        UDPSocket = serverUDPSocket;
        buffer = ByteBuffer.allocate(BUFFER_SIZE);
        pingTimer = new Timer();
        pingTimer.scheduleAtFixedRate(new checkAliveTask(),1000,1000);
    }

    private class checkAliveTask extends TimerTask {
        public void run() {
            try {
                if ((currentStatus.getStatus() == Status.FIN_RECEIVED) && (currentStatus.queueIsEmpty())) {
                    System.out.println("Connection is closed by the other side and packet queue is empty");
                    closeSession();
                    currentStatus.isAlive = false;
                    currentStatus.setStatus(Status.CLOSED);
                }
                else if (( currentStatus.getStatus() == Status.ESTABLISHED ) && (currentStatus.isAlive)) {
                    currentStatus.isAlive = false;
                }

                /*
                    When no ack is received
                */
                else if ((currentStatus.getStatus() == Status.ESTABLISHED) && (!currentStatus.isAlive) && (packetToSend != null)) {
                    if ( currentStatus.packetIsLost() ) {
                        currentStatus.setStatus(Status.CLOSED);
                    }
                    else {
                        UDPSocket.send(packetToSend);
                    }
                }
            }
            catch( IOException ex ) {
                ex.printStackTrace();
            }
            catch( InterruptedException ex ) {
                Thread.currentThread().interrupt();
            }
        }
    }

    public void send(byte[] dataToSend) throws IOException, InterruptedException {

        if ( currentStatus.getStatus() != Status.ESTABLISHED ) {
            System.out.println("Connection is not established yet");
            return;
        }

        int bytesHandled = 0;
        ByteBuffer tmpBuffer = null;
        byte[] tmpBufferArray = null;
        while ( bytesHandled < dataToSend.length ) {
            if ( bytesHandled + CHUNK_SIZE < dataToSend.length ) {
                tmpBuffer = ByteBuffer.wrap(dataToSend, bytesHandled, CHUNK_SIZE);
                tmpBufferArray = new byte[CHUNK_SIZE];
            }
            else {
                tmpBuffer = ByteBuffer.wrap(dataToSend, bytesHandled, dataToSend.length - bytesHandled);
                tmpBufferArray = new byte[dataToSend.length - bytesHandled];
            }

            tmpBuffer.get(tmpBufferArray);

            System.out.println("Sending " + tmpBufferArray.length + " bytes");
            byte[] data = PacketConstructor.buildDEFAULT(currentStatus.getSeq(), tmpBufferArray);
            packetToSend = new DatagramPacket(data, data.length);
            packetToSend.setSocketAddress(currentStatus.getAddress());
            UDPSocket.send(packetToSend);
            System.out.println("Chunk is send, waiting for ack...");
            DatagramPacket packetReceived = null;
            while (true) {
                packetReceived = currentStatus.pollPacket();
                if (PacketConstructor.getFlag(packetReceived.getData()) == Flags.RST_FLAG) {
                    System.out.println("RESET");
                    currentStatus.setStatus(Status.CLOSED);
                    return;
                }
                if (PacketConstructor.getFlag(packetReceived.getData()) == Flags.ACK_FLAG) {
                    break;
                }
            }
            bytesHandled += tmpBufferArray.length;
            currentStatus.incSeq();
            packetToSend = null;
        }

    }

    public byte[] receive() throws IOException,InterruptedException {
        if ( currentStatus.getStatus() != Status.ESTABLISHED ) {
            System.out.println("Connection is not established yet");
            return null;
        }

        int bytesReceived = 0;
        DatagramPacket packetReceived = null;
        int size = 0;
        while(true) {
            System.out.println("Waiting for chunk");
            packetReceived = currentStatus.pollPacket();

            if (PacketConstructor.getFlag(packetReceived.getData()) == Flags.RST_FLAG) {
                System.out.println("RESET");
                currentStatus.setStatus(Status.CLOSED);
                return null;
            }
            /*
                Wrong sequence handling
             */
            if (currentStatus.getSeq() != PacketConstructor.getSeq(packetReceived.getData())) {
                System.out.println("Wrong sequence number");
                currentStatus.packetReceived(packetReceived);
                continue;
            }

            size = PacketConstructor.getDataSize(packetReceived.getData());

            break;
        }


        byte[] content = PacketConstructor.getData(packetReceived.getData());
        buffer.position(bytesReceived);
        buffer.put(content);

        bytesReceived += size;
        System.out.println("Bytes received : " + bytesReceived);
        byte[] dataInPacket = PacketConstructor.buildACK(currentStatus.getSeq(),bytesReceived,BUFFER_SIZE - bytesReceived);
        packetReceived = new DatagramPacket(dataInPacket, dataInPacket.length);
        packetReceived.setSocketAddress(currentStatus.getAddress());
        UDPSocket.send(packetReceived);
        System.out.println("Ack is send");
        currentStatus.incSeq();

        return content;
    }

    public void close() throws IOException, InterruptedException {
        pingTimer.cancel();
        currentStatus.setStatus(Status.CLOSING);
        System.out.println("Closing connection...");
        byte[] packetData = PacketConstructor.buildFIN(false);
        DatagramPacket packet = new DatagramPacket(packetData, packetData.length);
        packet.setSocketAddress(currentStatus.getAddress());
        UDPSocket.send(packet);
        System.out.println("Waiting for ack...");
        while(true) {
            packet = currentStatus.pollPacket();
            if (PacketConstructor.getFlag(packet.getData()) == (Flags.FIN_FLAG | Flags.ACK_FLAG)) {
                packetData = PacketConstructor.buildFIN(true);
                packet = new DatagramPacket(packetData, packetData.length);
                packet.setSocketAddress(currentStatus.getAddress());
                UDPSocket.send(packet);
                break;
            }

            if (PacketConstructor.getFlag(packet.getData())  == (Flags.RST_FLAG)) {
                System.out.println("RESET");
                currentStatus.setStatus(Status.CLOSED);
                return;
            }
        }
        System.out.println("Client socket is closed");
    }


    protected void closeSession() throws IOException, InterruptedException {
        System.out.println("Closing session");
        if ( currentStatus.getStatus() == Status.ESTABLISHED ) {
            byte[] packetData = PacketConstructor.buildFIN(false);
            DatagramPacket packet = new DatagramPacket(packetData, packetData.length);
            packet.setSocketAddress(currentStatus.getAddress());
            UDPSocket.send(packet);
            currentStatus.setStatus(Status.FIN_WAIT);
            while(true) {
                packet = currentStatus.pollPacket();
                if (PacketConstructor.getFlag(packet.getData()) == (Flags.FIN_FLAG | Flags.ACK_FLAG)) {
                    System.out.println("Session is closed, ending session");
                    packetData = PacketConstructor.buildFIN(true);
                    packet.setData(packetData);
                    packet.setSocketAddress(currentStatus.getAddress());
                    UDPSocket.send(packet);
                    currentStatus.setStatus(Status.CLOSED);
                    break;
                }

                if (PacketConstructor.getFlag(packet.getData()) == Flags.RST_FLAG) {
                    System.out.println("RESET");
                    currentStatus.setStatus(Status.CLOSED);
                    return;
                }
            }
        }
        else if ( currentStatus.getStatus() == Status.FIN_RECEIVED ) {
            byte[] packetData = PacketConstructor.buildFIN(true);
            DatagramPacket packet = new DatagramPacket(packetData, packetData.length);
            packet.setSocketAddress(currentStatus.getAddress());
            UDPSocket.send(packet);
            currentStatus.setStatus(Status.CLOSED);
        }
        else {
            System.out.println("Unable to close session");
            return;
        }


    }

    protected void resetConnection() throws IOException {
        byte[] packetData = PacketConstructor.buildRST();
        DatagramPacket packet = new DatagramPacket(packetData, packetData.length);
        packet.setSocketAddress(currentStatus.getAddress());
        UDPSocket.send(packet);
        System.out.println("Connection is reset");
        currentStatus.setStatus(Status.CLOSED);
    }

    protected ConnectionStatus currentStatus;
    protected DatagramSocket UDPSocket;
    protected Timer pingTimer;
    protected DatagramPacket packetToSend;

    protected ByteBuffer buffer;
    protected static final short BUFFER_SIZE = 1024;
    protected static final short CHUNK_SIZE = 256;

}
