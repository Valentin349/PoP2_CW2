import java.util.ArrayList;

/**
 *  @author Anonymous (do not change)
 *
 *  Question 2:
 *
 *  Implement interpolation search for a list of Strings in Java
 *  using the skeleton class provided. The method should return
 *  the position in the array if the string is present, or -1 if
 *  it is not present.
*/

public class CWK2Q2 {

	public static int interpolation_search(ArrayList<String> array, String item) {
		int low = 0;
		int high = array.size() - 1;
		int mid;
		int key = array.indexOf(item);
		ArrayList<Integer> indexArr = new ArrayList<>();
		array.forEach(e -> indexArr.add(array.indexOf(e)));

		while ((!indexArr.get(high).equals(indexArr.get(low))) && (key >= indexArr.get(low)) && (key <= indexArr.get(high))){
			mid = low + ((key - indexArr.get(low)) * (high - low) / (indexArr.get(high) - indexArr.get(low)));
			if (indexArr.get(mid) < key){
				low = mid + 1;
			} else if (key < indexArr.get(mid)){
				high = mid - 1;
			} else {
				return mid;
			}
		}

		if (key == indexArr.get(low)){
			return low;
		} else {
			return -1;
		}
	}

	public static void main(String[] args) {
		ArrayList<String> testList = new ArrayList<String>();
		testList.add("Hello");
		testList.add("World");
		testList.add("How");
		testList.add("Are");
		testList.add("You");

		int result = interpolation_search(testList, "How");
		System.out.println("Result = " + result);
	}
}
