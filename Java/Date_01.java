import java.time.*;

public class Date_01 {
    public static void main(String[] args){

        // Period: A quantity of time in terms of years, months, and days (Date-based).
        LocalDate bday = LocalDate.of(1995, 5, 20);
        LocalDate today = LocalDate.now();
        
        Period p = Period.between(bday, today);
        System.out.println("Age: " + p.getYears() + " years");

        
        // Duration: A quantity of time in terms of seconds and nanoseconds (Time-based).
        LocalTime start = LocalTime.of(10, 0);
        LocalTime end = LocalTime.of(11, 30);

        Duration d = Duration.between(start, end);
        System.out.println(d.toMinutes()); // Prints 90
    }
}
