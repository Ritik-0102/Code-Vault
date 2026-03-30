// Print All the Subsequences of a String

public class Subsequences_of_string_00 {
    public static void Subsequences(int idx,String s,String Substring){
        if(idx==s.length()){
            System.out.println(Substring);
            return;
        }

        char current_char = s.charAt(idx);

        // Every character has choice To get included in Substring Or Not
        
        // When Included in Substring
        Subsequences(idx+1,s,Substring + current_char);

        // When NOT Included in Substring
        Subsequences(idx+1,s,Substring);
    }

    public static void main(String[] args){

        String s="abcd";

        Subsequences(0,s,"");

    }
}
