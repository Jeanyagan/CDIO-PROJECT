package solitaire;

public class Main {

    GameEngine game;
    GameGUI gui;

    public Main() {
        game = new GameEngine();
        gui = new GameGUI(game);
    }

    public static void main(String[] args) {
        Main main = new Main();
    }
}
