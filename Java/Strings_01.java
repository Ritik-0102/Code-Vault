// Print The No of Words in a Sentence

public class Strings_01 {
    public static int No_of_Words(String s){
        int c=0;
        for(int i=0;i<s.length();i++){
            if(s.charAt(i)==' '){
                c++;
            }
        }
        return c+1;
    }

    public static void Split_Words(String s){
        String[] words=s.trim().split(" ");

        for(String w:words){
            System.out.println(w);
        }
    }

    public static void main(String[] args){

        String s="aaaaa nwdcwom cjkrjew";

        int res=No_of_Words(s);
        System.out.println(res);
        
        Split_Words(s);
    }
}
