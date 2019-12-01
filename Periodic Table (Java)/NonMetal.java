public class NonMetal extends Element
{
    private char state;

    public NonMetal() //default constructor
    {
        super();
        state = 'G'; //default value
    }

    //alternate constructor
    public NonMetal(String inSymbol, String inName, int inAtomic, double inMass,char inState)
    {
        super(inSymbol, inName, inAtomic, inMass);
        state = inState;
    }

    //copy constructor
    public NonMetal(NonMetal inNonMetal)
    {
        super(inNonMetal);
        state = inNonMetal.getState();
    }

    //getters
    public char getState()
    {
        return state;
    }

    //setters
    public void setState(char inState)
    {
        state = inState;
    }

    //equals
    public boolean equals(NonMetal inNonMetal)
    {
        return super.equals(inNonMetal) &&
               state == inNonMetal.getState();
    }

    //toString
    public String toString()
    {
        return super.toString() + "," + state +"/>";
    }
}