import java.util.Scanner;
import java.util.Random;

public class 08cns {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter p: ");
        int p = scanner.nextInt();
        System.out.print("Enter g (less than p): ");
        int g = scanner.nextInt();
        System.out.print("Enter Alice's private key (a): ");
        int a = scanner.nextInt();
        int A = (int) Math.pow(g, a) % p;
        System.out.print("Enter Bob's private key (b): ");
        int b = scanner.nextInt();
        int B = (int) Math.pow(g, b) % p;
        System.out.print("Enter the message (integer): ");
        int message = scanner.nextInt();
        Random random = new Random();
        int k = random.nextInt(p - 2) + 1;
        int c1 = (int) Math.pow(g, k) % p;
        int c2 = (message * (int) Math.pow(A, k)) % p;
        int decryptedMessage = (c2 * modInverse((int) Math.pow(c1, b), p)) % p;
        System.out.println("Alice's public key (A): " + A);
        System.out.println("Bob's public key (B): " + B);
        System.out.println("Encrypted Message (c1, c2): (" + c1 + ", " + c2 + ")");
        System.out.println("Decrypted Message: " + decryptedMessage);
        scanner.close();
    }

    private static int modInverse(int a, int m) {
        for (int x = 1; x < m; x++) {
            if ((a * x) % m == 1) {
                return x;
            }
        }
        return -1;
    }
}
