// Print keypad combination

/*
0 -> .
1 -> abc
2 -> def
3 -> ghi
4 -> jkl
5 -> mno
6 -> pqrs
7 -> tu
8 -> vwx
9 -> yz
 */

public class Keypad_Combinations {
    public static String[] Keypad = { "." , "abc" , "def" , "ghi" , "jkl" , "mno" , "pqrs" , "tu" , "vwx" , "yz"};

    public static void Print_Combinations(String str,int idx ,String combination){
        if(idx == str.length()){
            System.out.println(combination);
            return;
        }

        char current_num = str.charAt(idx);
        String keypad_chars = Keypad[current_num - '0'];

        for(int i=0;i<keypad_chars.length();i++){
            Print_Combinations(str,idx+1,combination + keypad_chars.charAt(i));
        }
    }

    public static void main(String[] args){
        String n = "23";

        Print_Combinations(n,0,"");
    }
}
