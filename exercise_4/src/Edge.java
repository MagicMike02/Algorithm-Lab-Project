
import java.util.*;

/**
 * Edge class used in Graph.
 * @author Talliente, Roshanaie, Liquindoli
 * @param <T>: Lable of the vertices
 * @param <K>: Weight of the graph edges
 */

public class Edge<T extends Comparable<T>, K extends Comparable<K>> implements Comparable<Edge<T, K>> {
	private T vertex1, vertex2;
	private K weight;

	/**
	 *  Edge constructor.
	 * @param v1 The starting vertex of the edge.
	 * @param v2 The end vertex of the edge.
	 * @param weight The weight of the new edge.
	 */
	public Edge(T v1, T v2, K weight) {
		vertex1 = v1;
		vertex2 = v2;
		this.weight = weight;
	}

	/**
	 * @return The starting vertex of the edge.
	 */
	public T getVertex1() {
		return vertex1;
	}

	/**
	 * @return The end vertex of the edge.
	 */
	public T getVertex2() {
		return vertex2;
	}

	/**
	 * @return The weight of the edge.
	 */
	public K getWeight() {
		return weight;
	}

	/**
	 * Compares the weight of this with the weight of the given edge.
 	 * @param other The edge which is being compared with this
	 * @return	A positive integer if this.weight is larged, 0 if its equal to the other edge's weight, a negetive number if it is smaller.
	 */
	public int compareTo(Edge<T, K> other) {
		return this.weight.compareTo(other.getWeight());
	}

	/**
	 * Checkes if this is equal to the given edge.
	 * @param obj An edge instance
	 * @return True if the two edges ore the same object.
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof Edge))
			return false;
		Edge<T,K> _obj = (Edge<T,K>) obj;
		return _obj.vertex1.equals(vertex1) && _obj.vertex2.equals(vertex2) && _obj.weight == weight;
	}

	@Override
	public String toString() {

		StringBuilder s = new StringBuilder();
		s.append("from vertex ").append(this.getVertex1()).append(" to vertex ").append(this.getVertex2())
				.append(" weight ").append(this.getWeight()).append("\n");
		return s.toString();
	}

	@Override
	public int hashCode() {
	 int hash = 28;
	 hash = 5 * hash + Objects.hashCode(vertex1);
	 hash = 5 * hash + Objects.hashCode(vertex2);
	 hash = 5 * hash + Objects.hashCode(this.weight);
	 return hash;
	}
}