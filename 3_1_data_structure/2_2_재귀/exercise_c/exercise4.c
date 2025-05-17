/* gcd_euclid_nolabs.c ― 유클리드 호제법으로 최대공약수 구하기
   (stdlib.h·labs 미사용 버전) */
//    gcd(a,b) = gcd(b,a%b)야

   #include <stdio.h>
   long gcd(long a, long b)
   {
   
       /* (0,0) 예외 처리 */
       if (a == 0 && b == 0)
           return 0;
   
       /* 전통적(비재귀) 유클리드 호제법 */
       while (b != 0) {
           long r = a % b;
           a = b;
           b = r;
       }
       return a;   /* 마지막 남은 a가 최대공약수 */
   }
   
   int main(void)
   {
       printf("gcd(48, 12)    = %ld\n",  gcd(48, 12));
       printf("gcd(270, 192)  = %ld\n",  gcd(270, 192));
       printf("gcd(2, 2)      = %ld\n",  gcd(2, 2));
       printf("gcd(5, 7)      = %ld\n",  gcd(5, 7));
       printf("gcd(1, 2)      = %ld\n",  gcd(1, 2));
       printf("gcd(-42, 56)   = %ld\n",  gcd(-42, 56));
       printf("gcd(0, 0)      = %ld\n",  gcd(0, 0));
   
       return 0;
   }
   