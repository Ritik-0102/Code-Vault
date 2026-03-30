// ALWAYS REMEMBER : Java Strings are Immutable.

public class Strings_00 {
    public static void main(String[] args){
        // Strings Are Immutable
        
        String s1="Ritik Rana";

        // substring function

        System.out.println(s1.substring(6,s1.length()));
        
        // CharAt is used access character from string with its index
        for(int i=0;i<s1.length();i++){
            System.out.println(s1.charAt(i));
        }
        
        String s2="abc";
        String s3="ABC";

        // CompareTo is used to compare strings

        // if s1 > s2 => +ve Value
        // if s1 = s2 => 0
        // if s1 < s2 => -ve Value

        if(s2.compareTo(s3)==0){
            System.out.println("The strings are equal");
        }
        else{
            System.out.println("The strings are Not equal");
        }


    //  Substring
    //  The substring of a string is a subpart of it.
        String name = "TonyStark";
        
        System.out.println(name.substring(0, 4));


    // ParseInt Method of Integer class
        String str = "123";
        int number = Integer.parseInt(str);
        System.out.println(number);


    // ToString Method of String class
        number = 123;
        str = Integer.toString(number);
        System.out.println(str.length());


        String s="WorldofElephants";
        
        String newStr=s.replace('o', 'x');
        System.out.println(newStr);
    }
}
