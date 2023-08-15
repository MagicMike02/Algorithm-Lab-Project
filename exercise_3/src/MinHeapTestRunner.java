import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

/**
 * @author Talliente, Roshanaie, Liquindoli
 */

public class MinHeapTestRunner {
	public static void main(String[] args) {
		Result result = JUnitCore.runClasses(MinHeapTests.class);
		for (Failure failure : result.getFailures()) {
			System.out.println(failure.toString());
		}

		System.out.println(result.wasSuccessful());
	}
}
