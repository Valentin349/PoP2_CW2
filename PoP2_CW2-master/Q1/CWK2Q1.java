import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 *  @author Anonymous (do not change)
 *
 *  Question 1:
 *
 *  Implement the Shellsort algorithm (https://en.wikipedia.org/wiki/Shellsort) 
 *  for an array of up to 1000 signed doubles in Java. Your solution must use 
 *  concrete gaps of [1, 3, 7, 15, 31, 63, 127, 255, 511]. Your solution must 
 *  print the (partially) sorted array after each gap on a new line in the form:
 *      [a0, a1, a2, a3, ..., an]
 *  Where an is the nth element in the (partially) sorted array (please note 
 *  the space after the commas), and each element should be formatted to 2 
 *  decimal places (e.g. 1.00).
 *
*/

public class CWK2Q1 {
	public static void shell_sort(ArrayList<Double> array) {
		List<Integer> gaps = Arrays.asList(1, 3, 7, 15, 31, 63, 127, 255, 511);
		for (int gap: gaps){
			for (int i = gap; i < array.size(); i++){
				Double temp = array.get(i);
				int j;
				for (j = i; j>=gap && array.get(j-gap)>temp; j-= gap){
					array.set(j, array.get(j-gap));
				}
				array.set(j, temp);
				ArrayList<String> printList = new ArrayList<>();
				array.forEach(e -> printList.add(String.format("%.2f", e)));
				System.out.println(printList.toString());
			}
		}

	}

	public static void main(String[] args) {
		ArrayList<Double> testList = new ArrayList<Double>();
		testList.add(3.4);
		testList.add(6.55);
		testList.add(-12.2);
		testList.add(1.73);
		testList.add(140.98);
		testList.add(-4.18);
		testList.add(52.87);
		testList.add(99.14);
		testList.add(73.202);
		testList.add(-23.6);

		shell_sort(testList);
	}
}
