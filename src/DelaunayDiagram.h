/* 
 * Delaunay diagram class
 *  - instantiates the 3d convex hull object
 *  - constructs the delaunay diagram by using the 3d convex hull
 * File:   DelaunayDiagram.h
 * Author: munehiro
 *
 * Created on August 17, 2013, 1:44 PM
 */

#ifndef DELAUNAYDIAGRAM_H
#define	DELAUNAYDIAGRAM_H

#include <vector>
#include <unordered_map>
#include "ConvexHull.h"
#include "Vector3d.h"

using namespace std;

class DelaunayDiagram {
public:
    DelaunayDiagram();
    virtual ~DelaunayDiagram();
    void clear();
    void construct(const vector<Vector3d>& va);
    // @return delaunay edges
    const vector<int>& edges() const { return ea; };
    // @return delaunay faces
    const vector<int>& faces() const { return fa; };
    // Gets vertices of the edge
    // @param edge
    // @param vertices
    void getVerticesOfEdge(int e, int* kv) { ch.getVerticesOfEdge(e, kv); };
    // Gets vertices of the triangle
    // @param triangle
    // @param vertices
    void getVerticesOfTriangle(int f, int* kv) { ch.getVerticesOfTriangle(f, kv); };
private:
    void constructDelaunay();
    ConvexHull ch;  // 3d convex hull
    vector<int> ea; // delaunay edge array
    vector<int> fa; // delaunay face array

};

#endif	/* DELAUNAYDIAGRAM_H */

