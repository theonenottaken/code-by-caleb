package sprites;

import java.util.List;
import java.util.ArrayList;
import shapes.Point;
import biuoop.DrawSurface;

/**
 * AlienColumn class. This class implements Sprite.
 *
 * @author Mor Barak and Caleb shere ID numbers: 2493276919 and 302620638
 *
 */
public class AlienColumn implements Sprite {

    private List<Alien> aliens;
    private double initSpeed;
    private Point initLoc;
    private Alien lowest;
    private AlienFormation formation;

    /**
     *
     * @param speed
     *            - aliens speed.
     * @param p
     *            - location.
     * @param form
     *            - alien formation.
     */
    public AlienColumn(double speed, Point p, AlienFormation form) {
        this.aliens = new ArrayList<Alien>();
        this.initSpeed = speed;
        this.initLoc = p;
        this.lowest = null;
        this.formation = form;
    }

    /**
     * initialize Aliens.
     */
    public void initializeAliens() {
        double y = this.initLoc.getY();
        double x = this.initLoc.getX();
        for (int i = 0; i < 5; i++) {
            Point point = new Point(x, y);
            Alien alien = new Alien(point, this.initSpeed, this);
            this.aliens.add(alien);
            this.lowest = alien; // When the loop finishes, this will be the
                                 // last alien added.
            y += 40;
        }
    }

    /**
     * @param d
     *            - surface.
     */
    public void drawOn(DrawSurface d) {
        for (Alien alien : aliens) {
            alien.drawOn(d);
        }
    }

    /**
     * @param dt - time has passed.
     */
    public void timePassed(double dt) {
        for (Alien alien : aliens) {
            alien.timePassed(dt);
        }
    }

    /**
     *
     * @return the location.
     */
    public Point getLoc() {
        return this.aliens.get(0).getLoc();
    }

    /**
     *
     * @return - a shooting ball.
     */

    public Ball shoot() {
        return this.lowest.shoot();
    }

    /**
     *
     * @param wasHit
     *            - an alien that was being hit.
     */
    public void remove(Alien wasHit) {
        if (wasHit == this.lowest) {
            int i = this.aliens.indexOf(wasHit);
            if (i > 0) {
                this.lowest = this.aliens.get(i - 1);
            }
        }
        this.aliens.remove(wasHit);
        if (this.aliens.isEmpty()) {
            this.formation.remove(this);
        }
    }

    /**
     * moves it down.
     *
     */
    public void moveDown() {
        for (Alien alien : this.aliens) {
            alien.moveDown();
        }
        if (this.lowest.getLoc().getY() >= 500
                && !this.formation.ifReachedBottom()) {
            this.formation.loseLife();
            this.formation.reachedBottom();
        }
    }

    /**
     *
     * @return list of aliens.
     */
    public List<Alien> getAliens() {
        return this.aliens;
    }

    /**
     *
     * @param wasHit
     *            - an alien that was hit.
     */
    public void notifyHit(Alien wasHit) {
        this.formation.notifyHit(wasHit);
    }

    /**
     * reset Location.
     */
    public void resetLocation() {
        for (Alien alien : this.aliens) {
            alien.resetLocation();
        }
    }

}
