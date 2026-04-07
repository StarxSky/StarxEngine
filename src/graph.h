//
// Created by StarxSky on 2026/4/5.
//

#ifndef STARXENGINE_GRAPH_H
#define STARXENGINE_GRAPH_H
#include <map>
#include <vector>
#include <utility>
#pragma mark Graph

class Graph {


public:
    static long int uid_counter;
    static long int uid();
    static Graph* getInstance();
    void connect(const long int& uid, const std::pair<double, long int>& node);
    void new_recording();
    // 只读成员函数
    std::vector<std::pair<double, long int>> get(const long int& uid) const;
    bool isConnected(const long int& uid) const;


private:
    static Graph* instance;
    std::map<long int, std::vector<std::pair<double, long int>>> nodes;
    Graph() {};// Graph();



};


#endif //STARXENGINE_GRAPH_H
