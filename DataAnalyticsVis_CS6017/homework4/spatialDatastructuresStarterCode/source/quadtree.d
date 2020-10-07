module quadtree;

import common;
import std.conv;

struct quad_tree(size_t Dim)
{
    alias PT = Point!2;
    node root;

    class node
    {
        bool leaf;
        PT[] bucket;
        node ne, nw, se, sw;
        AABB!Dim aabb;

        this(PT[] array, AABB!Dim box)
        {
            aabb = box;
            if(array.length < 2)
            {
                leaf = true;
                bucket = array;
                ne, nw, se, sw = null;
            }
            else
            {
                float x = (box.min[0] + box.max[0]) / 2;
                float y = (box.min[1] + box.max[1]) / 2;

                auto right_half_x = array.partitionByDimension!0(x);
                auto left_half_x = array[0 .. $ - right_half_x.length];


                auto ne_points = right_half_x.partitionByDimension!1(y);
                auto se_points = right_half_x[0 .. $ - ne_points.length];

                auto nw_points = left_half_x.partitionByDimension!1(y);
                auto sw_points = left_half_x[0 .. $ - nw_points.length];

                ne = new node(ne_points, boundingBox([PT([x, y]), box.max]));
                nw = new node(nw_points, boundingBox([PT([box.min[0], y]), PT([x, box.max[1]])]));
                se = new node(se_points, boundingBox([PT([x, box.min[1]]), PT([box.max[0], y])]));
                sw = new node(sw_points, boundingBox([PT(box.min), PT([x, y])]));

                bucket = null;
            }
        }
    }
    this(PT[] points)
    {
        root = new node(points, boundingBox(points));
    }

    PT[] range_query(PT point, float r)
    {
        PT[] to_return;
        void range_recursive(node n)
        {
            if(n.leaf)
            {
                foreach(p; n.bucket)
                {
                    if(distance(p, point) < r)
                    {
                        to_return ~= p;
                    }
                }
            }
            else
            {
                if(distance(closest(n.nw.aabb, point), point) <= r)
                {
                    range_recursive(n.nw);
                }
                if(distance(closest(n.ne.aabb, point), point) <= r)
                {
                    range_recursive(n.ne);
                }
                if(distance(closest(n.se.aabb, point), point) <= r)
                {
                    range_recursive(n.se);
                }
                if(distance(closest(n.sw.aabb, point), point) <= r)
                {
                    range_recursive(n.sw);
                }
            }
        }
        range_recursive(root);
        return to_return;
    }

    PT [] knn_query(PT point, int k)
    {
        auto to_return = makePriorityQueue(point);
        void knn_recursive(node n)
        {
            if(n.leaf)
            {
                foreach(p; n.bucket)
                {
                    if(to_return.length < k)
                    {
                        to_return.insert(p);
                    }
                    else
                    {
                        if(distance(p, point) < distance(to_return.front, point))
                        {
                            to_return.popFront;
                            to_return.insert(p);
                        }
                    }
                }

            }
            else
            {
                if(to_return.length < k || distance(closest(n.nw.aabb, point), point) < distance(to_return.front, point))
                {
                    knn_recursive(n.nw);
                }
                   if(to_return.length < k || distance(closest(n.ne.aabb, point), point) < distance(to_return.front, point))
                {
                    knn_recursive(n.ne);
                }
                if(to_return.length < k || distance(closest(n.se.aabb, point), point) < distance(to_return.front, point))
                {
                    knn_recursive(n.se);
                }
                if(to_return.length < k || distance(closest(n.sw.aabb, point), point) < distance(to_return.front, point))
                {
                    knn_recursive(n.sw);
                }
            }
        } 
        knn_recursive(root);
        return to_return.release;
    }
}

unittest
{
    auto points = [Point!2([0, 0]), Point!2([1, 1]),
                Point!2([2, 2]), Point!2([3, 3]),
                Point!2([4, 4]), Point!2([5, 5]),
                Point!2([6, 6]), Point!2([7, 7]),
                Point!2([8, 8]), Point!2([9, 9]),
                Point!2([10, 10])  ];
    writeln("********Quad Tree Constructor**********");
    auto quad = new quad_tree!2(points);
    writeln("NE = ", quad.root.ne.aabb, " Leaf? -- ", quad.root.ne.leaf);
    writeln("SE = ", quad.root.se.aabb, " Leaf? -- ", quad.root.se.leaf);
    writeln("NW = ", quad.root.nw.aabb, " Leaf? -- ", quad.root.nw.leaf);
    writeln("SW = ", quad.root.sw.aabb, " Leaf? -- ", quad.root.sw.leaf);

    auto neighbors = quad.knn_query(Point!2([5.2, 5.2]), 6);
    writeln("neighbors", neighbors);
}