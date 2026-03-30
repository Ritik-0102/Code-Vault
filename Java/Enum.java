enum Traffic_Light {  
    RED,GREEN,YELLOW;
}

public class Enum {
    public static void main(String[] args){
        Traffic_Light object = Traffic_Light.RED;

        int x=Traffic_Light.YELLOW.ordinal();

        System.out.println(object);
        System.out.println(x);
    }
    
}