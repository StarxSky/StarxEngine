//
// Created by StarxSky on 2026/4/5.
//

#ifndef STARXENGINE_NODE_H
#define STARXENGINE_NODE_H

#include "graph.h"
#include "dyadic_operation.h"
#include "monadic_operation.h"
#include "polyadic_operation.h"
#include <iostream>


class Node {
public:
    Node(const double& value = 0);
    Node(const Node& node);
    // 成员函数
    // static修饰的成员函数无this 指针，可以直接在不实例的条件下直接调用类中成员函数
    static Node monadic_op(const Node& n, MonadicOperation (*)(const double&));
    static Node dyadic_op(const Node& n1, const Node& n2, DyadicOperation (*)(const double&, const double&));
    static Node polyadic_op(const std::vector<Node>& nodes, PolyadicOperation (*)(const std::vector<double>&));

    double gradient(const Node& node) const;
    std::vector<double> gradient(const std::vector<Node>& nodes) const;
    std::vector<std::vector<double> > gradient(const std::vector<std::vector<Node> >& nodes) const;

    friend Node operator+(const Node& l, const Node& r);
    friend Node operator-(const Node& l, const Node& r);
    friend Node operator*(const Node& l, const Node& r);
    friend Node operator/(const Node& l, const Node& r);

    // Node&: 函数运行后会产生一个指向Node 类型的一个引用
    Node& operator+=(const Node& r);
    Node& operator-=(const Node& r);
    Node& operator*=(const Node& r);
    Node& operator/=(const Node& r);

    friend bool operator==(const Node& l, const Node& r);
    friend bool operator<(const Node& l, const Node& r);
    friend bool operator>(const Node& l, const Node& r);
    friend bool operator<=(const Node& l, const Node& r);
    friend bool operator>=(const Node& l, const Node& r);

    friend Node sin(const Node& x);
    friend Node cos(const Node& x);
    friend Node tan(const Node& x);
    friend Node sinh(const Node& x);
    friend Node cosh(const Node& x);
    friend Node tanh(const Node& x);
    friend Node asin(const Node& x);
    friend Node acos(const Node& x);
    friend Node atan(const Node& x);

    friend Node log(const Node& x, const Node& base);
    friend Node log10(const Node& x);
    friend Node ln(const Node& x);

    friend Node pow(const Node& x, const Node& p);
    friend Node exp(const Node& x);
    friend Node sqrt(const Node& x);

    friend Node abs(const Node& x);
    friend Node min(const Node& l, const Node& r);
    friend Node max(const Node& l, const Node& r);

    friend std::ostream& operator<<(std::ostream& os, const Node& node);

private:
    double value;
    long int uid;
    double gradient_recursive(Graph* graph, const long int& current_uid, const long int& stop_uid) const;
};

#endif //STARXENGINE_NODE_H
