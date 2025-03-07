/* 
객체지향. 우리가 뭘 만들려고 하든 객체부터 만들어야 돼.
뭘 하려고 해도 객체를 만들어야돼.

무조건 객체를 만들어야돼.
객체에는 필드(변수)랑 메서드(함수)가 있어.

실행 메서드

 */

import java.util.ArrayList;

import java.math.BigInteger;    
public class 개수_세기 {
    public static void main(String[] args) {
        
        BigInteger a = new BigInteger("100000000000000000000000");

        BigInteger b = new BigInteger("100000000000000000000000");

        System.out.println(a.add(b));
        System.out.println(a.subtract(b));
        System.out.println(a.multiply(b));

    }
}