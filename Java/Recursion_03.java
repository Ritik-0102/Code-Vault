// Find the number of ways in which you can invite n people to your party, single or in pairs

// n = 4
// output = 10

public class Recursion_03 {
    public static int Invite_People(int n){
        if(n<=1){
            return 1;
        }

        int single = Invite_People(n-1);
        int pairs = (n-1)*Invite_People(n-2);

        return single + pairs;
    }

    public static void main(String[] args) {
        System.out.println(Invite_People(4));
    }
}
