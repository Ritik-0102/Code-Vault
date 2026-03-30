import java.sql.*;
import java.util.Scanner;

public class JDBC_05 {
    static final String url = "jdbc:mysql://localhost:3306/mydb";
    static final String username = "root";
    private static final String password = "Admin@123";

    public static void main(String[] args) {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println(e.getMessage());
        }
        try {
            Connection connection = DriverManager.getConnection(url, username, password);
            String debit_query = "UPDATE accounts SET balance = balance - ? WHERE account_number = ?";
            String credit_query = "UPDATE accounts SET balance = balance + ? WHERE account_number = ?";
            PreparedStatement debitPreparedStatement = connection.prepareStatement(debit_query);
            PreparedStatement creditPreparedStatement = connection.prepareStatement(credit_query);
            Scanner scanner = new Scanner(System.in);
            double amount = scanner.nextDouble();
            debitPreparedStatement.setDouble(1, amount);
            debitPreparedStatement.setInt(2, 101);
            creditPreparedStatement.setDouble(1, amount);
            creditPreparedStatement.setInt(2, 102);
            // if(isSufficient(connection, 101, amount)){
            // int affectedRows1 = debitPreparedStatement.executeUpdate();
            // int affectedRows2 = creditPreparedStatement.executeUpdate();
            // }else{
            // System.out.println("Insufficient Balance!!");
            // }
            debitPreparedStatement.executeUpdate();
            int affectedRows2 = creditPreparedStatement.executeUpdate();

        } catch (SQLException e) {
        }
    }
}