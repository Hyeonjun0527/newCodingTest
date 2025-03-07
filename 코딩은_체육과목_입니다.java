import java.util.Scanner;

public class 코딩은_체육과목_입니다 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        a = (a + 3) / 4;// (int)Math.ceil(a/4)
        // (a/b)올림연산 :::: (a + b - 1) / b
        // 21 / 4 => 5.xxx => 6
        // a가 5로 변함.

        String b = "long int";

        if (a == 1) {// N==4 인 경우임.
            System.out.println(b);
        }
        // System.out.println(a);
        // N==5 ~ 1000인 경우
        // N==5 => (a==2) ==> 1번
        if (a != 1) {
            for (int i = 1; i < a;) {
                b = "long " + b;
                i++;
            }
            System.out.println(b);
        }

    }
}