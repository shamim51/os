import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;

public class DateServer {
    public static void main(String[] args) {
        /* Welcome to the DateTime Server */
        System.out.println("Welcome to the Date Server\n\n");
        System.out.println("Listening for Requests.........\n");

        try {
            // Create a socket connection with localhost and port
            ServerSocket sock = new ServerSocket(6013);
            sock.setReuseAddress(true);

            /* now listen for connections */
            for(int count = 0; true; count++) {
                Socket clientSock = sock.accept();

                /* Create a ClientThread object */
                ClientThread client = new ClientThread(clientSock, count);

                /* Create threads to deal with multiple clients concurrently */
                new  Thread(client).start();

                /* close the socket and resume listening for connection */
                //clientSock.close();
            }
        } catch (IOException ioe) {
            System.err.println(ioe);
        }

    }
}

/*
 javac .\DateServer.java .\ClientThread.java
 java DateServer

 javac .\DateClient.java
 java DateClient
 */