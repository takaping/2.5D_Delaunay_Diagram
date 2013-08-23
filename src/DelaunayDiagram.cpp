/* 
 * File:   DelaunayDiagram.cpp
 * Author: munehiro
 * 
 * Created on August 17, 2013, 1:44 PM
 */

#include <algorithm>
#include "DelaunayDiagram.h"

/**
 * Constructor and Destructor
 */
DelaunayDiagram::DelaunayDiagram() {
}

DelaunayDiagram::~DelaunayDiagram() {
}

/**
 * Clears lists;
 */
void DelaunayDiagram::clear() {
    ch.clear();
    ea.clear();
    fa.clear();
}

/**
 * Constructs the delaunay diagram
 * @param vertex array
 */
void DelaunayDiagram::construct(const vector<Vector3d>& va) {
    clear();
    // construct the 3d convex hull
    vector<Vector3d> dva;
    for_each(va.begin(), va.end(), [&](Vector3d v) {
        double x = v.x();
        double y = v.y();
        dva.push_back(Vector3d(x, y, -(x * x + y * y) / 2.0));
    });
    ch.construct(dva);
    // construct the 2.5d delaunay edges and faces
    constructDelaunay();
}

/**
 * Constructs 2.5d delaunay edges and faces
 */
void DelaunayDiagram::constructDelaunay() {
    unordered_map<int, ConvexHull::PrimProperty> kep;
    unordered_map<int, ConvexHull::PrimProperty> kfp;

    // entries property of faces
    fa = ch.faces();
    for_each(fa.begin(), fa.end(), [&](int f) {
        if (ch.isFront(f)) {
            kfp[f] = ConvexHull::PrimProperty::UPWARD;
        } else {
            kfp[f] = ConvexHull::PrimProperty::DOWNWARD;
        }
    });
    // entries property of edges
    ea = ch.edges();
    for_each(ea.begin(), ea.end(), [&](int e) {
        int lf = ch.leftFace(e);
        int rf = ch.rightFace(e);
        if ((kfp[lf] == ConvexHull::PrimProperty::DOWNWARD && kfp[rf] == ConvexHull::PrimProperty::UPWARD) ||
            (kfp[lf] == ConvexHull::PrimProperty::UPWARD && kfp[rf] == ConvexHull::PrimProperty::DOWNWARD)) {
            kep[e] = ConvexHull::PrimProperty::CONVEXHULL;
        } else if (kfp[rf] == ConvexHull::PrimProperty::UPWARD) {
            kep[e] = ConvexHull::PrimProperty::DELAUNAY;
        } else {
            kep[e] = ConvexHull::PrimProperty::FARTHESTDELAUNAY;
        }
    });
    // constructs delaunay edges
    vector<int>::iterator e = ea.begin();
    while (e != ea.end()) {
        if (kep[*e] == ConvexHull::PrimProperty::FARTHESTDELAUNAY) {
            e = ea.erase(e);
        } else {
            ++e;
        }
    }
    // constructs delaunay faces
    vector<int>::iterator f = fa.begin();
    while (f != fa.end()) {
        if (kfp[*f] == ConvexHull::PrimProperty::DOWNWARD) {
            f = fa.erase(f);
        } else {
            ++f;
        }
    }
}

