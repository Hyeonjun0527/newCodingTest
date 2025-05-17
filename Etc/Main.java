
// 방금 파이썬 했을때 string타입의 a에 스플릿 있는게 이해가 안가지
// 내가 Car 타입을 만들 수 있어. 나는 어떤 타입이든 만들 수 있어.
// Car에는brand, speed가 존재한다라는 규칙을 만든거야.
// 프로그래밍언어는 세상에 있는거를 컴퓨터에 만든다야.
// 내가 지금 컴퓨터에 자동차라는 개념을 만들엇어. 이게 존나 대단한거지. 놀라운거지.

// 이전에 배웠을때 a.split()얘는 왜 a를 안바꾸지? string을 list로 바꾸는 놈.


// b = a.split()
class Car {
    String brand;
    int speed;
    int year;

    public Car() {

    }
    //생성자
    public Car(String brand, int speed, int year) {
        this.brand = brand;
        this.speed = speed;
        this.year = year;
    }

    public void setBrand(String newBrand) {
        this.brand = newBrand;
    }

    public String getBrand() {
        return brand;
    }
}

public class Main{
    public static void main(String[] args) {


        Car car1 = new Car("현대자동차",300,2025);//"카"라는 객체를 생성한거야. "카" 타입의 무언가를 만들었어.
        //사람 생명 손 발 눈 코 뇌 귀 내장 심장 하나도 없는거야;
    
        System.out.println("브랜드 명 : "+car1.brand + "\n속도 : " + car1.speed + "\n년도 : " + car1.year);

        Car car2 = new Car();//"카"라는 객체를 생성한거야. "카" 타입의 무언가를 만들었어.
        
        car2.brand = "벤틀리";
        car2.speed = 1000;
        car2.year = 2025;
    
        System.out.println("브랜드 명 : "+car1.brand + "\n속도 : " + car1.speed + "\n년도 : " + car1.year);

        car1.setBrand("삼성자동차");
        
        
        System.out.println("브랜드 명 : "+car1.brand + "\n속도 : " + car1.speed + "\n년도 : " + car1.year);

        car1.getBrand();
        car1.getBrand();
        car1.getBrand();
        car1.getBrand();
        car1.getBrand();
        car1.getBrand();

    }
}