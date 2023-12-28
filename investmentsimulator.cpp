#include "investmentsimulator.h"

InvestmentSimulator::InvestmentSimulator() {}

/**
 * @brief InvestmentSimulator::calculateCompoundInterest_slot
 * @param initialAmount
 * @param interestRate
 * @param compoundingFrequency
 * @param timeInvested
 * @param monthlyContributions
 */
void InvestmentSimulator::calculateCompoundInterest_slot(double initialAmount, double interestRate, double compoundingFrequency,
                                                         double timeInvested, double monthlyContributions)
{
    inputInitialAmount = initialAmount;
    inputInterestRate = interestRate / 100;
    inputCompoundingFrequency = compoundingFrequency;
    inputTimeInvested = timeInvested;
    inputMonthlyContributions = monthlyContributions;
    finalAmount = inputInitialAmount * pow((1 + inputInterestRate/inputCompoundingFrequency), inputCompoundingFrequency * inputTimeInvested)
                  + inputMonthlyContributions * (12/inputCompoundingFrequency)
                  * ((pow((1 + inputInterestRate/inputCompoundingFrequency), inputCompoundingFrequency * inputTimeInvested) - 1) / (inputInterestRate/inputCompoundingFrequency));
    earningsFromCompoundInterest = finalAmount - (inputMonthlyContributions * 12 * inputTimeInvested) - inputInitialAmount;
    emit updateFinalAmount_signal(finalAmount, earningsFromCompoundInterest);
}
