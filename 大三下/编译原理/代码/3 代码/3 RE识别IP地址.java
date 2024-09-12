/**
 * 正规表达式识别IP地址
 * */

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.regex.Pattern;

public class Main {
    final static String JIE = "[0-9]{1,3}";
    final static String R = JIE + "\\." + JIE + "\\." + JIE + "\\." + JIE;
	
    public static void main(String [] args) throws FileNotFoundException {
        Scanner cin = new Scanner(new FileInputStream("1.txt"));
        while(cin.hasNext()) {
        	String s = cin.nextLine();
        	if(Pattern.matches(R, s)){
                System.out.print(s);
            }
        	System.out.println("");
        }
        cin.close();
    }   

}




