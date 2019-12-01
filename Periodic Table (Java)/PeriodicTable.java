import java.util.*;
import java.io.*;
public class PeriodicTable
{
    /*
    Author: Jamie.
    Builds a PeriodicTable object.
    */
    private int count;
    private Element[][] elementArray;
    private boolean constructed;

    public PeriodicTable() //default
    {
        count = 0;
        elementArray = new Element[11][11];
        constructed = false;
    }
    
    public PeriodicTable(int inCount,Element[][] inElementArray, boolean isConstructed) //alternate
    {   
        count = inCount;
        elementArray = inElementArray;
        constructed = isConstructed;
    }

    public PeriodicTable(PeriodicTable inPeriodicTable) //Copy 
    {
        count = inPeriodicTable.getCount();
        elementArray = inPeriodicTable.getArray();
        constructed = inPeriodicTable.isConstructed();        
    }
//Getters
//-------------------------------------------------------------------------------------------------------
        public int getCount()
        {
            return count;
        }
    
        public Element[][] getArray()
        {
            return elementArray;
        }

        public boolean isConstructed()
        {
            return constructed;
        }
    
//Setters
//-------------------------------------------------------------------------------------------------------
        public void setCount(int inCount)
        {
            count = inCount;
        }
    
        public void setArray(Element[][] inElementArray)
        {
            elementArray = inElementArray;
        }

        public void isConstructed(boolean isConstructed)
        {
            constructed = isConstructed;
        }

// Equals
//------------------------------------------------------------------------------------------------------
        public boolean equals(PeriodicTable inPeriodicTable)
        {
            boolean isEqual = false;
            if( inPeriodicTable instanceof PeriodicTable )
            {
                inPeriodicTable = (PeriodicTable)inPeriodicTable;
                if (count == inPeriodicTable.getCount())
                    if (elementArray.equals(inPeriodicTable.getArray()))
                        if (constructed == inPeriodicTable.isConstructed())
                            isEqual = true;
            }
            return isEqual;
        }           


// toString
//------------------------------------------------------------------------------------------------------
        public String toString()
        {
            String returnString = new String();
            for(int i = 0; i < 11; i ++)
            {
                for(int j = 0; j < 11; j++)
                {
                    returnString += elementArray[i][j].getSymbol();
                }
                returnString += "\r\n";
            }

            return returnString;
        }
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
    public Element[][] addElement()
    {
        /*
            This submodule imports user inputs checks to see if they are vaild (data types and have the right values) stores them in the elementMultiArray
            Although the array is the main method of storing the elements info it is also creating an object incase the code needs to do that in the future.
            FUTURE Update sends inputs to objects stored in elementArray
        */
        String userInput;
        boolean isMetal = false;
        String symbol;
        String name;
        String atomicString;
        int atomicInt = 0;
        char stateChar = '0';
        String stateString = "";
        String conductivityString;
        double conductivityDouble = 0.00;
        String massString = "";
        double massDouble = 0.00;
        Scanner sc = new Scanner(System.in);
        

       
        System.out.println("=======================================================================================================================================" + "\r\n" +
                            "Is the Element a Metal, Yes or No");
        userInput = sc.nextLine();

        if ((userInput.equals("Yes") || userInput.equals("yes")))
        {
            isMetal = true;
        }

        else
        {
            isMetal = false;
        }

        System.out.println("=======================================================================================================================================" + "\r\n" +
                            "Please Enter a Symbol for the Element");
        symbol = sc.nextLine();
        
        if (symbol.length() > 2)
        {
            symbol = symbol.substring(0,2);
        }

        System.out.println("=======================================================================================================================================" + "\r\n" +
                            "Please Enter the Name for the Element");
        name = sc.nextLine();

        do
        {
            System.out.println("=======================================================================================================================================" + "\r\n" +
                            "Please Enter the Atomic Number for the Element");
            atomicString = sc.nextLine();
            try
            {
                atomicInt = Integer.parseInt(atomicString);
            }
        
            catch (Exception e)
            {
                System.out.println("Please Try Again");
            }

        }while (!((atomicInt > 0) && (atomicInt < 101)));
        
        if (isMetal == true)
        {
            do
            {
                System.out.println("=======================================================================================================================================" + "\r\n" +
                            "Please Enter the Conductivity of the Element");
                conductivityString = sc.nextLine();
                try
                {
                    // Putting String versions of all values into the array
                    conductivityDouble = Double.parseDouble(conductivityString);
                }
        
                catch (Exception e)
                {
                    System.out.println("Please Try Again");
                }

            }while (!(conductivityDouble > 0.00));
        }

        else
        {
            do
            {
                System.out.println("========================================================================================================================================" + "\r\n" +
                            "Please Enter the State of the Element");
                stateString = sc.nextLine();
                stateChar = stateString.charAt(0);

            }while(!((stateChar == 'L') || (stateChar == 'S') || (stateChar == 'G')));
        }

        do
        {
            System.out.println("=======================================================================================================================================" + "\r\n" +
                            "Please Enter the Mass of the Element");
            massString = sc.nextLine();
            try
            {
                massDouble = Double.parseDouble(massString);
            }
        
                catch (Exception e)
                {

                }

            }while (!(massDouble > 0.00));

        if (isMetal == true)
        {
             Element element = new Metal(symbol, name, atomicInt, massDouble, conductivityDouble);
             elementArray[getCount()/10%0][getCount()] = element;
             
        }

        else
        {
            Element element = new NonMetal(symbol, name, atomicInt, massDouble, stateChar);
             elementArray[getCount()/10%0][getCount()] = element;
            
        count++;
        }
        return elementArray;
    }
        
