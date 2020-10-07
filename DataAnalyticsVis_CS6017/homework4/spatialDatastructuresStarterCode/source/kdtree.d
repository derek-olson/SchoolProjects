module kdtree;
import std.conv;
import common;

struct kd_tree(size_t Dim)
{
    node!0 root;
    alias PT = Point!Dim;

    class node(size_t level)
    {
        int split_level;
        PT split_point;
        node!((level+1) % Dim) left;
        node!((level+1) % Dim) right;

        this(PT[] points)
        {
            split_level = level;
            medianByDimension!level(points);
            if(points.length < 2)
            {
                split_point = points[0];
                left = null;
                right = null;
            }
            else if(points.length == 2)
            {
                split_point = points[1];
                left = new node!((level+1)%Dim)(points[0 .. points.length/2]);
                right = null;
            }
            else
            {
                auto middle = points.length/2;
                split_point = points[middle];
                left = new node!((level+1)%Dim)(points[0 .. middle]);
                right = new node!((level+1)%Dim)(points[middle + 1 .. $]);
            }
            
        }
    }

    this(PT[] points)
    {
        root = new node!0(points);
    }

    PT[] range_query(PT p, float r)
    {
        PT[] out_points;
        recursive_range!0(this.root, p, r, out_points);
        return out_points;
    }

    void recursive_range(size_t level)(node!level n , PT p, float radius, ref PT[] out_points)
    {
        if(distance(n.split_point, p) < radius)
        {
            out_points ~= n.split_point;
        }
        if(p[n.split_level] - radius <= n.split_point[n.split_level])
        {
             if(n.left !is null)
            {
                recursive_range!((level+1) % Dim)(n.left, p, radius, out_points);
            }
            
        }
        if(p[n.split_level] + radius >= n.split_point[n.split_level])
        {
            if(n.right !is null)
            {
                recursive_range!((level+1) % Dim)(n.right, p, radius, out_points);
            }
            
        }
    }

    PT[] knn_query(PT p, int k)
    {
        auto toReturn = makePriorityQueue!Dim(p);
        Point!Dim max_infinity;
        Point!Dim min_infinity;

        for (int i = 0; i < Dim; i++){
            max_infinity[i] = float.infinity;
            min_infinity[i] = -float.infinity;
        }
        PT[] array = [max_infinity, min_infinity];
        auto box = boundingBox!Dim(array);
        void knn_recursive(size_t level)(node!level n, AABB!Dim bb)
        {
            if(toReturn. length < k)
            {
                toReturn.insert(n.split_point);
            }
            else
            {
                if(distance(n.split_point, p) < distance(toReturn.front, p))
                {
                    toReturn.popFront;
                    toReturn.insert(n.split_point);
                }
            }
            if(n.left !is null)
            {
                auto left_child_box = bb;
                left_child_box.max[level] = n.split_point[level];
                auto left_closest = closest!Dim(left_child_box, p);
                if(toReturn.length < k || distance(left_closest, p) < distance(toReturn.front, p))
                {
                    knn_recursive(n.left, left_child_box);
                }
            }
            if(n.right !is null)
            {
                auto right_child_box = bb;
                right_child_box.min[level] = n.split_point[level];
                auto right_closest = closest!Dim(right_child_box, p);
                if(toReturn.length < k || distance(right_closest, p) < distance(toReturn.front, p))
                {
                    knn_recursive(n.right, right_child_box);
                }
            }

        }
        knn_recursive!0(this.root, box);
        return toReturn.release;
    }

    void print_tree(size_t level)(node!level n)
    {
        writeln(n.split_point);
        if(n.left !is null)
        {
            print_tree!((level + 1) % Dim)(n.left);
        }
        if(n.right !is null)
        {
            print_tree!((level + 1) % Dim)(n.right);
        }
    }

}

unittest{
    writeln();
    writeln("test kdtree linear diagonal line");
    auto points = [Point!2([0,0]),
                    Point!2([1,1]),
                    Point!2([2,2]),
                    Point!2([3,3]),
                    Point!2([4,4]),
                    Point!2([5,5]),
                    Point!2([6,6]),
                    Point!2([7,7]),
                    Point!2([8,8]),
                    Point!2([9,9]),
                    Point!2([10,10])];
    auto kd = kd_tree!2(points);
    writeln("tree: ", kd);
    writeln("root: ", kd.root.split_point);
    writeln("first level: ", kd.root.left.split_point, kd.root.right.split_point);
    auto range = kd.range_query(Point!2([3,3]), 4.0);
    writeln("Range .....",range);
    auto knn = kd.knn_query(Point!2([5.2,5.2]), 3);
    writeln("knn .....", knn);
}