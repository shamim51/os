import java.net.Socket;
import java.io.PrintWriter;

public class ClientThread implements Runnable {

    private Socket sock =null;
    private int counter;

    public ClientThread() {
        this(null);
    }

    public ClientThread(Socket sock) {
        this(sock, 0);
    }

    public ClientThread(Socket sock, int counter) {
        this.sock = sock;
        this.counter = counter;
    }

    @Override
    public void run() {
        try {
            /* Write the current date and time to the client through the server */
            PrintWriter printout = new PrintWriter(sock.getOutputStream(), true);
            printout.println(new java.util.Date().toString());
            printout.close();
            System.out.println("Printing to client-" + (counter+1) + " successful!");
            sock.close();
        } catch(Exception exception) {
            System.err.println(exception);
        } finally {
            System.out.println("Server Message Successful!\n");
            System.out.println("Listening for Requests.........");
        }
    }
}
