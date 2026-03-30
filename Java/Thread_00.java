class MyThread extends Thread{
    public void run(){
        System.out.println("Thread is Running");
    }
}

public class Thread_00 {
    public static void main(String[] args){
        MyThread t1 = new MyThread();
        t1.start();
    }
}
