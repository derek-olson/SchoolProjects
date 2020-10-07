import java.util.HashMap;

public class Main {
    public static void main(String[] args) throws InterruptedException {

        for (int i = 2; i < 2002; i += 100) {
            Network.makeProbablisticNetwork(i);
            Network.startup();
            Network.runBellmanFord();
            System.out.println(i + "\t" + Network.getMessageCount());
        }


        //Network.makeSimpleNetwork(); //use this for testing/debugging
//        Network.makeProbablisticNetwork(5); //use this for the plotting part
//        Network.dump();
//
//        Network.startup();
//        Network.runBellmanFord();
//
//        System.out.println("done building tables!");
//        for(Router r : Network.getRouters()){
//            r.dumpDistanceTable();
//        }
//        System.out.println("total messages: " + Network.getMessageCount());

    }

}
