#include "node.h"

Node::Node(const double &value) {
    this->value = value;
    this->uid = 0;
}
Node::Node(const Node& node) {
    this->value = node.value;
    this->uid = node.uid;
}
double Node::gradient_recursive(Graph*  graph, const long int& current_uid, const long int& stop_uid) const{
    if(current_uid==stop_uid){
        return 1.0;
    }

    double sum=0.0;
    if(graph->isConnected(current_uid)){
        for(auto& pair : graph->get(current_uid)){
            sum += pair.first*gradient_recursive(graph, pair.second, stop_uid);
        }
    }
    return sum;
}

double Node::gradient(const Node& node) const{
    Graph* graph = Graph::getInstance();
    return gradient_recursive(graph, this->uid, node.uid);
}

std::vector<double> Node::gradient(const std::vector<Node>& nodes) const{
    Graph* graph = Graph::getInstance();
    std::vector<double> grad(nodes.size());
    for(size_t i=0 ; i<nodes.size() ; i++){
        grad[i] = gradient_recursive(graph, this->uid, nodes[i].uid);
    }
    return grad;
}

std::vector<std::vector<double> > Node::gradient(const std::vector<std::vector<Node> >& nodes) const{
    Graph* graph = Graph::getInstance();
    std::vector<std::vector<double> > grad(nodes.size());
    for(size_t i=0 ; i<nodes.size() ; i++){
        grad[i].resize(nodes[i].size());
        for(size_t j=0 ; j<nodes[i].size() ; j++){
            grad[i][j] = gradient_recursive(graph, this->uid, nodes[i][j].uid);
        }
    }
    return grad;
}

Node Node::monadic_op(const Node& n, MonadicOperation (*fun)(const double&)){
    MonadicOperation res = fun(n.value);
    Node result(res.value);
    Graph* graph = Graph::getInstance();
    graph->connect(result.uid, std::make_pair(res.grad, n.uid));
    return result;
}

Node Node::dyadic_op(const Node& left, const Node& right, DyadicOperation (*fun)(const double&, const double&)){
    DyadicOperation res = fun(left.value, right.value);
    Node result(res.value);
    Graph* graph = Graph::getInstance();
    graph->connect(result.uid, std::make_pair(res.grad1, left.uid));
    graph->connect(result.uid, std::make_pair(res.grad2, right.uid));
    return result;
}

Node Node::polyadic_op(const std::vector<Node>& nodes, PolyadicOperation (*fun)(const std::vector<double>&)){
    std::vector<double> values(nodes.size());
    for(size_t i=0 ; i<nodes.size() ; i++){
        values[i] = nodes[i].value;
    }
    PolyadicOperation res = fun(values);
    Node result(res.value);
    Graph* graph = Graph::getInstance();
    for(size_t i=0 ; i<nodes.size() ; i++){
        graph->connect(result.uid, std::make_pair(res.grad[i], nodes[i].uid));
    }
    return result;
}

Node operator+(const Node& left, const Node& right){
    return Node::dyadic_op(left, right, [](const double& l, const double& r){
        return DyadicOperation(l+r, 1.0, 1.0);
    });
}

Node operator-(const Node& left, const Node& right){
    return Node::dyadic_op(left, right, [](const double& l, const double& r){
        return DyadicOperation(l-r, 1.0, -1.0);
    });
}

Node operator*(const Node& left, const Node& right){
    return Node::dyadic_op(left, right, [](const double& l, const double& r){
        return DyadicOperation(l*r, r, l);
    });
}

Node operator/(const Node& left, const Node& right){
    return Node::dyadic_op(left, right, [](const double& l, const double& r){
        return DyadicOperation(l/r, 1.0/r, -1.0*l/(r*r));
    });
}

Node& Node::operator+=(const Node& r){
    *this = *this + r;
    return *this;
}

Node& Node::operator-=(const Node& r){
    *this = *this - r;
    return *this;
}

Node& Node::operator*=(const Node& r){
    *this = *this * r;
    return *this;
}

Node& Node::operator/=(const Node& r){
    *this = *this / r;
    return *this;
}

bool operator==(const Node& left, const Node& right){
    return left.value==right.value;
}

bool operator<(const Node& left, const Node& right){
    return left.value<right.value;
}

bool operator>(const Node& left, const Node& right){
    return left.value>right.value;
}

bool operator<=(const Node& left, const Node& right){
    return left.value<=right.value;
}

bool operator>=(const Node& left, const Node& right){
    return left.value>=right.value;
}

Node sin(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::sin(n), ::cos(n));
    });
}

Node cos(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::cos(n), -1.0*::sin(n));
    });
}

Node tan(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::tan(n), 1.0/::pow(::cos(n), 2));
    });
}

Node sinh(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::sinh(n), ::cosh(n));
    });
}

Node cosh(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::cosh(n), ::sinh(n));
    });
}

Node asin(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::asin(n), 1.0/(::sqrt(1-n*n)));
    });
}

Node acos(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::acos(n), -1.0/(::sqrt(1-n*n)));
    });
}

Node atan(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::atan(n), 1.0/(1+n*n));
    });
}

Node tanh(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::tanh(n), 1.0-::pow(::tanh(n), 2));
    });
}

Node log(const Node& x, const Node& base){
    return Node::dyadic_op(x, base, [](const double& a, const double& b){
        return DyadicOperation(::log(a)/::log(b), 1.0/(a*::log(b)), -1.0*::log(a)/(b*::log(b)));
    });
}

Node log10(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::log(n)/::log(10), 1.0/(n*::log(10)));
    });
}

Node ln(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::log(n), 1.0/::log(n));
    });
}

Node pow(const Node& x, const Node& base){
    return Node::dyadic_op(x, base, [](const double& a, const double& b){
        if(a<=0){
            return DyadicOperation(::pow(a,b), b*::pow(a,b-1), 0);
        }
        return DyadicOperation(::pow(a,b), b*::pow(a,b-1), ::log(a)*::pow(a,b));
    });
}

Node exp(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::exp(n), ::exp(n));
    });
}

Node sqrt(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        return MonadicOperation(::sqrt(n), 1.0/(2*::sqrt(n)));
    });
}

Node abs(const Node& x){
    return Node::monadic_op(x, [](const double& n){
        int sign = n==0 ? 0 : n/::abs(n);
        return MonadicOperation(::abs(n), sign);
    });
}

Node min(const Node& left, const Node& right){
    return Node::dyadic_op(left, right, [](const double& a, const double& b){
        if(a<b){
            return DyadicOperation(a, 1, 0);
        }
        if(a>b){
            return DyadicOperation(b, 0, 1);
        }
        return DyadicOperation(a, 0, 0);
    });
}

Node max(const Node& left, const Node& right){
    return Node::dyadic_op(left, right, [](const double& a, const double& b){
        if(a>b){
            return DyadicOperation(a, 1, 0);
        }
        if(a<b){
            return DyadicOperation(b, 0, 1);
        }
        return DyadicOperation(a, 0, 0);
    });
}

std::ostream& operator<<(std::ostream& os, const Node& node){
    os << node.value;
    return os;
}
