import java.sql.*;
import java.util.Scanner;

public class JDBC_04 {
    static final String url = "jdbc:mysql://localhost:3306/mydb";
    static final String username = "root";
    private static final String password = "Admin@123";

    public static void main(String[] args) {
        // Load the driver
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println("Driver not found: " + e.getMessage());
        }

        // Establish connection and execute batch
        try {
            Connection connection = DriverManager.getConnection(url, username, password);
            Statement statement = connection.createStatement();
            Scanner scanner = new Scanner(System.in);

            while(true) {
                System.out.print("Enter name: ");
                String name = scanner.next();
                
                System.out.print("Enter age: ");
                int age = scanner.nextInt();
                
                System.out.print("Enter marks: ");
                double marks = scanner.nextDouble();
                
                // 1. Completed the truncated String.format line
                String query = String.format("INSERT INTO students(name, age, marks) VALUES('%s', %d, %f)", name, age, marks);
                statement.addBatch(query);
                
                System.out.print("Enter more data(Y/N): ");
                String choice = scanner.next();
                
                if(choice.toUpperCase().equals("N")) {
                    break;
                }
            }

            // Execute the batch of queries
            int[] arr = statement.executeBatch();
            
            // 2. Fixed the logic to check if data was actually inserted
            if(arr.length > 0) {
                System.out.println("Data Updated Successfully! Added " + arr.length + " record(s).");
            } else {
                System.out.println("Data not Updated!");
            }

            // Close resources
            scanner.close();
            statement.close();
            connection.close();

        } catch (SQLException e) { // 3. Added the required catch block
            System.out.println("Database error: " + e.getMessage());
        }
    }
}