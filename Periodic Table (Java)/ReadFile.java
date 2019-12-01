import java.util.*;
import java.io.*;
public class ReadFile
{
    //this method takes a list of strings and fills it with the lines of a file
    public static String[] readFile()
    {
        String[] lines = new String[500];
        String userInput = "";
        Scanner sc = new Scanner(System.in);
        System.out.println("=======================================================================================================================================" + "\r\n" +
                            "Please Enter the name of the File");
        userInput = sc.nextLine();
        //try to read from a file
        try
        {
            //create a buffered reader to read the lines and open the file with an InputStream
            FileInputStream inputFile = new FileInputStream(userInput + ".csv");
            InputStreamReader reader = new InputStreamReader(inputFile);
            BufferedReader fileBuffer = new BufferedReader(reader);

            //for each value in the array, try to read the file
            String line = fileBuffer.readLine();
            for (int i = 0; i < 500; i++)
            {
                line = fileBuffer.readLine();
                lines[i] = line;
            }
        }
        //if anything goes wrong catch the exception
        catch(IOException ex)
        {
            System.out.println("ERROR! Could not read file: " + ex.getMessage());
        }
        return lines;
    }


}