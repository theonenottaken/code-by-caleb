package animations;

import biuoop.DrawSurface;
import biuoop.GUI;
import gameplay.BouncingBallAnimation;
import gameplay.GameEnvironment;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.awt.Color;

import counting.Counter;
import counting.ScoreTrackingListener;
import collisions.AlienRemover;
import collisions.BallRemover;
import collisions.BlockRemover;
import collisions.Collidable;
import levels.LevelInformation;
import levels.SpaceBattle;
import shapes.Point;
import sprites.Alien;
import sprites.AlienColumn;
import sprites.AlienFormation;
import sprites.Background;
import sprites.Ball;
import sprites.Block;
import sprites.ColoredBackground;
import sprites.LivesIndicator;
import sprites.NameIndicator;
import sprites.Paddle;
import sprites.ScoreIndicator;
import sprites.Sprite;
import sprites.SpriteCollection;
import biuoop.KeyboardSensor;
import gameplay.Timer;

/**
 * GameLevel class. This class implements Animation.
 *
 * @author Mor Barak and Caleb shere ID numbers: 2493276919 and 302620638
 *
 */
public class GameLevel implements Animation {
    private AnimationRunner runner;
    private boolean running;
    private SpriteCollection sprites;
    private GameEnvironment environment;
    private Counter alienCounter;
    private Counter ballCounter;
    private Counter myCounter;
    private Counter shieldBlocksRemoved;
    private AlienRemover alienRemover;
    private BallRemover ballRemover;
    private BlockRemover shieldRemover;
    private ScoreTrackingListener scoreTracking;
    private Counter score;
    private ScoreIndicator indicator;
    private Counter numberOfLives;
    private LivesIndicator lives;
    private KeyboardSensor keyboard;
    private SpaceBattle info;
    private Paddle paddle;
    private Point padStart;
    private NameIndicator levelName;
    private Timer shipTimer;
    private Timer alienTimer;
    private AlienFormation aliens;
    private List<Ball> ballsInPlay;

    /**
     * constructor.
     *
     * @param info
     *            - the current level's information.
     * @param score
     *            - the current score.
     * @param lives
     *            - the current lives.
     * @param runner
     *            - an animation runner.
     * @param keyboard
     *            - a keyboard's key.
     */
    public GameLevel(SpaceBattle info, Counter score, Counter lives,
            AnimationRunner runner, KeyboardSensor keyboard) {
        this.runner = runner;
        this.running = false;
        this.sprites = new SpriteCollection(this.runner.getDt());
        this.environment = new GameEnvironment();
        this.ballCounter = new Counter();
        this.alienCounter = null;
        this.myCounter = new Counter();
        this.alienRemover = null;
        this.ballRemover = new BallRemover(this, this.ballCounter);
        this.score = score;
        this.scoreTracking = new ScoreTrackingListener(this.score);
        this.indicator = new ScoreIndicator(this.scoreTracking);
        this.numberOfLives = lives;
        this.lives = new LivesIndicator(numberOfLives);
        this.keyboard = keyboard;
        this.info = info;
        levelName = new NameIndicator(this.info.levelName());
        if (info.levelName().equals("Wide Easy")) {
            this.padStart = new Point(100, 560);
        } else {
        	this.padStart = new Point(400, 560);
        }
        this.shipTimer = new Timer();
        this.alienTimer = new Timer();
        this.shieldBlocksRemoved = new Counter();
        this.shieldRemover = new BlockRemover(this, this.shieldBlocksRemoved);
        this.ballsInPlay = new ArrayList<Ball>();
    }

    /**
     *
     * @return the number of balls.
     */
    public Counter getNumOfBalls() {
        return this.myCounter;
    }

    /**
     *
     * @param c
     *            - set the number of balls.
     */
    public void setNumOfBalls(int c) {
        this.myCounter.increase(c);
    }

    /**
     *
     * @return the counter that counts the number of blocks removed.
     */
    public Counter getAliensRemoved() {
        return this.alienCounter;
    }

    /**
     *
     * @return the counter that counts number of lives
     */
    public Counter getLives() {
        return this.numberOfLives;
    }

    /**
     *
     * @param c
     *            - add it to collidable list.
     */
    public void addCollidable(Collidable c) {
        this.environment.addCollidable(c);
    }

