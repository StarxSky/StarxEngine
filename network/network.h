#include<iostream>
#include<string>
#include <math.h>
#include"../src/node.h"
#include"../matrixsrc/matrix_def.h"
#include"../matrixsrc/matrix_pro.h"
#include"../src/logistic_def.h"
using namespace std;
float sigmoid(float x){
    return 1/(1+exp(x));
}
Node sigmoid(Node z){
   Node sigmoid = 1/(1+(1/exp(z)));
    return sigmoid;
}


class  network {
private:
	int input;
	int num_neuron;
public:
	network(int input, int num_neuron){
		this->input = input;
		this->num_neuron = num_neuron;
    }
	Matrix forward(Matrix data,Matrix weights,Matrix bais)
	{

		cout_mat(weights);
		cout_mat(data);

		Matrix output = mul(weights,data);
		cout<<"out:"<<endl;
		cout_mat(output);
		output = add(output,bais,0);
		Matrix output1 = e_sigmoid(output);
		return output1;
	}
	Matrix forward_without_act(Matrix data,Matrix weights,Matrix bais)
	{
		Matrix output = mul(weights,data);
		output = add(output,bais,0);
		return output;
	}
	Matrix backward(Matrix grad_next, Matrix output_before,Matrix weights,Node p_(Node))
	{
		for(int index = 0;index<output_before.row;index++)
		{
			Node z = output_before.matrix[index][0];
			Node anyone = p_(z);
			change_va(output_before,index,0,anyone.gradient(z));
		}
		return mul_simple(mul(weights,grad_next),output_before);
	}
	Matrix end_layer_backward(Matrix label,Matrix acti_val,Node loss_fun(Node,Node),Node act_fun(Node))
	{
		Matrix loss_act = CreateMatrix(acti_val.row,acti_val.col);
		Matrix act_output = CreateMatrix(acti_val.row,acti_val.col);
		int index_x,index_y;
		for(index_x=0;index_x<loss_act.row;index_x++)
		{
		Node t1 = label.matrix[index_x][0],z31 =acti_val.matrix[index_x][0];
		Node a13 = 1/(1+(1/exp(z31)));
		Node loss = loss_fun(t1,a13);
		cout<<"loss:"<<loss<<endl;
		Node act = act_fun(z31);
		act_output.matrix[index_x][0] = act.gradient(z31);
		loss_act.matrix[index_x][0] = loss.gradient(a13);
		}
		Matrix mid_grad_end = mul_simple(loss_act,act_output);
		cout_mat(mid_grad_end);
		return mid_grad_end;
	}
};


