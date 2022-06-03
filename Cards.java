import java.util.Arrays;
import java.util.List;


public class Cards {
    private String faceName, suit;
    // privte Image.image; --> Billede ved GUI

    public Cards(String faceName, String suit) {
        setFaceName(faceName);
        setSuit(suit);
    }

    public String getFaceName() {
        return faceName;
    }



    /**
     * Denne metode retunrere en liste af navne som er valide
     * for kortene
     */
    public static List<String> getValidFaceNames()
    {
        return Arrays.asList("2","3","4,","5","6","7","8","9","10",
        "jack, queen", "king","ace");
    }

    /**
    * Metoden validere argumentet og sætter instance varaible
    * @param faceName 2,3,4,5,6,7,8,9,10, jack, queen, king,
    */
    public void setFaceName(String faceName) {
        List<String>validFaceNames = getValidFaceNames();
        faceName = faceName.toLowerCase();

        if (validFaceNames.contains(faceName))
            this.faceName = faceName;
        else
            throw new IllegalArgumentException("Not a valid suit");
    }

    public String getSuit() {
        return suit;
    }

    /**
     * This method will return a list of valid suits
     * @return spades, hearts, clubs, diamonds
     */
    public static List<String> getValidSuits()
    {
        return Arrays.asList("hearts","diamonds","spades","clubs");
    }

    public void setSuit(String suit) {
        List<String> validSuits = getValidSuits();
        suit = suit.toLowerCase();

        if (validSuits.contains(suit))
            this.suit = suit;
        else
            throw new IllegalArgumentException("Not a valid suit");
    }

    public String toString()
    {
        return String.format("%s of %s", faceName, suit);
    }
}
