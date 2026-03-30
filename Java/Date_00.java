import java.time.*;
import java.time.format.*;

public class Date_00 {
    public static void main(String[] args){

        // Formatting (Date -> String):
        LocalDateTime myDateObj = LocalDateTime.now();
        DateTimeFormatter myFormatObj = DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm:ss");
        
        String formattedDate = myDateObj.format(myFormatObj);
        System.out.println(formattedDate);

        // Parsing (String -> Date):
        String str = "2023-10-05";
        LocalDate date = LocalDate.parse(str); // Default ISO_LOCAL_DATE format
        System.out.println(date.getMonthValue());
    }
}
