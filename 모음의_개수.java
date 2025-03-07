import java.util.Scanner;

public class 모음의_개수 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (true) {
            String a = sc.nextLine();
            if (a.equals("#")) break;
            int b = 0;
            for (int i = 0; i < a.length(); i++) {
                char c = a.charAt(i);
                if (c == 'a' || c == 'e' || c =='i' || c == 'o' || c == 'u'
                || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                    b++;
                }
            }
            System.out.println(b);
        }
    }
}