public class Input_02 {
    public static void main(String[] args){
        // If we will give command line arguments like
        // java Input_02 Hello world 
        // This will print args length as 2
        System.out.println(args.length);

        for(int i=0;i<args.length;i++){
            System.out.println(args[i]);
        }
    }
}
