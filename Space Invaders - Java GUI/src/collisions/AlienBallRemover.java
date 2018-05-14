package collisions;

import sprites.Ball;
import sprites.Block;
import counting.Counter;
import animations.GameLevel;

/**
 * AlienBallRemover class implements HitListener.
 *
 * @author Mor Barak and Caleb shere ID numbers: 2493276919 and 302620638
 *
 */
public class AlienBallRemover implements HitListener {

    private GameLevel game;
    private int shieldLevel;

    /**
     * constructor.
     * @param game - game level.
     */
    public AlienBallRemover(GameLevel game) {
        this.game = game;
    }

    /**
     * @param beingHit - the block that was hit.
     * @param hitter - the hitting blovk.
     */
    public void hitEvent(Block beingHit, Ball hitter) {
        int y = hitter.getY();
        if (y < shieldLevel) {

        }
    }

}
