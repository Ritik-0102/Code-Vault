
// Print all Permutations of a String

public class Recursion_00 {
    public static void Permutations_of_string(String str,String Permutation){
        if(str.length()==0){
            System.out.println(Permutation);
            return;
        }

        for(int i=0;i<str.length();i++){
            String New_String = str.substring(0,i) + str.substring(i+1);
            
            Permutations_of_string(New_String,Permutation+str.charAt(i));
        }
    }
    public static void main(String[] args){
        String s="abc";

        Permutations_of_string(s,"");
    }
}
