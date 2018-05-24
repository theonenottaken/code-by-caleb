/***
 * Caleb Shere 2493276919
 * Benjamin Wexler 337955744
 * Liron Cohen 305610255
 * Adi Shlomo 308192806
 ***/

package DatabaseEx4.Model;

/**
 *
 * This class contains error information to be used when a script is run
 */
public class ErrorInfo {
    private boolean error;
    private String command;
    /**
     * Constructor
     * @param bool - true if an error occured. False if not.
     * @param comm - the command that caused the error
     */
    public ErrorInfo(boolean bool, String comm) {
        this.error = bool;
        this.command = comm;
    }
    
    /**
     * 
     * @return the error field 
     */
    public boolean isError() {
        return error;
    }
    
    /**
     * 
     * @return the command field
     */
    public String getErrorCommand() {
        return command;
    }
}
