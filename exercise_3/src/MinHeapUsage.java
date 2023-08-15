import java.io.IOException;


public class MinHeapUsage {

    private static void printIntHeap(MinHeap heap){
        int currElem;
        for (int i=0; i<=heap.lastPosition; i++){
            currElem =(int) heap.getElem(i);
            System.out.println("Element at index " + i + ": " + currElem);
        }
    }

    static int PowerOf2(int power)
    {
        return (1<<power);
    }

//    static void PrintTreeArray(MinHeap heap, int arrayLength)
//    {
//        int currentLevel = 0;
//        int maxPerLevel = PowerOf2(currentLevel);
//        for(int i = 0; i < arrayLength; i++)
//        {
//            if(i == maxPerLevel-1)
//            {
//                System.out.println("\n");
//                currentLevel++;
//                maxPerLevel = PowerOf2(currentLevel);
//            }
//            System.out.print(" "+heap.getElem(i));
//        }
//    }

    private static void printStrHeap(MinHeap heap){
        String currElem;
        for (int i=0; i<=heap.lastPosition; i++){
            currElem =(String) heap.getElem(i);
            System.out.println("Element at index " + i + ": " + currElem);
        }
    }




    public static void main(String[] args) throws MinHeapException {
        int[] numbers = {10, 15, 12, 2, 8, 11, 25};
        String[] names = {"Zara", "Stefano", "Davide", "Michele", "Mara"};

//        MinHeap intHeap = new MinHeap(new IntComparator());
//        for (int i = 0;  i<7; i++){
//            intHeap.insert(numbers[i]);
//        }
//        printIntHeap(intHeap);

        MinHeap strHeap = new MinHeap(5, new StrComparator());
        for (int i = 0;  i<5; i++){
            strHeap.insert(names[i]);
        }
        printStrHeap(strHeap);
        System.out.println("======== Decrese an element ==========");
        strHeap.decrease_element(1, "Ara");
        printStrHeap(strHeap);
//        PrintTreeArray(strHeap, strHeap.lastPosition);





    }
}
