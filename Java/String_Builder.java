
public class String_Builder {
    public static void main(String[] args){
    StringBuilder sb = new StringBuilder("Helo World");

    System.out.println(sb);

    // Char at index 0
    System.out.println(sb.charAt(0));

    // Updation
    // set char at index 0
    sb.setCharAt(0, 'A');
    System.out.println(sb);

    // Insertion
    // Insert character at any index
    sb.insert(2, 'l');
    System.out.println(sb);

    // Deletion
    sb.delete(5, 6);
    System.out.println(sb);

    // Append
    sb.append('s');
    System.out.println(sb);

    sb.reverse();
    System.out.println(sb);
    }
}
