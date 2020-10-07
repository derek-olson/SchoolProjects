import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;


public class Router {
    private HashMap<Router, Integer> distances;
    private String name;
    public Router(String name) {
        this.distances = new HashMap<>();
        this.name = name;
    }

    public void onInit() throws InterruptedException {

        HashSet<Neighbor> neighbors = Network.getNeighbors(this);
        for(Neighbor n : neighbors){
            distances.put(n.router, n.cost);
        }

        for(Neighbor n : neighbors) {
            Message message = new Message(this, n.router, distances);
            Network.sendDistanceMessage(message);
        }
    }

    public void onDistanceMessage(Message message) throws InterruptedException {
        //update your distance table and broadcast it to your neighbors if it changed
        boolean change = false;
        //handle if router table doesn't contain the router
        for(Router r : message.distances.keySet()){
            if(r.equals(this)){
                //distances.put(r, 0);
                continue;
            }
            else if(!distances.containsKey(r)){
                //get the distance between the router and the message sender
                int sendDist = distances.get(message.sender);
                //add the distance between the router and the message sender to the distance of new neighbor
                distances.put(r, message.distances.get(r) + sendDist);
                change = true;
            }
            //handle if router is present but distances are different
            //Check if the sum of the distances between the router, message sender, and neighbors is less than
            //the distance between router and neighbors. If true than update the distance with the sum.
            else if(distances.get(message.sender) + message.distances.get(r) < distances.get(r)) {
                distances.put(r, distances.get(message.sender) + message.distances.get(r));
                change = true;
            }
            else{
                continue;
            }
        }

        if(change == true) {
            for (Neighbor n : Network.getNeighbors(this)) {
                Message m = new Message(this, n.router, distances);
                Network.sendDistanceMessage(m);
            }
        }
    }

    public void dumpDistanceTable() {
        System.out.println("router: " + this);
        for(Router r : distances.keySet()){
            System.out.println("\t" + r + "\t" + distances.get(r));
        }
    }

    @Override
    public String toString(){
        return "Router: " + name;
    }
}
