import java.net.*;
import java.io.*;
import java.util.Scanner;

public class DateClient {
    public static void main(String[] args) {
        try {
            /* make connection to server socket */
            Socket sock = new Socket("127.0.0.1", 6013);

            /* Initial Prompt */
            System.out.println("Hello! We love to know more about our clients.");
            System.out.println("Please enter the following information to help provide you our best service.");

            /* Declaration and initialization of console input variable */
            Scanner input = new Scanner(System.in);
            /* Declare Array of Strings to send to Server */
            String info;
            /* Take input from Client to send to Server */
            System.out.print("\nEnter your name: ");
            info = input.nextLine();

            /* Write the data entry into the server socket */
            PrintWriter printout = new PrintWriter(sock.getOutputStream(), true);
            printout.println(info);

            System.out.println("Thank you for providing the information! ");
            System.out.println("\nHave a wonderful day!\n\n");
            /* read the date from the socket */

            /* Read server response through the socket */

            /* declaration and initialization of variable used to read from the server */
            BufferedReader bin = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            /* Declaration of variable to hold information read from the server */
            String line;
            /* Read from the server */
            while ( (line = bin.readLine()) != null)
                System.out.println(line);

            /* Close all connections to socket, readers, and writers */
            printout.close();
            bin.close();
            sock.close();
        } catch(IOException ioe) {
            System.err.println(ioe);
        }
    }
}
