public class Access_Modifiers {
    int a=10;
    public int b=20;
    private int c=30;
    protected int d=40;

    public static void main(String[] args){
        Access_Modifiers object = new Access_Modifiers();
        System.out.println(object.a);
        System.out.println(object.b);
        System.out.println(object.c);
        System.out.println(object.d);
     }      
}
