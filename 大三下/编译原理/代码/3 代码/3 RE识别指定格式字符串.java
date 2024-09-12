/**
 * 正规表达式识别指定格式的字符串
 * */

import java.io.FileNotFoundException;
import java.util.regex.Pattern;

public class Main {
    final static String R = "(1|01*0)*";
	final static String [] A = {
        "0010111110", "000", "111", "00"
    };
    public static void main(String [] args) throws FileNotFoundException {
        for(String a: A){
            if(Pattern.matches(R, a)){
                System.out.println("Yes: " + a);
            }else{
                System.out.println("No:  " + a);
            }
        }
    }   

}




