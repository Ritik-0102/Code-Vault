import java.sql.*;

public class JDBC_00 {
    // Database credentials and URL (Example uses MySQL)
    static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    static final String USER = "root";
    static final String PASS = "password123";

    public static void main(String[] args) {
        
        // Using Try-with-Resources to auto-close the connection
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            System.out.println("Connected to the database successfully!");

            // 1. CREATE (Insert)
            String insertSQL = "INSERT INTO employees (name, role) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(insertSQL)) {
                pstmt.setString(1, "Alice");
                pstmt.setString(2, "Developer");
                int rowsInserted = pstmt.executeUpdate();
                System.out.println(rowsInserted + " row(s) inserted.");
            }

            // 2. READ (Select)
            String selectSQL = "SELECT id, name, role FROM employees";
            try (Statement stmt = conn.createStatement();
                 ResultSet rs = stmt.executeQuery(selectSQL)) {
                System.out.println("--- Employee List ---");
                while (rs.next()) {
                    System.out.println("ID: " + rs.getInt("id") + 
                                       ", Name: " + rs.getString("name") + 
                                       ", Role: " + rs.getString("role"));
                }
            }

            // 3. UPDATE
            String updateSQL = "UPDATE employees SET role = ? WHERE name = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(updateSQL)) {
                pstmt.setString(1, "Senior Developer");
                pstmt.setString(2, "Alice");
                int rowsUpdated = pstmt.executeUpdate();
                System.out.println(rowsUpdated + " row(s) updated.");
            }

            // 4. DELETE
            String deleteSQL = "DELETE FROM employees WHERE name = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(deleteSQL)) {
                pstmt.setString(1, "Alice");
                int rowsDeleted = pstmt.executeUpdate();
                System.out.println(rowsDeleted + " row(s) deleted.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}