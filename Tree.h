#pragma once

class Tree
{
	private:

		static const int GREEK_STEP_DIVIDE = 1000000;

		double underlyingSpot, strike, volatility, expiry, riskFreeRate, dividendRate;
		bool optionIsCall;
		int stepNumber;

	public:

		Tree(double underlyingSpot, double strike, double volatility, double expiry, double riskFreeRate, double dividendRate, bool optionIsCall, int stepNumber);

		double GetPremium();
		double GetDelta(double premium = 0.);
		double GetGamma(double premium = 0.);
		double GetVega(double premium = 0.);
		double GetTheta(double premium = 0.);
};
