
#include <exception>
#include <iostream>
#include <algorithm> 

#include "Tree.h"
#include "NodeSet.h"

Tree::Tree(double underlyingSpot, double strike, double volatility, double expiry, double riskFreeRate, double dividendRate, bool optionIsCall, int stepNumber)
{
	this->underlyingSpot = underlyingSpot;
	this->strike = strike;
	this->volatility = volatility;
	this->expiry = expiry;
	this->riskFreeRate = riskFreeRate;
	this->dividendRate = dividendRate;
	this->optionIsCall = optionIsCall;
	this->stepNumber = stepNumber;

	if (underlyingSpot <= 0.)
		throw std::exception("Error input underlying");
	if (strike <= 0.)
		throw std::exception("Error input strike");
	if (volatility <= 0.)
		throw std::exception("Error input volatility");
	if (expiry <= 0.)
		throw std::exception("Error input expiry");
	if (stepNumber <= 0.)
		throw std::exception("Error input step number");
}

double Tree::GetPremium()
{
	double timeStep = expiry / stepNumber;
	if ((timeStep * std::pow(riskFreeRate - dividendRate, 2)) >= std::pow(volatility, 2)) // probaUp > 1.
		throw std::exception("Model failure : please increase step number");

	double multUp = std::exp(volatility * std::sqrt(timeStep));
	double multDown = 1. / multUp;

	double probaUp = (std::exp((riskFreeRate - dividendRate) * timeStep) - multDown) / (multUp - multDown);

	NodeSet currentNodeSet(underlyingSpot, strike, riskFreeRate * timeStep, multUp, probaUp, optionIsCall, stepNumber);

	for (int i = 0; i < stepNumber; i++)
	{
		currentNodeSet.Backwards();
	}

	return currentNodeSet.GetOptionValue();
}

double Tree::GetDelta(double premium)
{
	if (premium <= 0.)
	{
		Tree tree(underlyingSpot, strike, volatility, expiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);
		premium = tree.GetPremium();
	}

	double shiftSpot = underlyingSpot / GREEK_STEP_DIVIDE;
	Tree shiftTree(underlyingSpot + shiftSpot, strike, volatility, expiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);

	return (shiftTree.GetPremium() - premium) / shiftSpot;
}

double Tree::GetGamma(double premium)
{
	if (premium <= 0.)
	{
		Tree tree(underlyingSpot, strike, volatility, expiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);
		premium = tree.GetPremium();
	}

	double shiftSpot = underlyingSpot / GREEK_STEP_DIVIDE;
	Tree shiftUpTree(underlyingSpot + shiftSpot, strike, volatility, expiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);
	Tree shiftDownTree(underlyingSpot - shiftSpot, strike, volatility, expiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);
	
	return (shiftUpTree.GetPremium() - 2. * premium + shiftDownTree.GetPremium()) / (100. * std::pow(shiftSpot, 2));
}

double Tree::GetVega(double premium)
{
	if (premium <= 0.)
	{
		Tree tree(underlyingSpot, strike, volatility, expiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);
		premium = tree.GetPremium();
	}

	double shiftVol = volatility / GREEK_STEP_DIVIDE;
	Tree shiftTree(underlyingSpot, strike, volatility + shiftVol, expiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);

	return (shiftTree.GetPremium() - premium) / (100. * shiftVol);
}

double Tree::GetTheta(double premium)
{
	if (premium <= 0.)
	{
		Tree tree(underlyingSpot, strike, volatility, expiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);
		premium = tree.GetPremium();
	}

	double shiftExpiry = expiry / GREEK_STEP_DIVIDE;
	Tree shiftTree(underlyingSpot, strike, volatility, expiry + shiftExpiry, riskFreeRate, dividendRate, optionIsCall, stepNumber);

	return - (shiftTree.GetPremium() - premium) / (365. * shiftExpiry);
}
