/* 
 * File:   GraphicsModel.cpp
 * Author: munehiro
 * 
 * Created on August 3, 2013, 7:20 PM
 */

#include <ctime>
#include <random>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include "GraphicsModel.h"

/**
 * Constructor and Destructor
 */
GraphicsModel::GraphicsModel() {
}

GraphicsModel::~GraphicsModel() {
}

/**
 * Clears lists
 */
void GraphicsModel::clear() {
    va.clear();
    ea.clear();
    fa.clear();
    dd.clear();
}

/**
 * Generates vertices
 * @param number of vertices
 */
void GraphicsModel::generate(int nv) {
    clear();
    srand(time(nullptr));
    double pi = 4.0 * atan(1.0);
    // generates the vertex array in random order
    // (or loads the vertex array from the file)
    for (int i = 0; i < nv; i++) {
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double s = sqrt(x * x + y * y) * pi * 7.0;
        double z = (s != 0.0 ? sin(s) / s : 1.0);
        va.push_back(Vector3d(x, y, z));
    }
    /********************************
     *  must sort vertices in x order
     ********************************/
    sort(va.begin(), va.end(), Vector3d::lessX);
    // notifies observers
    notifyObservers();
}

/**
 * Constructs the delaunay diagram
 */
void GraphicsModel::construct() {
    // constructs the delaunay diagram
    dd.construct(va);
    // updates the edge and the face array
//    updateEdges();
    updateFaces();
    // notifies observers
    notifyObservers();
}

/**
 * Updates the edge array
 */
void GraphicsModel::updateEdges() {
    vector<int> ke = dd.edges();
    ea.clear();
    for_each(ke.begin(), ke.end(), [&](int k) {
        int kv[2];
        dd.getVerticesOfEdge(k, kv);
        Edge e(k, va[kv[0]], va[kv[1]]);
        if (e.isValid()) {
            ea.push_back(e);
        }
    });
}

/**
 * Updates the face array
 */
void GraphicsModel::updateFaces() {
    vector<int> kf = dd.faces();
    fa.clear();
    for_each(kf.begin(), kf.end(), [&](int k) {
        int kv[3];
        dd.getVerticesOfTriangle(k, kv);
        Face f(k, va[kv[0]], va[kv[1]], va[kv[2]]);
        if (f.isValid()) {
            fa.push_back(f);
        }
    });
}

