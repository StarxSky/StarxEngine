//
// Created by StarxSky on 2026/4/5.
//
#include "graph.h"

// 初始化类中static成员变量
Graph *Graph::instance = nullptr;
long int Graph::uid_counter = 0;


long int Graph::uid() {
    return ++uid_counter;
}

void Graph::connect(const long int &uid, const std::pair<double, long int> &node) {
        nodes[uid].push_back(node);
}

Graph *Graph::getInstance() {
    if (instance == nullptr) {
        instance = new Graph();
    }
    return instance;
}

bool Graph::isConnected(const long int& uid) const {
    return nodes.find(uid) != nodes.end();
}

void Graph::new_recording() {
    nodes.clear();
}

std::vector<std::pair<double, long int>> Graph::get(const long int& uid) const {
    return nodes.at(uid);
};
