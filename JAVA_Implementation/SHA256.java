import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;


public class SHA256 {

    public static void main(String[] args) throws NoSuchAlgorithmException{
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        Scanner sc = new Scanner(System.in);
        String input = sc.nextLine();
        byte[] messageDigest = md.digest(input.getBytes());
        BigInteger no = new BigInteger(1, messageDigest);
        for (byte b : messageDigest) {
                System.out.printf("%02x", b);
            }
                    
    }
}