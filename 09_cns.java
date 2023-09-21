import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;
import java.util.Scanner;

public class Exp9 {
    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        // Get the encryption key from the user
        System.out.print("Enter the encryption key (8 characters): ");
        String keyInput = scanner.nextLine();
        // Check if the key is exactly 8 characters long
        if (keyInput.length() != 8) {
            System.out.println("The key must be exactly 8 characters long.");
            return;
        }
        // Convert the key to bytes
        byte[] keyBytes = keyInput.getBytes();
        // Create a DES key specification from the user-provided key
        DESKeySpec desKeySpec = new DESKeySpec(keyBytes);
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");
        SecretKey secretKey = keyFactory.generateSecret(desKeySpec);
        // Create a DES Cipher instance for encryption
        Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding");
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);
        // Get input from the user
        System.out.print("Enter the plaintext: ");
        String plaintext = scanner.nextLine();
        // Encrypt the input
        byte[] encryptedBytes = cipher.doFinal(plaintext.getBytes());
        // Display the encrypted bytes (in hexadecimal format)
        System.out.print("Encrypted text (hexadecimal): ");
        for (byte b : encryptedBytes) {
            System.out.print(String.format("%02X", b));
        }
        System.out.println();
        // Decrypt the encrypted text (optional)
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        byte[] decryptedBytes = cipher.doFinal(encryptedBytes);
        String decryptedText = new String(decryptedBytes);
        System.out.println("Decrypted text: " + decryptedText);
    }
}
