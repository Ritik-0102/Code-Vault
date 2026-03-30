import java.util.HashSet;

public class Subsequences_of_string_01 {
    public static HashSet<String> set=new HashSet<>();

    public static void Unique_Subsequences_of_string(int idx,String s,String Substring){

        if(idx==s.length()){
            if(set.contains(Substring)){
                return;
            }
            else{
                System.out.println(Substring);
                set.add(Substring);
                return;
            }
        }

        char current_char=s.charAt(idx);

        // Every character has choice To get included in Substring Or Not
        
        // When Included in Substring
        Unique_Subsequences_of_string(idx+1,s,Substring + current_char);

        // When NOT Included in Substring
        Unique_Subsequences_of_string(idx+1,s,Substring);

    }
}
