import java.util.*;

public class MainMenu
{
    public static void main(String[] args)
    {
    /*
    Author: Jamie.
    Main is a menu that calls all the modules ( I guess this is a ... Main menu...)
    */
        
        Scanner sc = new Scanner(System.in);
        String userChoice = "0";
        //String[][] elementMultiArray = new String[100][5];
        PeriodicTable periodicTable = new PeriodicTable();
        

        do
        {
            System.out.println("=======================================================================================================================================");
            System.out.println("To Add an Element Type, \"Add\" or \"1\";");
            System.out.println("To Display an Element Type, \"Display\" or \"2\";");
            System.out.println("To Read a file Type, \"Read\" or \"3\";");
            System.out.println("To Write a file Type, \"Write\" or \"4\";");
            System.out.println("And To Exit the Program Type, \"Exit\".");
            
            userChoice = sc.nextLine();

            if(userChoice.equals("1") || userChoice.equals("Add"))
            {
                if (periodicTable.isConstructed() == true)
                {
                    System.out.println("You just added "+ periodicTable.addElement().toString());

                    
                }
              
                
                else if(periodicTable.isConstructed() == false)
                {
                    System.out.println("Please Import the Periodic Table First.");
                }
            }

            else if(userChoice.equals("2") || userChoice.equals("Display"))
            {
                System.out.println(periodicTable.displayElements());
            }

           else if(userChoice.equals("3") || userChoice.equals("Read"))
            {   
                if(periodicTable.isConstructed() != true)
                {
                    periodicTable.setArray(periodicTable.readFileToArray(ReadFile.readFile()));
                
                    if(periodicTable.getArray() != null)
                        periodicTable.isConstructed(true);

                    System.out.println("Import Complete "+ periodicTable.getCount());
                }
                else
                {
                    System.out.println("Table Already Imported");
                }
                
            }

            else if(userChoice.equals("4") || userChoice.equals("Write"))
            {
                periodicTable.fileOutput();
                System.out.println("Write Complete");
            }

        } while (!(userChoice.equals("5")|| (userChoice.equals("Exit"))));

        System.out.println("Goodbye!");
    }
   
    }
