public class Palindrome {
    public boolean isPalindrome(String s) {
        
        if (s == null) 
            return false;

        // Clean the string: remove non-alphanumeric characters and lowercase it
        // We reference 'this.text' explicitly
        String cleanStr = s.replaceAll("[^a-zA-Z0-9]", "").toLowerCase();

        // Reverse the string using StringBuilder
        StringBuilder sb = new StringBuilder(cleanStr);
        String reversedStr = sb.reverse().toString();

        // Compare content
        return cleanStr.equals(reversedStr);
    }
    public static void main(String[] args) {

        // Create an instance (object) of our class
        Palindrome word1 = new Palindrome();
        Palindrome word2 = new Palindrome();
        
        // Check if they are palindromes
        System.out.println("'Madam' is palindrome? " + word1.isPalindrome("Madam")); // true
        System.out.println("'Java' is palindrome? " + word2.isPalindrome("Java"));   // false
    }
}
