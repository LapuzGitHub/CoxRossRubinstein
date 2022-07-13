
#include <iostream>
#include <algorithm> 

#include "Node.h"

Node::Node(double underlyingSpot, double strike, double multUp, bool optionIsCall, int nodeIndex, int stepNumber)
{
	underlyingValue = underlyingSpot * std::pow(multUp, stepNumber - 2 * nodeIndex);
	optionValue = IntrinsicValue(optionIsCall, strike, underlyingValue);
}

Node::Node(const Node& nodeUp, const Node& nodeDown, double strike, double stepRiskFreeRate, double probaUp, double multUp, bool optionIsCall)
{
	underlyingValue = nodeUp.underlyingValue / multUp;

	double optionTreeValue = std::exp(-stepRiskFreeRate) * (probaUp * nodeUp.optionValue + (1. - probaUp) * nodeDown.optionValue);;
	double optionIntrinsicValue = IntrinsicValue(optionIsCall, strike, underlyingValue);
	optionValue = std::max(optionTreeValue, optionIntrinsicValue);
}

double Node::IntrinsicValue(bool optionIsCall, double strike, double underlyingValue)
{
	return optionIsCall ? std::max(underlyingValue - strike, 0.) : std::max(strike - underlyingValue, 0.);
}
