package com.company;

public class Main {
    static  int answer;
    static int maxValue;
    static int correctAnswer;

    private static void sayHello() throws InterruptedException {
        Thread threads[] = new Thread[10];

        Runnable runnable= ()->{
            for (int i = 0; i < 100; i++){
                //System.out.println("hello number "+i+" from thread number "+Thread.currentThread().getId());
            }
        };

        for (int i = 0; i < 10; i++) {
            threads[i] = new Thread(runnable);
            threads[i].start();
        }
        for (int i = 0; i < 10; i++) {
            threads[i].join();
        }

    }

    private static void badSum() throws InterruptedException {
        answer = 0;
        maxValue = 40000;
        int numThreads = 12;
        Thread threads[] = new Thread[numThreads];
        for (int i = 0; i < numThreads; i++) {
            int finalI = i;
            Thread t = new Thread(()->{
                int startNum = finalI * maxValue / numThreads;
                int maxNum = (Math.min((finalI + 1) * maxValue / numThreads, maxValue));
                for (int j = startNum; j < maxNum; j++) {
                    answer += j;
                }
            });
            threads[i] = t;
        }

        for (Thread t: threads) {
            t.start();
        }

        for (Thread t: threads) {
            t.join();
        }
        System.out.println(answer);
        correctAnswer = (maxValue * (maxValue - 1) / 2);
        System.out.println(correctAnswer);
    }


    public static void main(String[] args) throws InterruptedException {

        sayHello();
        badSum();


    }

// read, add, save
    //reads are blocking the writes which is why the answers are always lower than the correct answer.

}