    /**
     *
     * @param s
     *            - add it to the sprites list.
     */
    public void addSprite(Sprite s) {
        this.sprites.addSprite(s);

    }
    
    public void addBall(Ball ball) {
    	this.ballsInPlay.add(ball);
    }
    
    public void removeBalls() {
    	while (!this.ballsInPlay.isEmpty()) {
    		//this.removeSprite(ball);
    		Ball ball = ballsInPlay.get(0);
    		ball.removeFromGame(this);
    		ballsInPlay.remove(ball);
    	}
    }

    /**
     * creates the balls on top of the paddle.
     */
    /*public void createBallsOnTopOfPaddle() {

        Random rand = new Random();
        int xCoord = (int) this.getPaddle().getCollisionRectangle()
                .getUpperLeft().getX();
        int yCoord = (int) this.getPaddle().getCollisionRectangle()
                .getUpperLeft().getY();
        int counter = 0;
        for (int i = 0; i < info.numberOfBalls(); i++) {
            System.out.println("a ball has been created! " + counter);
            counter++;
            int x = rand.nextInt(info.paddleWidth() - 2) + xCoord;
            Point bCenter = new Point(x, yCoord - 1);
            BouncingBallAnimation bball = new BouncingBallAnimation();
            bball.createBounceBall(5);
            Ball ball = bball.getBall();
            ball.initVelocity(info.initialBallVelocities().get(i));
            ball.setLoc(bCenter);
            ball.setGameEnvironment(this.environment);
            ball.addToGame(this);
        }
    }*/
    
    private void spaceShipShoot() {
    	int xCoord = (int) this.paddle.getCollisionRectangle().getUpperLeft().getX();
    	int yCoord = (int) this.paddle.getCollisionRectangle().getUpperLeft().getY();
    	Point center = new Point(xCoord + (this.paddle.getCollisionRectangle().getWidth() /
    			       2), yCoord - 1);
    	BouncingBallAnimation bball = new BouncingBallAnimation();
    	bball.createBounceBall(3);
    	Ball ball = bball.getBall();
    	ball.initVelocity(info.initialBallVelocities().get(0));
    	ball.setLoc(center);
    	ball.setColor(Color.WHITE);
    	ball.setGameEnvironment(this.environment);
    	ball.addToGame(this);
    	this.addBall(ball);
    }

    /**
     * initialize the paddle.
     */
    private void initPaddle() {
        //System.out.println("paddle speed in game level is: "
                //+ info.paddleSpeed());
        Paddle pad = new Paddle(this.padStart, info.paddleWidth(), 20, info.paddleSpeed());
        pad.addHitListener(this.ballRemover);
        pad.addToGame(this);
        this.paddle = pad;
        
    }

    /**
     * initialize the background blocks.
     */
    /*public void initBackgroundBlocks() {
        Point ePoint1 = new Point(0, 21);
        Point ePoint2 = new Point(0, 31);
        Point ePoint3 = new Point(790, 31);
        Point ePoint4 = new Point(0, 590);
        Block eBlock1 = new Block(ePoint1, 800, 10);
        eBlock1.setBlockColor(Color.GRAY);

        Block eBlock2 = new Block(ePoint2, 10, 570, 0);
        eBlock2.setBlockColor(Color.GRAY);
        Block eBlock3 = new Block(ePoint3, 10, 570, 0);
        eBlock3.setBlockColor(Color.GRAY);
        Block deathBlock = new Block(ePoint4, 800, 10, 0);
        deathBlock.setBlockColor(Color.GRAY);
        deathBlock.addHitListener(ballRemover);
        eBlock1.addToGame(this);
        deathBlock.addToGame(this);
        eBlock3.addToGame(this);
        eBlock2.addToGame(this);
    } */

    /**
     * initialize the Aliens.
     */
    private void initAliens() {
    	this.alienCounter = new Counter();
    	this.aliens = info.getAllAliens();
    	this.alienRemover = new AlienRemover(this, this.alienCounter, aliens);
		aliens.addToGame(this);
		for (AlienColumn column : aliens.getColumns()) {
			for (Alien alien : column.getAliens()) {
				alien.addHitListener(this.alienRemover);
				alien.addHitListener(this.scoreTracking);
				alien.addHitListener(this.ballRemover);
			}
		}
    }
    
