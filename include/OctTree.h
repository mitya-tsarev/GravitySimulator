#ifndef GRAVITYSIMULATOR_OCTTREE_H
#define GRAVITYSIMULATOR_OCTTREE_H

#include <vector>
#include "vector.h"
#include "Body.h"

class OctTree {

private:

    class Node {
    public:
        mathing::Vec4 pos;
        double size;
        mathing::Vec4 pos_m;
        double sum_mass; // = 0d
        Node *TNW = nullptr;
        Node *TNE = nullptr;
        Node *TSE = nullptr;
        Node *TSW = nullptr;
        Node *BNW = nullptr;
        Node *BNE = nullptr;
        Node *BSE = nullptr;
        Node *BSW = nullptr;

        double getX();
        double getY();
        double getZ();

        double getSize();

        double getXm();
        double getYm();
        double getZm();

        double getSumMass();

        Node(const mathing::Vec4 &pos, double size, const mathing::Vec4 &posM, double sumMass);
        static Node *
        createOrInsert(Node *n, const mathing::Vec4 &posit, double h, const mathing::Vec4 &posit_m, double m);
        bool isLeaf();
        mathing::Vec4 get_accel(const mathing::Vec4 &position);
        void insertInternal(const mathing::Vec4 &posit_m, double m);
        Node *insert(const mathing::Vec4 &posit_m, double m);
        mathing::Vec4 calcNode(mathing::Vec4 ab, double l);
        mathing::Vec4 calcLeaf(const mathing::Vec4 &position, const mathing::Vec4 &ab, double l);
    };

    Node *root = nullptr;
    double minCoord, maxCoord;
    double SMOOTH = 0;

public:

    OctTree(double minCoord, double maxCoord) : minCoord(minCoord), maxCoord(maxCoord), SMOOTH(0) {}
    OctTree(double minCoord, double maxCoord, double smooth) : minCoord(minCoord), maxCoord(maxCoord), SMOOTH(smooth) {}
    Node *getRoot();
    double getSmoothParam();
    void setSmooth(double smooth_param);
    void insert(const std::vector<Body*>& bodies);
    void insert(const mathing::Vec4& posit_m, double body_mass);

    mathing::Vec4 get_accel(const mathing::Vec4 &position);

};


#endif //GRAVITYSIMULATOR_OCTTREE_H