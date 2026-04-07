//
// Created by StarxSky on 2026/4/5.
//

#ifndef STARXENGINE_DYADIC_OPERATION_H
#define STARXENGINE_DYADIC_OPERATION_H
struct DyadicOperation {
    double value;
    double grad1;
    double grad2;

    DyadicOperation(double value, double grad1, double grad2) {
        this->value = value;
        this->grad1 = grad1;
        this->grad2 = grad2;
    }
};
#endif //STARXENGINE_DYADIC_OPERATION_H
