/**
 * 正规表达式识别算术表达式
 * */

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
	final static String OP = "[\\(\\)\\+\\-\\*/]";
	final static String INT = "\\d+";
	final static String VAR = "[_a-z][_a-z0-9]*";
	final static String RR = OP + "|" + INT + "|" + VAR;
	final static Pattern P = Pattern.compile(RR);	
	
    public static void main(String [] args) throws FileNotFoundException {
        Scanner cin = new Scanner(new FileInputStream("3eg1.txt"));
        while(cin.hasNext()) {
        	String s = cin.nextLine();
        	Matcher m = P.matcher(s);
        	while(m.find()) {
        		System.out.print(s.substring(m.start(), m.end()));
        		System.out.print(" ");
        	}
        	System.out.println("");
        }
        cin.close();
    }   

}




