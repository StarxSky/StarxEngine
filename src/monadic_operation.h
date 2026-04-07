//
// Created by StarxSky on 2026/4/5.
//

#ifndef STARXENGINE_MONADIC_OPERATION_H
#define STARXENGINE_MONADIC_OPERATION_H
struct MonadicOperation {
    double value;
    double grad;

    //MonadicOperation(double& value, double& grad) : value(value), grad(grad) {}
    MonadicOperation(double v, double g) {
        this->value = v;
        this->grad = g;
    }

};
#endif //STARXENGINE_MONADIC_OPERATION_H