    private void initShields() {

    	for (Block shieldBlock : info.blocks()) {
    		shieldBlock.addToGame(this);
    		shieldBlock.addHitListener(this.ballRemover);
    		shieldBlock.addHitListener(this.shieldRemover);
    	}
    }

    /**
     * initialize all the level together.
     */
    public void initialize() {
        ColoredBackground back = new ColoredBackground(1);
        this.sprites.addSprite(back);
        initPaddle();
        //initBackgroundBlocks();
        initAliens();
        initShields();
        Point eScore = new Point(0, 0);
        Block eScoreBlock = new Block(eScore, 800, 20);
        eScoreBlock.setBlockColor(Color.LIGHT_GRAY);
        eScoreBlock.addToGame(this);
        eScoreBlock.addHitListener(this.ballRemover);
        Point bottom = new Point(0, 595);
        Block bottomBlock = new Block(bottom, 800, 5);
        bottomBlock.setBlockColor(Color.BLACK);
        bottomBlock.addHitListener(this.ballRemover);
        bottomBlock.addToGame(this);
        this.indicator.addToGame(this);
        this.lives.addToGame(this);
        this.levelName.addToGame(this);
        this.shipTimer.reset();
        this.alienTimer.reset();

    }

    /**
     *
     * @return the animation runner.
     */
    public AnimationRunner getRunner() {
        return this.runner;
    }

    /**
     * @return - either the game level should stop or not.
     */
    public boolean shouldStop() {
        return !this.running;
    }

    /**
     * @param d
     *            - current fraw surface.
     * @param dt
     *            - in order to normalize it with the frame rate.
     */
    public void doOneFrame(DrawSurface d, double dt) {
    	
        this.sprites.drawAllOn(d);
        this.sprites.notifyAllTimePassed();
        if (this.alienCounter.getValue() == this.info.numberOfBlocksToRemove()) {
            this.running = false;
        } //else if (this.myCounter.getValue() == 0) {
            //this.numberOfLives.decrease(1);
            //this.running = false;
        //}
        if (this.keyboard.isPressed("p")) {
            this.runner.run(new KeyPressStoppableAnimation(this.keyboard,
                    KeyboardSensor.SPACE_KEY, new PauseScreen(this.keyboard)));
        }
        if (this.keyboard.isPressed(KeyboardSensor.SPACE_KEY)) {
        	if (this.shipTimer.timeElapsed() >= 35) {
        	     spaceShipShoot();
        	     shipTimer.reset();
        	}
        }
        if (this.alienTimer.timeElapsed() >= 50) {
        	Ball shot = this.aliens.shoot();
        	shot.setGameEnvironment(this.environment);
        	shot.addToGame(this);
        	this.addBall(shot);
        	alienTimer.reset();
        }
    }

    /**
     * plays one turn of the level.
     */
    public void playOneTurn() {
        this.paddle.setLocation(this.padStart);
        //this.createBallsOnTopOfPaddle();
        this.aliens.resetLocation();
        this.runner.run(new CountdownAnimation(2, 3, sprites, this.keyboard,
                this));
        this.running = true;
        // use our runner to run the current animation -- which is one turn of
        // the game.
        this.runner.run(this);

    }

    /**
     * runs the level.
     *
     */
    public void run() {
        playOneTurn();
        while (this.numberOfLives.getValue() > 0) {
            //createBallsOnTopOfPaddle();
            playOneTurn();
        }
        this.runner.getGUI().close();
    }

    /**
     *
     * @param c
     *            - removes it from the collidable's list.
     */
    public void removeCollidable(Collidable c) {
        this.environment.removeCollidable(c);
    }

    /**
     *
     * @param s
     *            - removes it from the sprite's list.
     */
    public void removeSprite(Sprite s) {
        this.sprites.removeSprite(s);
    }

    /**
     *
     * @return - the information of the current level.
     */
    public LevelInformation getInfo() {
        return this.info;
    }

    /**
     *
     * @return the current paddle.
     */
    public Paddle getPaddle() {
        return this.paddle;
    }

    /**
     *
     * @return - the point where the paddle need to start from.
     */
    public Point getPadStart() {
        return this.padStart;
    }
    
    public void loseLife() {
        this.numberOfLives.decrease(1);
        this.removeBalls();
        this.running = false;
    }
}