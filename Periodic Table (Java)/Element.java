import java.util.*;
public abstract class Element
{
    /*
        Here is where the objects are created with the % of the element feilds being handled by inheritance
    */
    private String symbol;
    private String name;
    private int atomic;
    private double mass;

    public Element() //default
    {
        name = " ";
        symbol = " ";
        atomic = 1;
        mass = 0.01;
    }
    
        public Element(String inSymbol, String inName, int inAtomic, double inMass) //alternate
        {   
            symbol = inSymbol;
            name = inName;
            atomic = inAtomic;
            mass = inMass;
        }

        public Element(Element inElement) //Copy 
        {
            symbol = inElement.getSymbol();
            name = inElement.getName();
            atomic = inElement.getAtomic();
            mass = inElement.getMass();          
        }

//Getters
//-------------------------------------------------------------------------------------------------------
        public String getSymbol()
        {
            return symbol;
        }
    
        public String getName()
        {
            return name;
        }

        public int getAtomic()
        {
            return atomic;
        }
    
        public double getMass()
        {
            return mass;
        }
//Setters
//-------------------------------------------------------------------------------------------------------
        public void setSymbol(String inSymbol)
        {
            symbol = inSymbol;
        }
    
        public void setName(String inName)
        {
            name = inName;
        }

        public void setAtomic(int inAtomic)
        {
            atomic = inAtomic;
        }

        public void setMass(double inMass)
        {
            mass = inMass;
        }
// Equals
//------------------------------------------------------------------------------------------------------
        public boolean equals( Element inElement)
        {
            boolean isEqual = false;
            if( inElement instanceof Element )
            {
                inElement = (Element)inElement;
                if (symbol.equals(inElement.getSymbol()))
                    if (name.equals(inElement.getName()))
                        if ( atomic == inElement.getAtomic())
                            if(mass == inElement.getMass())
                                isEqual = true;
            }
            return isEqual;
        }           


// toString
//------------------------------------------------------------------------------------------------------
        public String toString()
        {
            return "<" + symbol + "," + name + "," + atomic +  "," + mass;
        }
}