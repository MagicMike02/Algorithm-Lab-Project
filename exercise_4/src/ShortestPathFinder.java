
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * Dijkstra shortest path finder: finds the shortest path from a given vertex
 * @author Talliente, Roshanaie, Liquindoli
 * @param <L>: type of minimum heap elements
 */

public class ShortestPathFinder<L extends Comparable<L>> {
	Graph<L, Double> graph;

	private HashMap<L, Double> dist;
	private HashMap<L, L> pi;
	private MinHeap<L> pq;

	/**
	 * Initializes the comparator of minHeap.
	 * It accepts as input a graph
	 * @param graph: an instance of a graph.
	 */
	public ShortestPathFinder(Graph<L, Double> graph) {
		this.graph = graph;

		this.pq = new MinHeap<L>(graph.sizeVertexes(), (L v1, L v2) -> {
			if (dist.get(v1) < dist.get(v2))
				return -1;
			else if (dist.get(v1) > dist.get(v2))
				return 1;
			else {
				return v1.compareTo(v2);
			}
		});
		this.dist = new HashMap<>(graph.sizeVertexes());
		this.pi = new HashMap<>(graph.sizeVertexes());
	}

	/**
	 * Implementation of Dijkstra algorithm.
	 * @param source: The source vertex from which the shortest path is calculated.
	 */
	public void dijkstra(L source) {
		List<L> s = new ArrayList<>();
		L u;

		for (L v : graph.getVertices()) {
			dist.put(v, Double.POSITIVE_INFINITY);
			pi.put(v, null);
		}

		dist.replace(source, 0.0);

		MakePriorityQueue(source);
		while (!pq.isEmpty()) {
			u = pq.extract_min();
			s.add(u);
			for (L v : graph.getAdjVerticesOf(u)) {
				Relax(u, v);

			}
		}
		printSolution(source, dist, pi);
	}

	private void Relax(L u, L v) {
		if (dist.get(v) > dist.get(u) + (Double) graph.getEdgeWeight(u, v)) {
			dist.replace(v, dist.get(u) + (Double) graph.getEdgeWeight(u, v));
			pi.replace(v, u); // set the parent of v equal to u.
			try {
				pq.decrease_element(pq.indexOf(v), v);
			} catch (MinHeapException e) {
				System.out.println(e);

			}
		}
	}

	private void MakePriorityQueue(L source) {
		//        pq.insert(source);
		boolean foundSource = false;
		for (L v : graph.getVertices()) {
			if (!foundSource && v.equals(source)) {
				pq.insert(v);
				foundSource = true;
			} else {
				pq.insert(v);
			}
		}
		//System.out.println(pq); print heap after insert all elements
	}

	private void printSolution(L source, HashMap<L, Double> dist,
							   HashMap<L, L> pi) {
		System.out.print("Vertex\t Distance\tPath");

		// ArrayList<Vertex<L>> keySet =(ArrayList<Vertex<L>>)new ArrayList<Vertex<L>>dist.keySet();

		for (L v : dist.keySet()) {
			if (!(v.equals(source))) {
				System.out.print("\n" + source + " -> ");
				System.out.print(v + " \t\t ");
				System.out.print(dist.get(v) / 1000 + "\t\t");
				if (v.equals("catania"))
					printPath(v, pi);
				//System.out.println("\n#########################################");
			}
		}
	}

	// Function to print shortest path
	// from source to currentVertex
	// using parents array
	private void printPath(L currentVertex, HashMap<L, L> parents) {

		// Base case : Source node has
		// been processed
		if (parents.get(currentVertex) == null) {
			return;
		}
		printPath(parents.get(currentVertex), parents);

		System.out.print(currentVertex + " ");

	}

	private Graph<L, Double> createGraph() {
		Graph<L, Double> minGraph = new Graph<L, Double>(true);
		for (L v : pi.keySet()) {
			if (pi.get(v) != null && v != null) {
				Edge<L, Double> e = new Edge<L, Double>(pi.get(v), v, graph.getEdgeWeight(pi.get(v), v));
				minGraph.addEdge(e);
			}
		}

		return minGraph;

	}

}