#pragma once

class Node
{
	private:

		double optionValue, underlyingValue;

		static double IntrinsicValue(bool optionIsCall, double strike, double underlyingValue);

	public:

		Node(double underlyingSpot, double strike, double multUp, bool optionIsCall, int nodeIndex, int stepNumber);
		Node(const Node& nodeUp, const Node& nodeDown, double strike, double stepRiskFreeRate, double probaUp, double multUp, bool optionIsCall);

		double GetOptionValue() { return optionValue; }
};
