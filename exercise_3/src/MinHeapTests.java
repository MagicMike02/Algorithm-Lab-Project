import org.junit.Before;
import org.junit.Test;
import java.util.Comparator;
import static org.junit.Assert.*;

/**
 * @author Talliente, Roshanaie, Liquindoli
 */

public class MinHeapTests {
	public class IntComparator implements Comparator<Integer> {
		@Override
		public int compare(Integer o1, Integer o2) {
			return o1.compareTo(o2);
		}
	}

	private Integer i1, i2, i3;
	private MinHeap<Integer> heap;

	@Before
	public void createMinHeap() throws MinHeapException {
		i1 = -12;
		i2 = 0;
		i3 = 4;

		heap = new MinHeap<>(3, new IntComparator());
	}

	@Test
	public void testIsEmpty_zeroEl() {
		assertTrue(heap.isEmpty());
		assertEquals(0, heap.size());
	}

	@Test
	public void testSize_oneEl() throws MinHeapException {
		heap.insert(i1);
		assertEquals(1, heap.size());
	}

	@Test
	public void testSize_twoEl() throws MinHeapException {
		heap.insert(i1);
		heap.insert(i2);
		assertEquals(2, heap.size());
	}

	@Test
	public void testSize_threeEl() throws MinHeapException {
		heap.insert(i1);
		heap.insert(i2);
		heap.insert(i3);
		assertEquals(3, heap.size());
	}

	@Test
	public void testGet_oneEl() throws MinHeapException {
		heap.insert(i1);
		assertSame(i1, heap.getElem(0));
	}

	@Test
	public void testAdd_threeEl_1() throws MinHeapException {
		Integer[] arrExpected = { i1, i2, i3 };
		heap.insert(i1);
		heap.insert(i2);
		heap.insert(i3);

		assertArrayEquals(arrExpected, heap.heap);
	}

	@Test
	public void testAdd_threeEl_2() throws MinHeapException {
		Integer[] arrExpected = { i1, i2, i3 };
		heap.insert(i2);
		heap.insert(i1);
		heap.insert(i3);

		assertArrayEquals(arrExpected, heap.heap);
	}

	@Test
	public void testGetLeft() throws MinHeapException {
		heap.insert(i1);
		heap.insert(i2);
		heap.insert(i3);

		assertEquals(i2, heap.get_left(0));
	}

	@Test
	public void testGetRight() throws MinHeapException {
		heap.insert(i1);
		heap.insert(i2);
		heap.insert(i3);

		assertEquals(i3, heap.get_right(0));
	}

	@Test
	public void testGetParent() throws MinHeapException {
		heap.insert(i1);
		heap.insert(i2);
		heap.insert(i3);

		assertEquals(i1, heap.get_parent(2));
	}

	@Test
	public void test_extractMin() throws MinHeapException {
		heap.insert(i1);
		heap.insert(i2);
		heap.insert(i3);

		assertEquals(i1, heap.extract_min()); // extract min -> heapify
		assertEquals(i2, heap.getElem(0)); // check if trickle_down works
	}

	@Test
	public void test_decreaseKey() throws MinHeapException {
		Integer newKey = -99;

		heap.insert(i1);
		heap.insert(i2);
		heap.insert(i3);

		heap.decrease_element(2, newKey); // decrease key of the elem "i3" -> trickle_up

		assertEquals(newKey, (Integer) heap.getElem(0)); // check if the key has been changed and if trickle_up wortked
	}

	@Test
	public void test_grewSize() throws MinHeapException {
		heap.insert(i1);
		heap.insert(i2);
		heap.insert(i3);

		Integer i4 = 99;
		Integer i5 = -99;

		heap.insert(i4);
		heap.insert(i5);

		// check if lastposition is 
		assertEquals(5, heap.size());
	}

	@Test
	public void test_indexof() throws MinHeapException {
		heap.insert(i1);
		heap.insert(i2);
		heap.insert(i3);

		assertEquals(1, heap.indexOf(i2));
	}
}
