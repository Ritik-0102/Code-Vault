public class Variable_Arguments {
    public static int add(int...num){
        int sum=0;
        for(int i=0;i<num.length;i++){
            sum+=num[i];
        }
        return sum;
    }
    public static void main(String[] args){
        System.out.println(add(2));
        System.out.println(add(2,3));
        System.out.println(add(2,3,4));
    }
}
