module bucket;
import std.conv;
import common;
import std.algorithm.searching : canFind;
import std.range;
import std.typecons : tuple;

struct BucketKnn(size_t Dim)
{
    alias PT = Point!Dim;
    alias Bucket = Point!Dim[];
    private Bucket[] buckets;
    private int splits;
    private PT min_corner;
    private PT cell_size;

    this(PT[] points)
    {
        this.splits = to!int(pow(to!float(points.length),0.5/Dim));
        auto aabb = boundingBox(points);
        this.min_corner = aabb.min;
        this.cell_size = (aabb.max - aabb.min)/splits;
        //writeln(this.splits);
        buckets = new Bucket[pow(splits, Dim)];
        foreach(p; points){
            int index = getBucketIndex(getBucketCoords(p));
            buckets[index] ~= p;
        }
    }


    Indices!Dim getBucketCoords(PT point)
    {
        Indices!Dim coordinates;

        for (int i = 0; i < Dim; i++)
        {
            coordinates[i] = clamp(to!int((point[i]-min_corner[i])/cell_size[i]), 0, splits-1);
        }

        return coordinates;
    }

    int getBucketIndex(Indices!Dim coordinates)
    {
        int index = 0;
        for(int i = 0; i < Dim; i++)
        {
            index += to!int(coordinates[i] * pow(splits, (Dim-i)-1));
        }
        return index;
    }

    Bucket rangeQuery(PT p, float radius){
        Bucket ret;
        Point!Dim min_search_area;
        Point!Dim max_search_area;

        for(int i = 0; i < Dim; i++)
        {
            min_search_area[i] = clamp((p[i] - radius), min_corner[i], p[i]);
            max_search_area[i] = clamp((p[i] + radius),p[i], (min_corner[i]+(cell_size[i]*splits)));
        }

        //min_search_area = p - radius;
        //max_search_area = p + radius;
        auto min_bucket = getBucketCoords(min_search_area);
        auto max_bucket = getBucketCoords(max_search_area);

        auto cart = getIndicesRange(min_bucket, max_bucket);
        foreach (c; cart)
        {
            foreach (point; buckets[getBucketIndex(c)])
            {
                if(distance(point, p) < radius){
                    ret ~= point;
                }
            }
        }
        return ret;
    }

    Bucket knnquery(PT p, int k){
        float r = 0;
        foreach (i; 0 .. Dim)
        {
            r += cell_size[i];
        }
        r = r/Dim;
        auto range = rangeQuery(p, r);
        while(range.length < k){
            r *= 1.5;
            range = rangeQuery(p, r);
        }
        topNByDistance(range, p, k);
        return range[0 .. k];
    }


}
unittest{
    writeln("this is a test");
    //I'd include unitttesting code for each of your data structures to test with
    //use a small # of points and manually check that you get the answers you expect
    auto points = [Point!2([.5, .5]), Point!2([1, 1]),
                   Point!2([0.75, 0.4]), Point!2([0.4, 0.74])];
    //since the points are 2D, the data structure is a DumbKNN!2
    auto bucket = BucketKnn!2(points);

    //auto points = [Point!2([0,0])],


/+     writeln("dumbknn rq");
    foreach(p; bucket.rangeQuery(Point!2([1,1]), .7)){
        writeln(p);
    }

    writeln("dumb knn");
    foreach(p; bucket.knnQuery(Point!2([1,1]), 3)){
        writeln(p);
    } +/

}