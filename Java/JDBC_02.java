import java.sql.*;

public class JDBC_02 {
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
            Statement statement = connection.createStatement();
            String query = String.format("INSERT INTO students(name, age, marks) VALUES('%s', %d, %f)", "Rahul", 23,
                    74.5);

            int rowsAffected = statement.executeUpdate(query);
            if (rowsAffected > 0) {
                System.out.println("Data Inserted Successfully!");
            } else {
                System.out.println("Data Not Inserted!");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}