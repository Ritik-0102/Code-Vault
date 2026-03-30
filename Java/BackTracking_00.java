public class BackTracking_00 {
    public static void print_permutations(String str,String perm){
        if(str.length()==0){
            System.out.println(perm);
            return;
        }

        for(int i=0;i<str.length();i++){
            char curr_char=str.charAt(i);
            String newStr=str.substring(0,i)+str.substring(i+1);
            print_permutations(newStr, perm+curr_char);
        }
    }

    public static void main(String[] args){
        print_permutations("ABC","");
    }
}
