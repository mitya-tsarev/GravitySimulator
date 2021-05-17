#include "../include/OctTree.h"
#include "../include/Constants.h"


double OctTree::Node::getX() {
    return pos.x;
}

double OctTree::Node::getY() {
    return pos.y;
}

double OctTree::Node::getZ() {
    return pos.z;
}

double OctTree::Node::getSize() {
    return size;
}

double OctTree::Node::getXm() {
    return pos_m.x;
}

double OctTree::Node::getYm() {
    return pos_m.y;
}

double OctTree::Node::getZm() {
    return pos_m.z;
}

double OctTree::Node::getSumMass() {
    return sum_mass;
}

OctTree::Node::Node(const mathing::Vec4 &pos, double size, const mathing::Vec4 &posM, double sumMass) : pos(pos),
                                                                                                        size(size),
                                                                                                        pos_m(posM),
                                                                                                        sum_mass(
                                                                                                                sumMass) {}

OctTree::Node *
OctTree::Node::createOrInsert(OctTree::Node *n, const mathing::Vec4 &posit, double h, const mathing::Vec4 &posit_m,
                              double m) {
    //TODO Deal with identical bodies
    return (n == nullptr ? new Node(posit, h, posit_m, m) : n->insert(posit_m, m));
}

bool OctTree::Node::isLeaf() {
    return TSW == nullptr && TNW == nullptr && TSE == nullptr && TNE == nullptr &&
           BSW == nullptr && BNW == nullptr && BSE == nullptr && BNE == nullptr;
}

mathing::Vec4 OctTree::Node::get_accel(const mathing::Vec4 &position) {
    mathing::Vec4 ab = pos_m;
    ab -= position;
    double l = ab.Length3();
    if (isLeaf()) {
        return calcLeaf(position, ab, l);
    } else {
        double theta = 2 * size / l;
        if (theta < Constants::TAU) {
            return calcNode(ab, l);
        } else {
            mathing::Vec4 a = mathing::Vec4();
            if (TSW != nullptr) a += TSW->get_accel(position);
            if (TNW != nullptr) a += TNW->get_accel(position);
            if (TSE != nullptr) a += TSE->get_accel(position);
            if (TNE != nullptr) a += TNE->get_accel(position);
            if (BSW != nullptr) a += BSW->get_accel(position);
            if (BNW != nullptr) a += BNW->get_accel(position);
            if (BSE != nullptr) a += BSE->get_accel(position);
            if (BNE != nullptr) a += BNE->get_accel(position);
            return a;
        }
    }
}

void OctTree::Node::insertInternal(const mathing::Vec4 &posit_m, double m) {
    double xm = posit_m.x;
    double ym = posit_m.y;
    double zm = posit_m.z;
    double x = pos.x;
    double y = pos.y;
    double z = pos.z;
    double ns = size / 2;
    if (xm <= x && ym <= y && zm <= z) {
        BNW = createOrInsert(BNW, mathing::Vec4(x - ns, y - ns, z - ns), ns, posit_m, m);
    } else if (xm <= x && ym > y && zm <= z) {
        BSW = createOrInsert(BSW, mathing::Vec4(x - ns, y + ns, z - ns), ns, posit_m, m);
    } else if (xm > x && ym <= y && zm <= z) {
        BNE = createOrInsert(BNE, mathing::Vec4(x + ns, y - ns, z - ns), ns, posit_m, m);
    } else if (xm > x && ym > y && zm <= z) {
        BSE = createOrInsert(BSE, mathing::Vec4(x + ns, y + ns, z - ns), ns, posit_m, m);
    } else if (xm <= x && ym <= y && zm > z) {
        TNW = createOrInsert(TNW, mathing::Vec4(x - ns, y - ns, z + ns), ns, posit_m, m);
    } else if (xm <= x && ym > y && zm > z) {
        TSW = createOrInsert(TSW, mathing::Vec4(x - ns, y + ns, z + ns), ns, posit_m, m);
    } else if (xm > x && ym <= y && zm > z) {
        TNE = createOrInsert(TNE, mathing::Vec4(x + ns, y - ns, z + ns), ns, posit_m, m);
    } else if (xm > x && ym > y && zm > z) {
        TSE = createOrInsert(TSE, mathing::Vec4(x + ns, y + ns, z + ns), ns, posit_m, m);
    } else {
        std::cout << "At \"Insert_Internal\": not adding a body to a octant\n" << std::endl;
    }
}

OctTree::Node *OctTree::Node::insert(const mathing::Vec4 &posit_m, double m) {
    if (isLeaf()) {
        insertInternal(mathing::Vec4(pos_m), sum_mass);
    }
    insertInternal(posit_m, m);
    pos_m = (posit_m * m + sum_mass * pos_m) / (sum_mass + m);
    sum_mass += m;
    return this;
}

mathing::Vec4 OctTree::Node::calcNode(mathing::Vec4 ab, double l) {
    return ab *= (Constants::G * sum_mass / (l * (l * l))); //TODO add SMOOTH * SMOOTH to l * l
}

mathing::Vec4 OctTree::Node::calcLeaf(const mathing::Vec4 &position, const mathing::Vec4 &ab, double l) {
    if ((position - pos_m).Length3Sqr() == 0) { // Fix comparing double to 0
        return mathing::Vec4();
    }
    return calcNode(mathing::Vec4(ab), l);
}

OctTree::Node *OctTree::getRoot() {
    return root;
}

void OctTree::insert(const std::vector<Body *> &bodies) {
    for (Body *p : bodies) {
        insert(p->getPos(), p->getMass());
    }
}

void OctTree::insert(const mathing::Vec4 &posit_m, double body_mass) {
    if (root != nullptr) {
        root->insert(posit_m, body_mass);
    } else {
        double midPoint = (minCoord + maxCoord) / 2;
        double halfSize = (maxCoord - minCoord) / 2;
        mathing::Vec4 centre = mathing::Vec4(midPoint, midPoint, midPoint);

        root = new Node(centre, halfSize, posit_m, body_mass);
    }
}

double OctTree::getSmoothParam() {
    return SMOOTH;
}

mathing::Vec4 OctTree::get_accel(const mathing::Vec4 &position) {
    if (root == nullptr) {
        return mathing::Vec4();
    }
    return root->get_accel(position);
}

void OctTree::setSmooth(double smooth_param) {
    SMOOTH = smooth_param;
}
