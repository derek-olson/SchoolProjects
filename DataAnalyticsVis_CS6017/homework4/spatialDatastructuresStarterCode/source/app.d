import std.stdio;
import bucket;
import common;
import dumbknn;
import kdtree;
import quadtree;
import std.csv;
import std.file;
import std.stdio;
//import your files here

void main()
{
    auto f = File("output.csv", "w");
    f.writeln("type,","dim,","n,","k,","time");
    //because dim is a "compile time parameter" we have to use "static foreach"
    //to loop through all the dimensions we want to test.
    //the {{ are necessary because this block basically gets copy/pasted with
    //dim filled in with 1, 2, 3, ... 7.  The second set of { lets us reuse
    //variable names.
    for (int i = 0; i < 20; i++)
    {
        for (int k = 1; k < 6; k++)
        {
            for(int j = 1; j < 11; j++)
            {
                static foreach(dim; 1..8)
                {{
                    //get points of the appropriate dimension
                    auto trainingPoints = getGaussianPoints!dim(10000*j);
                    auto testingPoints = getUniformPoints!dim(100);
                    auto kd = DumbKNN!dim(trainingPoints);
                    //writeln("tree of dimension ", dim, " built");
                    StopWatch sw;
                    sw.start;
                    foreach(const ref qp; testingPoints){
                        kd.knnQuery(qp, 10*k);
                    }
                    auto time = sw.peek.total!"usecs";
                    auto outstring = "dumb,%dim,%time\n";
                    //std.file.write("outcsv.csv", outstring);
                    f.writeln("dumb,",dim,",",j*10000,",",k*10,",", sw.peek.total!"usecs"); //output the time elapsed in microseconds
                    //NOTE, I SOMTEIMS GOT TOTALLY BOGUS TIMES WHEN TESTING WITH DMD
                    //WHEN YOU TEST WITH LDC, YOU SHOULD GET ACCURATE TIMING INFO...
                    sw.reset;
                }}
            }
        }
        for (int k = 1; k < 6; k++)
        {
            for(int j = 1; j < 11; j++)
            {
                static foreach(dim; 1..8)
                {{
                    //get points of the appropriate dimension
                    auto trainingPoints = getGaussianPoints!dim(10000*j);
                    auto testingPoints = getUniformPoints!dim(100);
                    auto kd = BucketKnn!dim(trainingPoints);
                    //writeln("tree of dimension ", dim, " built");
                    StopWatch sw;
                    sw.start;
                    foreach(const ref qp; testingPoints){
                        kd.knnquery(qp, 10*k);
                    }
                    auto time = sw.peek.total!"usecs";
                    auto outstring = "bucket,%dim,%time\n";
                    //std.file.write("outcsv.csv", outstring);
                    f.writeln("bucket,",dim,",",j*10000,",",k*10,",", sw.peek.total!"usecs"); //output the time elapsed in microseconds
                    //NOTE, I SOMTEIMS GOT TOTALLY BOGUS TIMES WHEN TESTING WITH DMD
                    //WHEN YOU TEST WITH LDC, YOU SHOULD GET ACCURATE TIMING INFO...
                    sw.reset;
                }}
            }
        }
        for(int a = 1; a < 6; a++)
        {
            for(int b = 1; b < 11; b++)
            {
                static foreach(dim; 1..8)
                {{
                    //get points of the appropriate dimension
                    auto trainingPoints = getGaussianPoints!dim(10000*b);
                    auto testingPoints = getUniformPoints!dim(100);
                    auto kd = kd_tree!dim(trainingPoints);
                    //writeln("tree of dimension ", dim, " built");
                    StopWatch sw;
                    sw.start;
                    foreach(const ref qp; testingPoints){
                        kd.knn_query(qp, 10*a);
                    }
                    auto time = sw.peek.total!"usecs";
                    auto outstring = "kd_tree,%dim,%time\n";
                    //std.file.write("outcsv.csv", outstring);
                    f.writeln("kdtree,",dim,",",b*10000,",",a*10,",", sw.peek.total!"usecs"); //output the time elapsed in microseconds
                    //NOTE, I SOMTEIMS GOT TOTALLY BOGUS TIMES WHEN TESTING WITH DMD
                    //WHEN YOU TEST WITH LDC, YOU SHOULD GET ACCURATE TIMING INFO...
                    sw.reset;
                }}
            }
        }
        for(int c = 1; c < 6; c++)
        {
            for(int d = 1; d < 11; d++)
            {
                static foreach(dim; 2..3)
                {{
                    //get points of the appropriate dimension
                    auto trainingPoints = getGaussianPoints!dim(10000*d);
                    auto testingPoints = getUniformPoints!dim(100);
                    auto kd = quad_tree!dim(trainingPoints);
                    //writeln("tree of dimension ", dim, " built");
                    StopWatch sw;
                    sw.start;
                    foreach(const ref qp; testingPoints){
                        kd.knn_query(qp, 10*c);
                    }
                    auto time = sw.peek.total!"usecs";
                    auto outstring = "quad_tree,%dim,%time\n";
                    //std.file.write("outcsv.csv", outstring);
                    f.writeln("quadtree,",dim,",",d*10000,",",c*10,",", sw.peek.total!"usecs"); //output the time elapsed in microseconds
                    //NOTE, I SOMTEIMS GOT TOTALLY BOGUS TIMES WHEN TESTING WITH DMD
                    //WHEN YOU TEST WITH LDC, YOU SHOULD GET ACCURATE TIMING INFO...
                    sw.reset;
                }}
            }
        }

    }
    
}


