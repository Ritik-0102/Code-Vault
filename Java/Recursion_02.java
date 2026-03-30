// Find Total No. of Ways To Place Tile of (1 x m) in the Floor of (n x m)

public class Recursion_02 {
    public static int Place_Tiles(int n,int m){
        if(n==m){
            return 2;
        }
        if(n<m){
            return 1;
        }

        int Vertical_Placement=Place_Tiles(n-m, m);
        int Horizontal_Placement=Place_Tiles(n-1, m);

        return Vertical_Placement + Horizontal_Placement;
    }
    public static void main(String[] args){
        int n=4;
        int m=2;

        System.out.println(Place_Tiles(n, m));
    }
}