    public Element[][] readFileToArray(String[] lines)
    {
        //Reads from Lines, turns it to objects and stores that into elementArray
        // Still needs logic refinements to read the whole array cant work out whats happening done multiple tests
        //Seems like the for loop for i is only running once
        try
        {
            //for each line of the file
            for(int i = 0; i < lines.length && lines != null; i++)
            {
                //regex magic to split out the <..../> parts
                String[] elementStrings = lines[i].split("<|\\/><|\\/>");
            
                //for each element in the line (ignoring the first because that's a blank "<"
                for(int j = 1; j < 11; j++)
                {
                   
                    //split out each token by comma
                    String[] elementString = elementStrings[j].split(",");
                    //create a new element and add it to my Element list
    
                        try
                        {
                            elementArray[i][j] = new Metal(elementString[0], elementString[1], Integer.parseInt(elementString[2]), Double.parseDouble(elementString[3]), Double.parseDouble(elementString[4]));  

                        }

                        catch (Exception e)
                        {
                            elementArray[i][j] = new NonMetal(elementString[0], elementString[1], Integer.parseInt(elementString[2]), Double.parseDouble(elementString[3]), elementString[4].charAt(0));
                        }
                        count++;
                        setCount(count);
                }
            }
        }
        catch(Exception e)
        {

        }
                setArray(elementArray);
                return elementArray;
    }


    
    public String displayElements()
    {
        String input = "";
        for(int i = 0; i < 11 ; i++)
        {

            for(int j = 0; j < 11; j++)
            {

                if(j == 10)
                {
                    input = "\r\n";
                }
                try
                {
                    System.out.print("|" + elementArray[i][j].getSymbol() + input);
                    input = "";
                }
                catch(Exception e)
                {
                    
                }
            }
                    
        }
        return "    |End Transmition";
    }

    public void fileOutput()
    { 
        try
        {
            FileOutputStream fileStrm = null;
            PrintWriter pw;

            fileStrm = new FileOutputStream("PeriodicTable.csv"); 
            pw = new PrintWriter(fileStrm);
            for(int i=0; i < 10; i++)
            {
                for(int j=0; j <10; j++)
                    {
                    pw.println("<" + elementArray[i][j].getSymbol() + "," + elementArray[i][j].getName() + "," + elementArray[i][j].getAtomic() + "," + elementArray[i][j].getMass() + "/>");
                    }
                i++;
            }
        }
        catch(Exception e)
        {
            
        }
    }
           
    
}
