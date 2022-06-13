package com.example.cdioproject;

import java.io.File;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.example.cdioproject.Card.CardSuit;
import com.example.cdioproject.Pile.PileType;

public class GameEngine {

    ArrayList<Pile> piles;
    ArrayList<Pile> finalPiles;
    Pile drawPile, getPile;
    ArrayList<Pile> allPiles;
    public final int pileNumber = 7;
    public Deck deck;

    public GameEngine() {
        resetCards();
    }

    public void resetCards() {
        deck = new Deck();
        deck.shuffle();

        drawPile = new Pile(120);
        drawPile.setOffset(0);

        getPile = new Pile(180);
        getPile.setOffset(0);

        finalPiles = new ArrayList<Pile>();
        piles = new ArrayList<Pile>();

        allPiles = new ArrayList<Pile>();
        allPiles.add(drawPile);
        allPiles.add(getPile);
    }

    public void setupGame() {
        drawPile.pileType = PileType.Draw;
        getPile.pileType = PileType.Get;

        for (int i = 1; i <= pileNumber; ++i) {
            Pile pile = new Pile(120);
            for (int j = 1; j <= i; ++j) {
                Card card = deck.drawCard();
                pile.addCard(card);

                if (j != i) {
                    card.hide();
                } else {
                    card.show();
                }
            }

            piles.add(pile);
            allPiles.add(pile);
        }

        for (CardSuit cardSuit : CardSuit.values()) {
            Pile pile = new Pile(100);
            pile.setOffset(0);
            pile.pileType = PileType.Final;
            finalPiles.add(pile);
            allPiles.add(pile);
        }

        while (deck.cardSize() > 0) {
            Card card = deck.drawCard();
            card.hide();
            drawPile.addCard(card);
        }
    }

    public void drawCards() {
        if (!drawPile.cards.isEmpty()) {
            Card drewCard = drawPile.drawCard();
            drewCard.isReversed = false;
            getPile.addCard(drewCard);
        }
    }

    public void clickPile(Pile pile) {
        if (!pile.cards.isEmpty()) {
            Card card = pile.cards.get(pile.cards.size() - 1);
            if (card.isReversed) {
                card.isReversed = false;
            }
        }
    }

    public void turnGetPile() {
        if (!drawPile.cards.isEmpty()) {
            return;
        }

        while (!getPile.cards.isEmpty()) {
            Card card = getPile.drawCard();
            card.isReversed = true;

            drawPile.addCard(card);
        }
    }

    public boolean checkIfWin() {
       boolean flag=true;
        for (Pile pile : finalPiles) {
            if (pile.cards.size() != 13) {
                return false;
            }
        }
        return true;
    }

    public void saveGame() {

        String saveString = "";

        try {
            DocumentBuilder docBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
            Document doc = docBuilder.newDocument();
            String newLine = System.getProperty("line.separator");
            Element game = doc.createElement("game");
            doc.appendChild(game);

            // This is from previous implementation, save each pile in a new line
            for (Pile pile : piles) {
                saveString += pile.toString() + newLine;
            }
            for (Pile pile : finalPiles) {
                saveString += pile.toString() + newLine;
            }
            saveString += drawPile.toString() + newLine;
            saveString += getPile.toString() + newLine;

            String[] lines = saveString.split(newLine);

            for (String pile : lines) {
                Element element = doc.createElement("pile");

                String cardStrings[] = pile.split("-");
                for (String crd : cardStrings) {
                    String parts[] = crd.split(" of ");

                    Element cardE = doc.createElement("card");
                    cardE.setAttribute("value", parts[0]);
                    cardE.setAttribute("suit", parts[1]);
                    cardE.setAttribute("isReversed", parts[2]);

                    element.appendChild(cardE);
                }

                game.appendChild(element);
            }

            Transformer transformer = TransformerFactory.newInstance().newTransformer();
            DOMSource src = new DOMSource(doc);
            StreamResult res = new StreamResult(new File("save.xml"));

            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
            transformer.transform(src, res);
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public void loadGame() {
        try {
            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            DocumentBuilder db = dbf.newDocumentBuilder();
            Document dom = db.parse("save.xml");
            Element docEle = dom.getDocumentElement();
            NodeList nl = docEle.getChildNodes();
            int currentPileCount = 0;
            if (nl != null) {
                for (int i = 0; i < nl.getLength(); i++) {
                    if (nl.item(i).getNodeType() != Node.ELEMENT_NODE) {
                        continue;
                    }
                    Element el = (Element) nl.item(i);
                    if (el.getNodeName().contains("pile")) {

                        NodeList cardList = el.getChildNodes();
                        Pile tempPile = new Pile(100);

                        if (cardList != null) {
                            for (int j = 0; j < cardList.getLength(); j++) {
                                if (cardList.item(j).getNodeType() != Node.ELEMENT_NODE) {
                                    continue;
                                }

                                Element cardNode = (Element) cardList.item(j);

                                String suitName = cardNode.getAttribute("suit");
                                boolean isReversed = cardNode.getAttribute("isReversed").equals("true");
                                int value = Card.valueInInt(cardNode.getAttribute("value"));

                                if (value == 100) {
                                    continue;
                                }

                                Card card = null;
                                Pile foundPile = null;

                                for (Pile pile : allPiles) {
                                    if ((card = pile.searchCard(value, suitName)) != null) {
                                        foundPile = pile;
                                        break;
                                    }
                                }

                                tempPile.addCard(card);
                                foundPile.removeCard(card);

                                if (isReversed) {
                                    card.hide();
                                } else {
                                    card.show();
                                }
                            }

                            if (currentPileCount < pileNumber) {
                                piles.get(currentPileCount).merge(tempPile);
                            } else if (currentPileCount < pileNumber + 4) {
                                finalPiles.get(currentPileCount - pileNumber)
                                        .merge(tempPile);

                                if (!tempPile.isEmpty()) {
                                    
                                    Card card = tempPile.peekTopCard();
                                    finalPiles.get(currentPileCount
                                            - pileNumber).cardSuit = card.cardSuit;
                                }
                            } else if (currentPileCount == pileNumber + 4) {
                                drawPile.merge(tempPile);
                            } else {
                                getPile.merge(tempPile);
                            }
                        }
                        currentPileCount++;
                    }
                }
            }

            for (Pile pile : allPiles) {
                ArrayList<Card> cards = new ArrayList<Card>();

                while (!pile.isEmpty()) {
                    cards.add(pile.drawCard());
                }

                for (Card card : cards) {
                    pile.addCard(card);
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
