import java.util.Scanner;
import java.io.*;

class 10_ShellSortModified {
	static void shellSort(int[] arr) {
		int len = arr.length;
		for (int gap = len / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < len; i++) {
				int key = arr[i];
				int j;

				for (j = i; j >= gap && arr[j - gap] > key; j -= gap) {
					arr[j] = arr[j - gap];
				}
				arr[j] = key;
			}
		}
	}

	static void printArray(int[] arr, char sep) {
		for (int i = 0; i < arr.length; i++) {
			System.out.print("" + arr[i] + sep);
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		System.out.print("Enter the number of elements: ");
		int n = Integer.parseInt(in.readLine());
		int[] nums = new int[n];

		System.out.print("Enter the " + n + " elements: ");
		for (int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(in.readLine());
		}

		System.out.print("\nElements before sorting: \n");
		printArray(nums, ' ');

		shellSort(nums);

		System.out.print("\n\nElements after sorting: \n");
		printArray(nums, ' ');
		System.out.println();
	}
}
