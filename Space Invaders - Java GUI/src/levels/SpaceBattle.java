package levels;

import java.awt.Color;
import java.util.List;

import collisions.Velocity;
import shapes.Point;
import sprites.AlienFormation;
import sprites.Block;
import sprites.ColoredBackground;

/**
 * class SpaceBattle. This class extends AllLevels.
 *
 * @author Mor Barak and Caleb shere ID numbers: 2493276919 and 302620638
 *
 */
public class SpaceBattle extends AllLevels {

    private double alienSpeed;
    private int shieldSize = 5;
    private AlienFormation aliens;

    /**
     *
     * @param num - int.
     * @param speed - the speed.
     */
    public SpaceBattle(int num, double speed) {
        super();
        super.setNumBalls(0);
        super.setPaddle(400, 70);
        super.setName("Battle No. " + num);
        super.setBackground(new ColoredBackground(1));
        super.setToRemove(50);
        this.makeBlockList(); // Shields
        this.alienSpeed = speed;
        this.makeAliens();
        this.makeVelocityList();
    }

    /**
     * create aliens.
     */
    private void makeAliens() {
        this.aliens = new AlienFormation(this.alienSpeed);
        aliens.initializeColumns();
    }

    /**
     * makes Blocks List.
     */
    public void makeBlockList() {
        List<Block> list = super.blocks();
        int y = 500;
        int x = 125;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 20; k++) {
                    Point point = new Point(x, y);
                    Block block = new Block(point, shieldSize, shieldSize, 1);
                    block.setBlockColor(Color.CYAN);
                    list.add(block);
                    x += shieldSize;
                }
                y += shieldSize;
                x -= 100;
            }
            y = 500;
            x += 225;
        }
    }

    /**
     * makes Velocities List.
     */
    public void makeVelocityList() {
        List<Velocity> list = super.initialBallVelocities();
        Velocity shipBallV = new Velocity(0, -600);
        list.add(shipBallV);
    }

    /**
     *
     * @return an alien.
     */
    public AlienFormation getAllAliens() {
        return this.aliens;
    }
}
