package collisions;

import sprites.Alien;

import sprites.AlienFormation;
import sprites.Ball;
import sprites.Block;
import counting.Counter;
import animations.GameLevel;

/**
 * AlienRemover class implements HitListener.
 *
 * @author Mor Barak and Caleb shere ID numbers: 2493276919 and 302620638
 *
 */
public class AlienRemover implements HitListener {

    private GameLevel game;
    private Counter removedAliens;
    private AlienFormation aliens;

    /**
     *
     * @param game - game level.
     * @param removedAliens - counts the remived aliens.
     * @param a - an aliaen formation.
     */
    public AlienRemover(GameLevel game, Counter removedAliens, AlienFormation a) {
        this.game = game;
        this.removedAliens = removedAliens;
        this.aliens = a;
    }

    /**
     * @param beingHit - the block that was hit.
     * @param hitter - the hitting blovk.
     */
    public void hitEvent(Block beingHit, Ball hitter) {
        if (hitter.getVelocity().getDY() < 0) {
            Alien alien = aliens.getHit();
            game.removeCollidable(alien);
            alien.remove();
            removedAliens.increase(1);
            alien.removeHitListener(this);
        }
    }
}
