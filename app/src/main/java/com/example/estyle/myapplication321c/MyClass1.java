package com.example.estyle.myapplication321c;

/**
 * C调用Java
 */
public class MyClass1 {

    public static String hello(String str) {
        System.out.println("java MyClass1 hello: " + str);
        return "this is " + str;
    }

    public int plus(int a, int b) {
        int plus = a + b;
        System.out.println("java MyClass1 plus: " + plus);
        return plus;
    }
}
