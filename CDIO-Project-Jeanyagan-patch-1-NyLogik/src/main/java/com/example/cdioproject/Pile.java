package com.example.cdioproject;

import java.awt.Component;
import java.awt.Dimension;
import java.util.ArrayList;
import javax.swing.JLayeredPane;
import com.example.cdioproject.Card.CardSuit;

public class Pile extends JLayeredPane {

    Card base;
    ArrayList<Card> cards;
    int offset = 15;
    CardSuit cardSuit;
    int width;
    Pile pileParent;
    PileType pileType;

    enum PileType {
        Normal, Draw, Get, Final
    };

    public Pile(int width) {
        cards = new ArrayList<Card>();
        this.width = width;

        base = new Card(100, CardSuit.Spades);
        add(base, 1, 0);

        pileType = PileType.Normal;
    }

    public void addCard(Card card) {
        card.setLocation(0, offset * cards.size());
        cards.add(card);

        this.add(card, 1, 0);
        updateSize();
    }

    public void removeCard(Card card) {
        cards.remove(card);
        this.remove(card);
        updateSize();
    }

    public Card peekTopCard() {
        return cards.get(cards.size() - 1);
    }

    public Card drawCard() {
        Card c = cards.get(0);
        removeCard(c);
        return c;
    }

    public void setWidth(int width) {
        this.width = width;
        updateSize();
    }

    public void updateSize() {
        int height = base.getSize().height;

        if (!cards.isEmpty()) {
            height += offset * (cards.size() - 1);
        }

        this.setPreferredSize(new Dimension(width, height));
        this.setSize(width, height);
    }

    public void setOffset(int offset) {
        this.offset = offset;
        updateSize();
    }

    public Pile split(Card first) {
        Pile pile = new Pile(100);

        for (int i = 0; i < cards.size(); ++i) {
            if (cards.get(i) == first) {
                for (; i < cards.size();) {
                    pile.addCard(cards.get(i));
                    removeCard(cards.get(i));
                }
            }
        }
        pile.pileParent = this;
        return pile;
    }

    public void merge(Pile pile) {
        for (Card c : pile.cards) {
            addCard(c);
        }
        updateSize();
    }

    public Card searchCard(int cardValue, String suitName) {

        for (Card card : cards) {
            if (card.cardValue == cardValue && card.cardSuit.name().equals(suitName)) {
                return card;
            }
        }

        return null;
    }

    public boolean isEmpty() {
        return cards.size() == 0;
    }

    public boolean acceptsPile(Pile pile) {
        if (this == pile) {
            return false;
        }
        Card newCard = pile.cards.get(0);
        Card topCard;

        switch (pileType) {
            case Normal:
                if (cards.isEmpty()) {
                    if (newCard.cardValue == 14) {
                        return true;
                    }
                    return false;
                }

                topCard = cards.get(cards.size() - 1);
                if (topCard.isReversed) {
                    return false;
                }

                if (topCard.cardSuit.isRed != newCard.cardSuit.isRed) {
                    if (topCard.cardValue == newCard.cardValue + 1
                            || topCard.cardValue == 12 && newCard.cardValue == 10) {
                        return true;
                    }
                }
                break;

            case Final:

                if (pile.cards.size() > 1) {
                    return false;
                }

                if (cards.isEmpty() && newCard.cardValue == 1) {
                    cardSuit = newCard.cardSuit;
                    return true;
                }

                if (cardSuit != newCard.cardSuit) {
                    return false;
                }

                topCard = cards.get(cards.size() - 1);
                if (topCard.cardValue == newCard.cardValue - 1
                        || topCard.cardValue == 10 && newCard.cardValue == 12) {
                    return true;
                }
                break;
        }
        return false;
    }

    public boolean isOptimizedDrawingEnabled() {
        return false;
    }

    @Override
    public String toString() {
        String result = "";
        result += base.saveAsString() + "-";
        for (Card card : cards) {
            result += card.saveAsString() + "-";
        }

        return result;
    }

    @Override
    public Component.BaselineResizeBehavior getBaselineResizeBehavior() {
        return Component.BaselineResizeBehavior.CONSTANT_ASCENT;
    }

    @Override
    public int getBaseline(int width, int height) {
        return 0;
    }
}
