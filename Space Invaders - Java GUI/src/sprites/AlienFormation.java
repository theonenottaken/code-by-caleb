package sprites;

import java.util.List;
import java.util.ArrayList;
import java.util.Random;

import animations.GameLevel;
import biuoop.DrawSurface;
import biuoop.GUI;
import shapes.Point;

/**
 * AlienFormation class. This class implements Sprite.
 *
 * @author Mor Barak and Caleb shere ID numbers: 2493276919 and 302620638
 *
 */
public class AlienFormation implements Sprite {

    private List<AlienColumn> columns;
    private boolean movingRight;
    private double initSpeed;
    private AlienColumn mostRight;
    private Alien mostRecentHit;
    private GameLevel game;
    private boolean reachedBottom;

    /**
     *
     * @param speed
     *            - speed.
     */
    public AlienFormation(double speed) {
        this.columns = new ArrayList<AlienColumn>();
        this.movingRight = true;
        this.initSpeed = speed;
        this.mostRight = null;
        this.mostRecentHit = null;
        this.reachedBottom = false;
    }

    /**
     * initialize Columns.
     *
     */
    public void initializeColumns() {
        double x = 50;
        double y = 70;
        for (int i = 0; i < 10; i++) {
            Point point = new Point(x, y);
            AlienColumn column = new AlienColumn(this.initSpeed, point, this);
            column.initializeAliens();
            this.columns.add(column);
            this.mostRight = column;
            x += 50;
        }
    }

    /**
     * @param d
     *            - surface.
     */
    public void drawOn(DrawSurface d) {
        for (AlienColumn col : this.columns) {
            col.drawOn(d);
        }
    }

    /**
     * @param dt
     *            - time has passed.
     */
    public void timePassed(double dt) {
        for (AlienColumn col : this.columns) {
            col.timePassed(dt);
        }
        if (this.reachedEnd()) {
            for (AlienColumn col : this.columns) {
                col.moveDown();
            }
        }
    }

    /**
     *
     * @return if it reached to the end.
     */
    private boolean reachedEnd() {
        if (this.movingRight) {
            if (this.mostRight.getLoc().getX() >= 760) {
                movingRight = false;
                return true;
            }
        } else {
            if (this.columns.get(0).getLoc().getX() <= 0) {
                movingRight = true;
                return true;
            }
        }
        return false;
    }

    /**
     *
     * @param col
     *            - an alien column.
     */
    public void remove(AlienColumn col) {
        if (col == this.mostRight) {
            int i = this.columns.indexOf(col);
            if (i > 0) {
                this.mostRight = this.columns.get(i - 1);
            }
        }
        this.columns.remove(col);
    }

    /**
     *
     * @param g
     *            - game level.
     */
    public void addToGame(GameLevel g) {
        this.game = g;
        g.addSprite(this);
        for (AlienColumn column : this.columns) {
            for (Alien alien : column.getAliens()) {
                g.addCollidable(alien);
            }
        }
    }

    /**
     *
     * @return list of alien columns.
     */
    public List<AlienColumn> getColumns() {
        return this.columns;
    }

    /**
     *
     * @param alien
     *            - an alien.
     */
    public void notifyHit(Alien alien) {
        this.mostRecentHit = alien;
    }

    /**
     *
     * @return the most recent hit.
     */
    public Alien getHit() {
        return this.mostRecentHit;
    }

    /**
     *
     * @return a shooting ball.
     */
    public Ball shoot() {
        Random rand = new Random();
        int index = rand.nextInt(columns.size());
        AlienColumn chosen = this.columns.get(index);
        return chosen.shoot();
    }

    /**
     * reset location.
     */
    public void resetLocation() {
        for (AlienColumn column : this.columns) {
            column.resetLocation();
        }
        this.movingRight = true;
        this.reachedBottom = false;
    }

    /**
     * lose life.
     */
    public void loseLife() {
        this.game.loseLife();
    }

    /**
     *
     * @return if it reached to the bottom.
     */
    public boolean ifReachedBottom() {
        return this.reachedBottom;
    }

    /**
     * reached bottom.
     */
    public void reachedBottom() {
        this.reachedBottom = true;
    }

    /**
     * main function.
     * @param args - args.
     */
    /*public static void main(String[] args) {
        AlienFormation aliens = new AlienFormation(8);
        GUI screen = new GUI("Test", 800, 600);
        DrawSurface d = screen.getDrawSurface();
        aliens.initializeColumns();
        aliens.drawOn(d);
        screen.show(d);
    } */
}
