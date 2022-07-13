
#include <iostream>

#include "Tree.h"

int main()
{
	double underlyingSpot = 100;
	double strike = 100;
	double volatility = 0.15;
	double expiry = 0.25;
	double riskFreeRate = 0.04;
	double dividendRate = 0.02;
	bool optionIsCall = true;
	int stepNumber = 100;

	try
	{
		Tree tree(underlyingSpot, strike, volatility, expiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);
		double premium = tree.GetPremium();

		std::cout << "Premium " << premium << std::endl;
		std::cout << "Delta " << tree.GetDelta(premium) << std::endl;
		std::cout << "Gamma " << tree.GetGamma(premium) << std::endl;
		std::cout << "Vega " << tree.GetVega(premium) << std::endl;
		std::cout << "Theta " << tree.GetTheta(premium) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception caught: " << e.what() << '\n';
	}
}
