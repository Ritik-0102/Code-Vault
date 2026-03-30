import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class JDBC_03 {
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
            String query = "INSERT INTO students(name, age, marks) VALUES(?, ?, ?)";

            // Statement statement = connection.createStatement();
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, "Ankita");
            preparedStatement.setInt(2, 25);
            preparedStatement.setDouble(3, 84.7);
            int rowsAffected = preparedStatement.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Data Inserted Successfully!");
            } else {
                System.out.println("Data not Inserted!");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}
