import java.util.LinkedList;
import org.junit.*;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import org.junit.Test;
import static org.junit.Assert.*;

public class GraphTest {
	private Graph<String, Integer> graph;

	@Before
	public void setUp() {
		graph = new Graph<>(false);

		String a = "A";
		String b = "B";
		String c = "C";
		String d = "D";
		String e = "E";

		Edge<String, Integer> ab5 = new Edge<String, Integer>(a, b, 5);
		Edge<String, Integer> bc10 = new Edge<String, Integer>(b, c, 10);
		Edge<String, Integer> ac6 = new Edge<String, Integer>(a, c, 6);
		Edge<String, Integer> de6 = new Edge<String, Integer>(d, e, 6);

		graph.addEdge(ab5);
		graph.addEdge(bc10);
		graph.addEdge(ac6);
		graph.addEdge(de6);
	}

	@Test
	public void testIsOriented() {
		assertFalse(graph.isOriented());
	}

	@Test
	public void testSizeEdges() {
		assertEquals(4, graph.sizeEdges());
	}

	@Test
	public void testSizeVertexes() {
		assertEquals(5, graph.sizeVertexes());
	}

	@Test
	public void testContainsVertexes() {
		assertTrue(graph.containsV(new String("A")));
		assertTrue(graph.containsV(new String("B")));
		assertTrue(graph.containsV(new String("C")));
		assertTrue(graph.containsV(new String("D")));
		assertTrue(graph.containsV(new String("E")));
	}

	@Test
	public void testContainsEdges() {
		Edge<String, Integer> e = new Edge<String, Integer>("A", "B", 5/*graph.getEdgeWeight("A", "B")*/);
		assertTrue(graph.containsE(e));

		assertTrue(graph.containsE(new Edge<String, Integer>(new String("B"), new String("C"), 10)));
		assertTrue(graph.containsE(new Edge<String, Integer>(new String("C"), new String("B"), 10)));
		assertTrue(graph.containsE(new Edge<String, Integer>(new String("E"), new String("D"), 6)));
	}

	@Test
	public void testAddVertex() {
		String toAdd = "F";
		graph.addVertex(toAdd);
		assertTrue(graph.containsV(toAdd));
	}

	@Test
	public void testRemoveVertex() {
		String toRemove = "E";
		graph.removeVertex(toRemove);
		assertFalse(graph.containsV(toRemove));
	}

	@Test
	public void testAddEdge() {
		Integer expected = 1;

		graph.addEdge(new Edge<String, Integer>(new String("A"), new String("D"), 1));

		assertEquals(expected, graph.getEdgeWeight(new String("A"), new String("D")));
		assertEquals(expected, graph.getEdgeWeight(new String("D"), new String("A")));
	}

	@Test
	public void testRemoveEdge() {
		boolean test = graph.removeEdge(new Edge<String, Integer>(new String("D"), new String("E"), 6));
		assertTrue(test);
	}

	@Test
	public void testGetVertices() {
		LinkedList<String> expected = new LinkedList<>();
		expected.add("A");
		expected.add("B");
		expected.add("C");
		expected.add("D");
		expected.add("E");

		LinkedList<String> result = graph.getVertices();
		assertEquals(expected, result);
	}

	@Test
	public void testGetAdjVerticesOf() {
		LinkedList<String> expected = new LinkedList<>();
		expected.add("D");

		LinkedList<String> result = graph.getAdjVerticesOf("E");

		assertEquals(expected, result);
	}

	@Test
	public void testGetEdges() {
		Graph<String, Integer> graphClone = new Graph<>(false);

		//Build a new graph with the same edges and vertex
		String a = "A";
		String b = "B";
		String c = "C";
		String d = "D";
		String e = "E";

		Edge<String, Integer> ab5 = new Edge<String, Integer>(a, b, 5);
		Edge<String, Integer> bc10 = new Edge<String, Integer>(b, c, 10);
		Edge<String, Integer> ac6 = new Edge<String, Integer>(a, c, 6);
		Edge<String, Integer> de6 = new Edge<String, Integer>(d, e, 6);

		graphClone.addEdge(ab5);
		graphClone.addEdge(bc10);
		graphClone.addEdge(ac6);
		graphClone.addEdge(de6);

		LinkedList<Edge<String, Integer>> expected = graphClone.getEdges();
		LinkedList<Edge<String, Integer>> result = graph.getEdges();
		assertEquals(expected, result);
	}

	@Test
	public void testGetEdgeWeight() {
		Integer expected = 5;
		assertEquals(expected, graph.getEdgeWeight(new String("A"), new String("B")));
	}

	public static void main(String[] args) {
		Result result = JUnitCore.runClasses(GraphTest.class);
		for (Failure failure : result.getFailures()) {
			System.out.println(failure.toString());
		}
		System.out.println("\nGraphTests result: " + result.wasSuccessful());
	}

}
