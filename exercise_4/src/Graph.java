import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.NoSuchElementException;

/**
 * Graph data structure. Can ba oriented or not.
 * @author Talliente, Roshanaie, Liquindoli
 * @param <L>: Lable of the vertices
 * @param <E>: Weight of the graph edges
 */
public class Graph<L extends Comparable<L>,E extends Comparable<E>> {
	private final Map<L, LinkedList<Edge<L, E>>> adjList;
	private final boolean isOriented;


	/**
	 * Graph constructor. Initializes the class fields.
	 * @param isOriented: Boolean value to indicated if the graph is oriented or not.
	 */
	public Graph(boolean isOriented) {
		this.adjList = new HashMap<>();
		this.isOriented = isOriented;
	}


	/**
	 * @return returns the array represented by adjacent list.
	 */
	public Map<L, LinkedList<Edge<L,E>>> getAdjList() {
		return adjList;
	}

	/**
	 * @return true if the graph is oriented, false otherwise
	 */
	public boolean isOriented() {
		return isOriented;
	}

	/**
	 *  @Return the number of the vertexes which is equal to size of the hashmap
	 *  **/
	public int sizeVertexes(){
		return adjList.size();
	}

	/** Returns the number of the edges **/
	public int sizeEdges(){
		int size = 0;
		for (L v : adjList.keySet()) // adjList.keySet() returns a set of all the keys in the hash map. So we are saying for each vertex ...
			size += adjList.get(v).size(); // adjList.get(v) returns a linkedList associated to each vertex v
		if(this.isOriented)
			return size;
		else
			return size/2;
	}

	/** Checks if the Vertex v is contained in the Graph */
	public boolean containsV(L v) {
		return adjList.containsKey(v);
	}

	//Checks if the Edge is contained in the Graph
	public boolean containsE(Edge<L,E> e) {
		return adjList.get(e.getVertex1()).contains(e); // adjList.get(e.getVertex1()) returns a list of adj vertexes of Vertex1 -> its arcs
	}

	/**
	 * Adds the Vertex v in the Graph.
	 * @param v new vertex to add to the graph
	 */
	public void addVertex(L v) {
		if (!adjList.containsKey(v))
			adjList.put(v, new LinkedList<>());
	}

	/**
	 * Removes the Vertex v and all the edges connected to it from the adjList.
	 * @param v the vertex to be removed
	 */
	public void removeVertex(L v) {
		try{
			while(adjList.get(v).removeFirst() != null) // While there is a vertex in the adj list of the vertex v, remove the first element of the list
				adjList.get(v).removeFirst();
		} catch(NoSuchElementException e) {
			/* this exception is thrown by removeFirst() method in LinkedList,
			 * when it occurs, we know that the LinkedList is empty, because the
			 * first element is null. If the LinkedList is null, then we can remove
			 * the vertex v (key) itself from the List.
			 */
			adjList.remove(v);
		}
	}

	/**
	 * Adds Edge in the Graph.
	 * @param e new edge to add to the graph
	 */
	public void addEdge(Edge<L,E> e) {
		if (isOriented) {
			addEdgeOriented(e);
		}
		else {
			Edge<L,E> eReverse = new Edge<L,E>(e.getVertex2(), e.getVertex1(), e.getWeight());
			addEdgeOriented(e);
			addEdgeOriented(eReverse);
		}
	}

	private void addEdgeOriented(Edge<L,E> e) {
		// first we check if both of the vertices of the edge
		// are already inside the adjList, if not, then we add them.
		adjList.putIfAbsent(e.getVertex1(), new LinkedList<>());
		adjList.putIfAbsent(e.getVertex2(), new LinkedList<>());
		adjList.get(e.getVertex1()).add(e);  // get(e.getVertex1()) returns the list of v1's edges
	}

	/**
	 * Removes an edge from the Graph
	 * @param e removes the given edge
	 * @return returns true if the elimination is finished successfully
	 */
	public boolean removeEdge(Edge<L,E> e) {
		if (this.isOriented) {
			LinkedList<Edge<L,E>> edges = adjList.get(e.getVertex1());
			return edges.remove(e);
		} else {
			LinkedList<Edge<L,E>> edgesV1 = adjList.get(e.getVertex1());
			LinkedList<Edge<L,E>> edgesV2 = adjList.get(e.getVertex2());
			Edge<L,E> eReverse = new Edge<L,E>(e.getVertex2(), e.getVertex1(), e.getWeight());
			return edgesV1.remove(e) && edgesV2.remove(eReverse);
		}
	}

	/**
	 * @return It returns a LinkedList<T> which contains all the vertex of the Graph.
	 */
	public LinkedList<L> getVertices() {
		return new LinkedList<>(adjList.keySet());
	}

	/**
	 *
	 * @param v Gets adjacent vertices of the v.
	 * @return linked list that contains adjacent vertices of v.
	 */
	public LinkedList<L> getAdjVerticesOf(L v) {
		LinkedList<L> res = new LinkedList<>();
		for (Edge<L,E> e: adjList.get(v)) {
			res.add(e.getVertex2());
		}
		return res;
	}

	/**
	 * @return It returns a LinkedList<T> which contains all the edges of the Graph.
	 */
	public LinkedList<Edge<L,E>> getEdges() {
		LinkedList<Edge<L,E>> res = new LinkedList<>();
		for (L v : adjList.keySet()) {
			res.addAll(adjList.get(v));
		}
		return res;
	}

	/**
	 * @param v1 starting vertex
	 * @param v2 end vertex
	 * @return weight of the edge (v1, v2)
	 */
	public E getEdgeWeight(L v1, L v2)  {
		LinkedList<Edge<L,E>> res = adjList.get(v1);
		for (Edge<L,E> e : res)
			if (e.getVertex1().equals(v1) && e.getVertex2().equals(v2))
				return e.getWeight();
		return null;
	}

	@Override
	public String toString() {
		StringBuilder s = new StringBuilder();
		for (L v : adjList.keySet()) {
			for (Edge<L,E> e: adjList.get(v)) {
				s.append("From vertex ").
						append(e.getVertex1()).append(" to vertex ").
						append(e.getVertex2()).append(". Weight: ").
						append(e.getWeight()).append("\n");
			}
		}
		return s.toString();
	}

	public static void main(String[] args) {
		Graph<String, Double> Graph = new Graph<String, Double>(true);

//		 Create 5 Vertexs
		String a = "A";
		String b = "B";
		String c = "C";
		String d = "D";
		String e = "E";

		//Create 4 edges
		Edge<String, Double> ab5 = new Edge<String, Double>(a, b, 5.0);
		Edge<String, Double> bc10 = new Edge<String, Double>(b, c, 10.5);
		Edge<String, Double> ac6 = new Edge<String, Double>(a, c, 6.1);
		Edge<String, Double> de6 = new Edge<String, Double>(d, e, 6.1);
		Edge<String, Double> ce6 = new Edge<String, Double>(c, e, 6.1);

		//add all the vertex in the graph
		Graph.addVertex(a);
		Graph.addVertex(b);
		Graph.addVertex(c);
		Graph.addVertex(d);
		Graph.addVertex(e);

		//add all the edges in the graph
		Graph.addEdge(ab5);
		Graph.addEdge(bc10);
		Graph.addEdge(ac6);
		Graph.addEdge(de6);
		Graph.addEdge(ce6);

		System.out.println(Graph);
	}




}
