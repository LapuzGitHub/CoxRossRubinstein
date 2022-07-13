
#include "NodeSet.h"

NodeSet::NodeSet(double underlyingSpot, double strike, double stepRiskFreeRate, double multUp, double probaUp, bool optionIsCall, int stepNumber)
{
	this->strike = strike;
	this->stepRiskFreeRate = stepRiskFreeRate;
	this->probaUp = probaUp;
	this->multUp = multUp;
	this->optionIsCall = optionIsCall;

	for (int nodeIndex = 0; nodeIndex <= stepNumber; nodeIndex++)
	{
		nodeVector.push_back(Node(underlyingSpot, strike, multUp, optionIsCall, nodeIndex, stepNumber));
	}
}

void NodeSet::Backwards()
{
	std::vector<Node> newVector;
	for (unsigned int i = 0; i < nodeVector.size() - 1; i++)
	{
		newVector.push_back(Node(nodeVector.at(i), nodeVector.at(i + 1), strike, stepRiskFreeRate, probaUp, multUp, optionIsCall));
	}

	nodeVector = newVector;
}

double NodeSet::GetOptionValue()
{
	if (nodeVector.size() != 1)
		throw std::exception("Computation is ongoing");
	return nodeVector.at(0).GetOptionValue();
}
