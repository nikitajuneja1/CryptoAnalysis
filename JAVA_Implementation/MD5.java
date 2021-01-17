import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class MD5 {

    public static void main(String[] args) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("MD5");
        Scanner sc = new Scanner(System.in);
        //Taking the input from the user
        String input = sc.nextLine();
        //digest() method is called to calculate the message digest of the input
        //it returns a byte array
        byte[] messageDigest = md.digest(input.getBytes());
        for (byte b : messageDigest) {
                System.out.printf("%02x", b);
            }   
    }
}