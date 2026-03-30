// Count the Total no. of Paths in a maze to Move from (0,0) To (m,n)

public class Recursion_01 {
    public static int No_of_paths(int i,int j,int m,int n){
        if(i==m-1 && j==n-1){
            return 1;
        }

        if(i==m || j==n){
            return 0;
        }

        int Path_in_Rightward_Direction = No_of_paths(i , j+1 , m , n );
        int Path_in_Downward_Direction = No_of_paths(i+1 , j , m , n );

        return Path_in_Downward_Direction + Path_in_Rightward_Direction;
    }

    public static void main(String[] args){
        System.out.println(No_of_paths(0,0,3,3));
    }
}
