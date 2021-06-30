package Fizz;

public class FizzBuzz {

    public static void computeFizzBuzz(){

        for(int num = 1; num < 101; num ++) {

            if (num > 100 || num < 1) {

                System.out.println("num is not between 1-100");
            } else if (num % 5 == 0 && num % 7 == 0) {
                System.out.println("FizzBuzz");
            } else if (num % 5 == 0) {
                System.out.println("Fizz");
            } else if (num % 7 == 0) {
                System.out.println("Buzz");
            } else System.out.println(num);
        }
    }
    public static void main(String args[]){

        computeFizzBuzz();

    }
}
