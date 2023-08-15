/**
 * @author Talliente, Roshanaie, Liquindoli
 */

public class MinHeapMain {

	public static void main(String[] args) {
		System.out.println("The Min Heap is ");

		MinHeap<Integer> minHeap = new MinHeap<>(4, Integer::compareTo);

		//qui userà insert per inserire gli elem nell' heap
		minHeap.insert(5);
		minHeap.insert(3);
		minHeap.insert(17);
		minHeap.insert(4);
		minHeap.insert(8);
		minHeap.insert(15);
		minHeap.insert(25);
		minHeap.insert(23);
		minHeap.print();
		System.out.println(minHeap);
		System.out.println("Extract min");
		minHeap.extract_min();
		System.out.println(minHeap);

		minHeap.print();
		System.out.println("Add numbers");
		minHeap.insert(40);
		minHeap.print();
		minHeap.insert(90);
		minHeap.print();
		minHeap.insert(18);
		minHeap.print();
		//        minHeap.insert(1);
		//        minHeap.print();
		System.out.println("decrease ");
		try {
			minHeap.decrease_element(2, 2);
		} catch (MinHeapException e) {
			System.out.println(e);
			;
		}

		minHeap.print();

	}
}