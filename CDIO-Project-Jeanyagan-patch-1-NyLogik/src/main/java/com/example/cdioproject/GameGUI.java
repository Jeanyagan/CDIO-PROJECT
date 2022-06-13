package com.example.cdioproject;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import javax.imageio.ImageIO;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLayeredPane;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.WindowConstants;

import com.example.cdioproject.Pile.PileType;

public class GameGUI extends JFrame implements ActionListener, MouseListener,
        MouseMotionListener {

    private JMenuBar menuBar;

    Map<String, String> text;
    JPanel panelGameArea;
    JPanel panelColumns;
    JPanel topColumns;
    JLayeredPane lp;
    GameEngine game;
    Pile tempPile;
    Point mouseOffset;

    public GameGUI(GameEngine game) {
        this.game = game;
        createTextMap();
        setTitle("Solitaire");
        setSize(900, 700);
        try {
            setContentPane((new JPanelWithBackground("src/main/java/com/example/cdioproject/images/background.jpg")));
        } catch (IOException e) {
            e.printStackTrace();
        }

        setLayout(new BorderLayout());

        panelGameArea = new JPanel();
        panelGameArea.setOpaque(false);
        panelGameArea.setLayout(new BoxLayout(panelGameArea, BoxLayout.PAGE_AXIS));

        setLocationRelativeTo(null);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        createTopMenu();
        FlowLayout flowLayout = new FlowLayout(FlowLayout.CENTER);
        flowLayout.setAlignOnBaseline(true);

        panelColumns = new JPanel();
        panelColumns.setOpaque(false);
        panelColumns.setLayout(flowLayout);
        panelColumns.setMinimumSize(new Dimension(200, 900));

        FlowLayout topFlow = new FlowLayout(FlowLayout.LEFT);
        topFlow.setAlignOnBaseline(true);

        topColumns = new JPanel();
        topColumns.setOpaque(false);
        topColumns.setLayout(topFlow);
        panelGameArea.add(topColumns);
        panelGameArea.add(panelColumns);
        add(panelGameArea);

        lp = getLayeredPane();
        setVisible(true);

        mouseOffset = new Point(0, 0);
        initializeComponents();
    }

    private void initializeComponents() {
        topColumns.removeAll();
        panelColumns.removeAll();

        for (Card card : game.deck.cards) {
            card.addMouseListener(this);
            card.addMouseMotionListener(this);
        }

        game.setupGame();
        for (Pile pile : game.piles) {
            panelColumns.add(pile);
        }

        topColumns.add(game.drawPile);
        topColumns.add(game.getPile);

        for (Pile pile : game.finalPiles) {
            topColumns.add(pile);
        }

        validate();
    }

    private void createTextMap() {
        text = new HashMap<String, String>();
        text.put("Game", "Game");
        text.put("New Game", "New Game");
        text.put("Save Game", "Save Game");
        text.put("Load Game", "Load Game");
        text.put("Exit", "Exit");
    }

    public void resetGame() {
        game.resetCards();
        initializeComponents();
        repaint();
    }

    private void createTopMenu() {
        menuBar = new JMenuBar();

        JMenu FileMenu = new JMenu("Game");
        FileMenu.setMnemonic(KeyEvent.VK_F);
        menuBar.add(FileMenu);

        menuOption[] fileOptions = new menuOption[]{
            new menuOption(text.get("New Game"), KeyEvent.VK_N),
            new menuOption(text.get("Save Game"), KeyEvent.VK_S),
            new menuOption(text.get("Load Game"), KeyEvent.VK_L),
            new menuOption(text.get("Exit"), KeyEvent.VK_X)
        };

        for (menuOption option : fileOptions) {
            JMenuItem opt = new JMenuItem(option.name);
            if (option.shorcut != 0) {
                opt.setMnemonic(option.shorcut);
            }

            opt.addActionListener(this);
            FileMenu.add(opt);
        }

        setJMenuBar(menuBar);
    }

    class menuOption {

        public String name;
        public Integer shorcut = 0;

        public menuOption(String name, Integer shorcut) {
            this.name = name;
            this.shorcut = shorcut;
        }
    }

    public void actionPerformed(ActionEvent e) {

        if (e.getSource() instanceof JMenuItem) {
            handleMenuInteraction(e);
        }

    }

    private void handleMenuInteraction(ActionEvent e) {
        JMenuItem menuItem = (JMenuItem) e.getSource();

        if (menuItem.getText().equals(text.get("Exit"))) {
            this.dispose();
            return;
        }
        if (menuItem.getText().equalsIgnoreCase(text.get("New Game"))) {
            resetGame();
            return;
        }
        if (menuItem.getText().equalsIgnoreCase(text.get("Save Game"))) {
            game.saveGame();
            JOptionPane.showMessageDialog(null, "Successfully saved!", "Solitaire Game", JOptionPane.INFORMATION_MESSAGE);
            return;
        }
        if (menuItem.getText().equalsIgnoreCase(text.get("Load Game"))) {
            game.loadGame();
            validate();
            return;
        }
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        if (tempPile != null) {
            Point pointPos = getLocationOnScreen();
            pointPos.x = e.getLocationOnScreen().x - pointPos.x - mouseOffset.x;
            pointPos.y = e.getLocationOnScreen().y - pointPos.y - mouseOffset.y;

            tempPile.setLocation(pointPos);
        }
        repaint();
    }

    @Override
    public void mouseMoved(MouseEvent e) {

    }

    @Override
    public void mouseClicked(MouseEvent e) {
        if (e.getComponent() instanceof Card) {
            Card card = (Card) e.getComponent();
            Pile pile = (Pile) card.getParent();

            switch (pile.pileType) {
                case Draw:
                    game.drawCards();
                    break;
                case Normal:
                    game.clickPile(pile);
                    break;
                case Get:
                    game.turnGetPile();
                    break;
            }
            repaint();
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {
        if (e.getComponent() instanceof Card) {
            Card card = (Card) e.getComponent();
            boolean reverseFlag=card.isReversed;
            if (reverseFlag) {
                return;
            }

            Pile pile = (Pile) card.getParent();

            if (pile.cards.isEmpty() || pile.pileType == PileType.Final) {
                return;
            }

            tempPile = pile.split(card);

            lp.add(tempPile, JLayeredPane.DRAG_LAYER);

            Point pointPos = getLocationOnScreen();
            mouseOffset = e.getPoint();
            pointPos.x = e.getLocationOnScreen().x - pointPos.x - mouseOffset.x;
            pointPos.y = e.getLocationOnScreen().y - pointPos.y - mouseOffset.y;

            tempPile.setLocation(pointPos);

            repaint();
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        if (tempPile != null) {

            Point mousePos = e.getLocationOnScreen();
            boolean match = false;
            ArrayList<Pile> droppable = new ArrayList<Pile>(game.piles);
            droppable.addAll(game.finalPiles);

            for (Pile p : droppable) {
                Point pilePos = p.getLocationOnScreen();
                Rectangle rac = p.getBounds();
                rac.x = pilePos.x;
                rac.y = pilePos.y;

                if (rac.contains(mousePos) && p.acceptsPile(tempPile)) {
                    p.merge(tempPile);
                    match = true;
                    break;
                }
            }

            if (match==false) {
                tempPile.pileParent.merge(tempPile);
            }

            lp.remove(tempPile);
            tempPile = null;

            repaint();
            boolean check=game.checkIfWin();
            if (check) {
                JOptionPane.showMessageDialog(null, "You win! Congratulation!", "Solitaire Game", JOptionPane.INFORMATION_MESSAGE);
                resetGame();
            }
        }
    }

    public void mouseEntered(MouseEvent arg0) {
    }

    public void mouseExited(MouseEvent arg0) {
    }

    public class JPanelWithBackground extends JPanel {

        private Image backgroundImage;

        public JPanelWithBackground(String fileName) throws IOException {
            File fileImage = new File(fileName);
            backgroundImage = ImageIO.read(fileImage);
        }

        public void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.drawImage(backgroundImage, 0, 0, this);
        }
    }
}
