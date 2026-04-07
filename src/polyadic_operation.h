//
// Created by StarxSky on 2026/4/5.
//

#ifndef STARXENGINE_POLYADIC_OPERATION_H
#define STARXENGINE_POLYADIC_OPERATION_H
#include <vector>

struct PolyadicOperation {
    double value;
    std::vector<double> grad; // 梯度向量
    //构造函数, 参数传入使用&引用方式防止创建副本变量节省内存开销
    PolyadicOperation(double& value, const std::vector<double>& grad) {
        this->value = value;
        this->grad = grad;
    }
};
#endif //STARXENGINE_POLYADIC_OPERATION_H
