
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

class FileUtils {
	static void GraphCSV(Graph<String, Double> graph, String file) {
		
		try {
			BufferedReader br = new BufferedReader(new FileReader(file));
			String line = br.readLine();
			while (line != null) {
				String[] fields = line.split(",");
				String v1 = fields[0];
				String v2 = fields[1];
				graph.addVertex(v1);
				graph.addVertex(v2);

				Edge<String, Double> e = new Edge<>(v1, v2, Double.parseDouble(fields[2]));
				
				graph.addEdge(e);

				line = br.readLine();
			}
			br.close();
		} catch (IOException e) {
			System.out.println("Error, file not found ...");
		}
	
	
	
	}


}
