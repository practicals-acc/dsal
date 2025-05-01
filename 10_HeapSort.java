// HeapSort.java

public class 10_HeapSort {

	// Main function to run the program
	public static void main(String[] args) {
		int[] array = {12, 11, 13, 5, 6, 7};

		System.out.println("Original array:");
		printArray(array);

		heapSort(array);

		System.out.println("Sorted array:");
		printArray(array);
	}

	// Function to perform heap sort
	public static void heapSort(int[] arr) {
		int n = arr.length;

		// Build max heap
		for (int i = n / 2 - 1; i >= 0; i--) {
			heapify(arr, n, i);
		}

		// Extract elements from heap one by one
		for (int i = n - 1; i > 0; i--) {
			// Move current root to end
			swap(arr, 0, i);

			// Call max heapify on the reduced heap
			heapify(arr, i, 0);
		}
	}

	// To heapify a subtree rooted with node i which is an index in arr[]. n is size of heap
	public static void heapify(int[] arr, int n, int i) {
		int largest = i;		 // Initialize largest as root
		int left = 2 * i + 1;	 // left child
		int right = 2 * i + 2;	 // right child

		// If left child is larger than root
		if (left < n && arr[left] > arr[largest])
			largest = left;

		// If right child is larger than largest so far
		if (right < n && arr[right] > arr[largest])
			largest = right;

		// If largest is not root
		if (largest != i) {
			swap(arr, i, largest);

			// Recursively heapify the affected subtree
			heapify(arr, n, largest);
		}
	}

	// Utility function to swap two elements in array
	public static void swap(int[] arr, int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	// Utility function to print the array
	public static void printArray(int[] arr) {
		for (int num : arr)
			System.out.print(num + " ");
		System.out.println();
	}
}
