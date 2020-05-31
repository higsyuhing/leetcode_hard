/* The read4 API is defined in the parent class Reader4.
      int read4(char[] buf); */
 
public class Solution extends Reader4 {
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    private char[] buf4 = new char[4];
    private int buf4Index = 4;
    private int buf4Size = 4;
    public int read(char[] buf, int n) {
        int i = 0;
        while (i < n) {
            if (buf4Index >= buf4Size) {
               buf4Size = read4(buf4);
               buf4Index = 0;
               if (buf4Size == 0) {
                   break;
               }
            }
            buf[i] = buf4[buf4Index];
            buf4Index ++;
            i ++;
        }
        return i;
    }
}

/*
use a buffer is fine.. accepted OK.. 
from: 
https://cheonhyangzhang.wordpress.com/2016/12/22/158-leetcode-java-read-n-characters-given-read4-ii-call-multiple-times-add-to-list-questioneditorial-solution-hard/

*/
