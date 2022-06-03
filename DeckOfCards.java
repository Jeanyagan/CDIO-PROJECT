import java.util.ArrayList;
import java.util.List;

public class DeckOfCards {
    private ArrayList<Cards> deck;


    /**
     *
     * @param deck
     */
    public DeckOfCards(ArrayList<Cards> deck) {
        this.deck = deck;
    }


    /**
     * Build a full deck of cards
     */

    public DeckOfCards()
    {
        List<String> suits = Cards.getValidSuits();
        List<String> faceNames = Cards.getValidFaceNames();

        deck = new ArrayList<>();
        for (String suit:suits)
        {
            for (String faceName:faceNames)
                deck.add(new Cards(faceName, suit));
        }
    }

}
