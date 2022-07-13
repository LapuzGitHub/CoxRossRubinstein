#pragma once

#include <vector>

#include "Node.h"

class NodeSet
{
	private:

		std::vector<Node> nodeVector;
		double strike, stepRiskFreeRate, probaUp, multUp;
		bool optionIsCall;

	public:

		NodeSet(double underlyingSpot, double strike, double stepRiskFreeRate, double multUp, double probaUp, bool optionIsCall, int stepNumber);
		void Backwards();
		double GetOptionValue();
};
