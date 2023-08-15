import java.util.Arrays;
import java.util.Comparator;

/**
 * It represents a minimum heap (zero indexed)
 * @author Talliente, Roshanaie, Liquindoli
 * @param <T>: type of minimum heap elements
 */

public class MinHeap<T> {
	int maxSize;
	int lastPosition;
	T[] heap;
	Comparator<? super T> comparator = null;

	/**
	 * It creates an empty minimum heap.
	 * It accepts as input a comparator implementing the
	 * precedence relation between the array elements.
	 * @param comparator: a comparator implementing the precedence relation between the array elements.
	 * @param size: initial size of minHeap
	 */
	public MinHeap(int size, Comparator<? super T> comparator) {
		lastPosition = -1;
		this.maxSize = size;
		this.heap = (T[]) new Comparable[this.maxSize];
		this.comparator = comparator;
	}

	/**
	 * It inserts an element in the heap
	 * @param element: the element to be added
	 */
	public void insert(T element) {
		if (lastPosition + 1 >= maxSize) {
			grow();
		}
		heap[++lastPosition] = element;
		trickle_up(lastPosition);
	}

	/**
	 * @return: The heap size
	 */
	public int size() {
		return this.lastPosition + 1;
	}

	/**
	 * @param index: index of the element that we search
	 * @return: an element of the heap
	 */
	public T getElem(int index) {
		return heap[index];
	}

	/**
	 * @param index: the son's index
	 * @throws MinHeapException if the parameter index is zero
	 * @return: the father of an element
	 */
	public T get_parent(int index) throws MinHeapException {
		if (index == 0)
			throw new MinHeapException("Root index passed. Root has no parent.");
		return heap[(int) Math.floor((index - 1) / 2)];
	}

	/**
	 * @param index: the father's index
	 * @throws MinHeapException if the parameter index*2+1 is bigger than the heap size or the index is invalid
	 * @return: the left son of the father
	 */
	public T get_left(int index) throws MinHeapException {
		if (index > lastPosition)
			throw new MinHeapException("Out of bound index.");
		else if (2 * index + 1 > lastPosition)
			throw new MinHeapException("No child found.");
		return heap[2 * index + 1];
	}

	/**
	 * @param index: the father's index
	 * @throws MinHeapException if the parameter (index*2)+2 is bigger than the heap size or the index is invalid
	 * @return: the right son of the father
	 */
	public T get_right(int index) throws MinHeapException {
		if (index > lastPosition)
			throw new MinHeapException("Out of bound index.");
		else if (2 * index + 2 > lastPosition)
			throw new MinHeapException("No child found.");
		return heap[2 * index + 2];
	}

	/**
	 * @return: the minimum element of the heap
	 */
	public T extract_min() {
		T min = heap[0];
		swap(lastPosition--, 0);
		trickle_down(0); //Heapify
		return min;
	}

	/**
	 * Support method for the insert/decrease_element in the new Heap
	 * It brings up the elem in the correct position based on the comparator
	 * @param position: position of the last element added
	 **/
	private void trickle_up(int position) {
		if (position == 0)
			return;
		int parent = (int) Math.floor((position - 1) / 2);
		if ((this.comparator).compare(heap[parent], heap[position]) > 0) {
			swap(position, parent);
			trickle_up(parent);
		}
	}

	/**
	 * Support method for the extract_min in the new Heap
	 * It sinks the elem in its correct position based on the comparator 
	 * @param parent: Index of the root
	 **/
	private void trickle_down(int parent) {
		int left = 2 * parent + 1;
		int right = 2 * parent + 2;

		// when the parent has only one left child that is the last element, and it is less than the parent
		if (left == lastPosition && this.comparator.compare(heap[parent], heap[left]) > 0) {
			swap(parent, left);
			return;
		} // when the right child is the last element, and it is less than the parent
		if (right == lastPosition && this.comparator.compare(heap[parent], heap[right]) > 0) {
			swap(parent, right);
			return;
		}
		if (left >= lastPosition || right >= lastPosition)
			return;

		// Exchange parent with the largest between the children
		if (this.comparator.compare(heap[left], heap[right]) < 0
				&& this.comparator.compare(heap[parent], heap[left]) > 0) { // exchange with the left child as it is larger than the right one
			swap(parent, left);
			trickle_down(left);
		} else if (this.comparator.compare(heap[parent], heap[right]) > 0) { // exchange with the right child as it is larger than the left one
			swap(parent, right);
			trickle_down(right);
		}
	}

	/**
	 * Swap 2 elements
	 * @param from: element to swap from
	 * @param to:   element to swap from with.
	 */
	private void swap(int from, int to) {
		T temp = heap[to];
		heap[to] = heap[from];
		heap[from] = temp;
	}

	/**
	 * Decreases value of key at index 'i' to new_val. It is assumed that new_val is smaller than harr[i].
	 * @param index:     the index of the element to be decreased
	 * @param new_value: the new value to be inserted
	 * @throws MinHeapException if the index is minor than 0, bigger than the heap size or the new value is not less than the old value.
	 */
	public void decrease_element(int index, T new_value) throws MinHeapException {
		if (index < 0 || index > lastPosition)
			throw new MinHeapException("DECREASE_ELEMENT: index out of bound.");
		if (this.comparator.compare(new_value, heap[index]) > 0)
			throw new MinHeapException("DECREASE_ELEMENT: new value is bigger than the old value. ");
		heap[index] = new_value;
		trickle_up(index);
	}

	/**
	 * @return true if the Heap is empty
	 */
	public boolean isEmpty() {
		return this.lastPosition == -1;
	}

	/**
	 * @param o: element which we want to find the position in the heap
	 * @return the index of an element in the heap
	 */
	public int indexOf(T o) {
		if (o != null) {
			final T[] es = heap;
			for (int i = 0, n = lastPosition + 1; i < n; i++)
				if (o.equals(es[i]))
					return i;
		}
		return -1;
	}

	/**
	 * Support method for increasing dynamically the Heap size
	 */
	private void grow() {
		int newCapacity = maxSize * 2;
		heap = Arrays.copyOf(heap, newCapacity);
	}

	@Override
	public String toString() {
		return "MinHeap{" +
				"heap=" + Arrays.toString(heap) +
				'}';
	}

	/**
	 * Prints in a tree-looking way the minHeap
	 */
	public void print() {
		StringBuilder sb = new StringBuilder();
		int max = 0;
		for (int i = 0; i < lastPosition + 1; i++) {
			for (int j = 0; j < Math.pow(2, i) && j + Math.pow(2, i) < 10; j++) {
				if (j > max) {
					max = j;
				}
			}

		}

		for (int i = 0; i < lastPosition + 1; i++) {
			for (int j = 0; j < Math.pow(2, i) && j + Math.pow(2, i) < 10; j++) {

				for (int k = 0; (k < max / ((int) Math.pow(2, i))); k++) {
					sb.append(" ");
				}
				sb.append(heap[j + (int) Math.pow(2, i) - 1] + " ");

			}
			sb.append("\n");

		}

		System.out.println(sb.toString());

	}
}
