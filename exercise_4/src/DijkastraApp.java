public class DijkastraApp {

// javac .\DijkastraApp.java 
// java DijkastraApp "src/italian_dist_graph.csv"

	public static void main(String[] args) {
		Graph<String, Double> Graph = new Graph<String, Double>(false);

		FileUtils.GraphCSV(Graph, "../italian_dist_graph.csv");
		ShortestPathFinder<String> shortPath = new ShortestPathFinder<String>(Graph);
		shortPath.dijkstra(new String("torino"));
		System.out.println();

	}
}