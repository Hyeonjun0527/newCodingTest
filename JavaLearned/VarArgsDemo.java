// VarArgsDemo.java
public class VarArgsDemo {

    /** 0개 이상 문자열을 받아 콘솔에 출력 */
    static void printAll(String... words) {
        System.out.println("개수 = " + words.length);
        for (String w : words) {
            System.out.println("  • " + w);
        }
    }

    /** 0개 이상 정수를 더한 결과 반환 */
    static int sum(int... numbers) {
        int acc = 0;
        for (int n : numbers) acc += n;
        return acc;
    }

    /** var-args 오버로딩 충돌·배열 전달 예시 */
    static void demoOverload(String label, String... words) {
        System.out.println(label + " : " + String.join(", ", words));
    }

    public static void main(String[] args) {
        // 1) 인자 여러 개
        printAll("apple", "banana", "cherry");

        // 2) 인자 0개
        printAll();

        // 3) 배열을 그대로 전달
        String[] fruits = {"kiwi", "mango"};
        printAll(fruits);

        // 4) 합계 계산
        System.out.println("sum(1,2,3) = " + sum(1, 2, 3));
        System.out.println("sum()      = " + sum());   // 0

        // 5) 오버로딩·배열 참고
        demoOverload("과일", "포도", "복숭아");
    }
}
