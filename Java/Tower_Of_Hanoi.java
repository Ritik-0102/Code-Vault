public class Tower_Of_Hanoi {
    public static void Tower_of_Hanoi(int n,String src,String helper,String dest){
        if(n==0){
            System.out.println("Transfer Disk : " + n + " From " + src + " -> " + dest);
            return;
        }
        Tower_of_Hanoi(n-1,src,dest,helper);
        System.out.println("Transfer Disk : " + n + " From " + src + " -> " + dest);
        Tower_of_Hanoi(n-1,helper,src,dest);
    }
    public static void main(String[] args){
        int n=3;

        Tower_of_Hanoi(n,"A","B","C");
    }
}
