/***
 * Caleb Shere 2493276919
 * Benjamin Wexler 337955744
 * Liron Cohen 305610255
 * Adi Shlomo 308192806
 ***/

package DatabaseEx4.Model;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;

/**
 * Checking DML queries class.
 */
public class DML {

    private ArrayList<String> reservedWords;

    /**
     * Class constructor.
     * Initialize a list of saved querie's words.
     */
    public DML() {
        reservedWords = new ArrayList<>();
        try {
            initializeList();
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }

    /**
     * Initialize a list of saved querie's words.
     * @throws FileNotFoundException 
     */
    public void initializeList() throws FileNotFoundException {
        //read all reserved files from a file and add them to a list
        try {
            BufferedReader buffer = new BufferedReader(new FileReader("reservedWords.txt"));
            String word;
            while ((word = buffer.readLine()) != null) {
                reservedWords.add(word);
            }
        } catch (Exception ex) {
            System.out.println(ex);
        }

    }

    /**
     * Get a querty, split it and check each word for lower case.
     * @param message - a query
     * @return true or false for valid word
     */
    public boolean checkLowerCase(String message) {
        String[] splited = message.split(" ");
        int i;
        int size =  splited.length;
        String upperWord, word;
        //check each word in the list
        for(i = 0; i < size; i++)
        {
            word = splited[i];
            upperWord = word.toUpperCase();
            if (reservedWords.contains(upperWord))
            {
                if (!upperWord.equals(word))
                    return false;
            }
        }
        return true;
    }
}

