package gameplay;

/**
 * Timer class.
 *
 * @author Mor Barak and Caleb shere ID numbers: 2493276919 and 302620638
 *
 */
public class Timer {

    private long startTime;

    /**
     * reset timer.
     */
    public void reset() {
        this.startTime = System.nanoTime();
    }

    /**
     *
     * @return - the time.
     */
    public long timeElapsed() {
        long now = System.nanoTime();
        // We want to measure in hundreths of a second, so that 0.35 seconds is
        // an integer (35).
        return (now - this.startTime) / (long) Math.pow(10, 7);
    }
}
