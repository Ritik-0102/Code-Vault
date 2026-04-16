// Collection & FrameWork (LinkedList Implementation)

import java.util.Collections;
import java.util.LinkedList;

public class Linked_List_01 {
    public static void main(String[] args){
        LinkedList<Integer> list=new LinkedList<>();

        list.add(1);
        list.add(2);
        list.add(3);
        list.add(4);

        list.addFirst(0);
        list.addLast(5);

        System.out.println(list);

        list.removeFirst();
        list.removeLast();

        System.out.println(list);

        list.remove(2);

        System.out.println(list);
        System.out.println(list.get(1));
        System.out.println(list.size());

        // Reversing the list using Collections.reverse() method
        Collections.reverse(list);
        System.out.println(list);
    }
}
