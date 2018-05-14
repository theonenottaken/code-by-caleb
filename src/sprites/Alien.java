package sprites;

import gameplay.BouncingBallAnimation;

import java.awt.Color;
import java.util.ArrayList;
import java.util.List;
import biuoop.DrawSurface;
import levels.ImageFill;
import collisions.Collidable;
import collisions.HitListener;
import collisions.Velocity;
import shapes.Point;
import shapes.Rectangle;

/**
 * Alien class. This class implements Sprite, Collidable.
 *
 * @author Mor Barak and Caleb shere ID numbers: 2493276919 and 302620638
 *
 */
public class Alien implements Sprite, Collidable {

    private Velocity v;
    private ImageFill image;
    private Block block;
    private double dt = 1.00 / 60;
    private AlienColumn column;
    private List<HitListener> listeners;
    private Point startLoc;
    private double initSpeed;

    /**
     *
     * @param loc - location of alien.
     * @param sp - initial speed.
     * @param col - the alien's column.
     */
    public Alien(Point loc, double sp, AlienColumn col) {
        this.block = new Block(loc, 40, 30, 1);
        this.startLoc = loc;
        this.block.setBlockColor(Color.BLACK);
        this.image = new ImageFill("resources/block_images/alien.png");
        sp = (sp + (1.00 / this.dt) - 1) / (1.00 / this.dt);
        this.initSpeed = sp;
        this.v = new Velocity(sp, 0);
        this.column = col;
        this.listeners = new ArrayList<HitListener>();
    }

    /**
     * @param d - surface.
     */
    public void drawOn(DrawSurface d) {
        this.block.drawOn(d);
        this.image.fillBlock(d, this.block);
    }

    /**
     *
     * @return - the location.
     */
    public Point getLoc() {
        return this.block.getCollisionRectangle().getUpperLeft();
    }

    /**
     *
     * @param p - new location.
     */
    public void setLoc(Point p) {
        this.block.getCollisionRectangle().setUpperLeft(p.getX(), p.getY());
    }

    /**
     * @param dt - time has passed.
     */
    public void timePassed(double dt) {
        this.dt = dt;
        Point newP = v.applyToPoint(block.getCollisionRectangle()
                .getUpperLeft());
        this.setLoc(newP);
    }

    /**
     * increment Velocity.
     */
    private void incrementVelocity() {
        // double speed = Math.abs(this.v.getDX());
        // this.v.setSpeed(speed * 4);

        Velocity newV = new Velocity(v.getDX() * 1.1, v.getDY());
        this.v = newV;
    }

    /**
     *
     * @return - a ball.
     */
    public Ball shoot() {
        double xCoord = this.block.getCollisionRectangle().getUpperLeft()
                .getX()
                + (this.block.getCollisionRectangle().getWidth() / 2);
        double yCoord = this.block.getCollisionRectangle().getUpperLeft()
                .getY()
                + this.block.getCollisionRectangle().getHeight();
        Point start = new Point(xCoord, yCoord + 1);
        BouncingBallAnimation bball = new BouncingBallAnimation();
        bball.createBounceBall(4);
        Ball ball = bball.getBall();
        ball.initVelocity(new Velocity(0, 300));
        ball.setVelocity(new Velocity(ball.getVelocity().getDX(), ball
                .getVelocity().getDY() * -1));
        ball.setLoc(start);
        return ball;
    }

    /**
     *
     * @param hl - hit listener.
     */
    public void addHitListener(HitListener hl) {
        this.listeners.add(hl);
    }

    /**
     * @param hl
     *            - Remove hl from the list of listeners to hit events.
     */
    public void removeHitListener(HitListener hl) {
        this.listeners.remove(hl);
    }

    /**
     * will be called whenever a hit() occurs.
     *
     * @param hitter
     *            - the ball that hit the current block.
     */

    private void notifyHit(Ball hitter) {

        this.column.notifyHit(this);
        // Make a copy of the hitListeners before iterating over them.
        List<HitListener> listeners = new ArrayList<HitListener>(this.listeners);
        // Notify all listeners about a hit event:
        for (HitListener hl : listeners) {
            hl.hitEvent(this.block, hitter);
        }
    }

    /**
     * @param hitter - the hitting ball.
     * @param collisionPoint - the collision point.
     * @param v - velocity.
     */
    public void hit(Ball hitter, Point collisionPoint, Velocity v) {
        notifyHit(hitter);
    }

    /**
     * @return the collision rectangle.
     */
    public Rectangle getCollisionRectangle() {
        return this.block.getCollisionRectangle();
    }

    /**
     *
     * @return a block.
     */
    public Block getBlock() {
        return this.block;
    }

    /**
     * moves it down.
     */
    public void moveDown() {
        Point newP = new Point(this.block.getCollisionRectangle()
                .getUpperLeft().getX(), this.block.getCollisionRectangle()
                .getUpperLeft().getY() + 40);
        this.setLoc(newP);
        Velocity newV = new Velocity(this.v.getDX() * (-1), 0);
        this.setVelocity(newV);
        this.incrementVelocity();

    }

    /**
     *
     * @param v - new velocity.
     */
    private void setVelocity(Velocity v) {
        this.v = v;
    }

    /**
     * removes from list.
     */
    public void remove() {
        this.column.remove(this);
    }

    /**
     * reset the location of aliens.
     */
    public void resetLocation() {
        setLoc(this.startLoc);
        setVelocity(new Velocity(this.initSpeed, 0));
    }
}
