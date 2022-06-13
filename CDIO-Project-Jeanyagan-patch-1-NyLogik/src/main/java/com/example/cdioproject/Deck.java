package com.example.cdioproject;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

import com.example.cdioproject.Card.CardSuit;

public class Deck {

    ArrayList<Card> cards;

    public Deck() {
        cards = new ArrayList<Card>();
        for (CardSuit suit : CardSuit.values()) {
            for (int cardValue = 1; cardValue <= 14; ++cardValue) {
                if (cardValue != 11) {
                    cards.add(new Card(cardValue, suit));
                }
            }
        }
    }

    public void shuffle() {

        int size = cards.size();
        for (int shuffles = 1; shuffles <= 20; ++shuffles) {
            for (int i = 0; i < size; i++) {
                Collections.swap(cards, i, new Random().nextInt(size));
            }
        }

    }

    public int cardSize() {
        return cards.size();
    }

    public Card drawCard() {
        Card c = cards.get(0);
        cards.remove(0);
        return c;
    }

}
