
/**
 * Write a description of class TestPerson here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class TestElement
{
    public static void main(String [] args)
    {
        Element p = new Metal("Sa","Saline", 20, 10.0, 10.0);
        System.out.println("Testing...");
        System.out.println(p.toString());

        Element pa = new NonMetal("Sa","Saline", 20, 10.0, 'i');
        System.out.println(pa.toString());
    }
}
