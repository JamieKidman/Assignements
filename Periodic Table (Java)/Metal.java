public class Metal extends Element
{
    private double conductivity;

    public Metal() //default constructor
    {
        super();
        double conductivity = 0.00; //default value
    }

    //alternate constructor
    public Metal(String inSymbol, String inName, int inAtomic, double inMass,double inConductivity)
    {
        super(inSymbol, inName, inAtomic, inMass);
        conductivity = inConductivity;
    }

    //copy constructor
    public Metal(Metal inMetal)
    {
        super(inMetal);
        conductivity = inMetal.getConductivity();
    }

    //getters
    public double getConductivity()
    {
        return conductivity;
    }

    //setters
    public void setConductivity(double inConductivity)
    {
        conductivity = inConductivity;
    }

    //equals
    public boolean equals(Metal inMetal)
    {
        return super.equals(inMetal) &&
               conductivity == inMetal.getConductivity();
    }

    //toString
    public String toString()
    {
        return super.toString() + "," + conductivity +"/>";
    }
}