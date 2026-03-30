class MyRunnable implements Runnable {
    @Override
    public void run() {
        System.out.println("Runnable thread is running.");
    }
}


public class Thread_01 {
    public static void main(String[] args){
        MyRunnable myRun = new MyRunnable();
        Thread t2 = new Thread(myRun);
        t2.start();
    }
}
