#include "budgethandler.h"

BudgetHandler::BudgetHandler(){}

/**
 * @brief BudgetHandler::calculateBudgetSummaries_slot
 * @param grossIncome
 */
void BudgetHandler::calculateBudgetSummaries_slot(double grossIncome)
{
    this->inputMonthlyGrossIncome = grossIncome;
    expectedMonthlyWitholdings = grossIncome * .195;
    monthlyNetIncome = grossIncome - expectedMonthlyWitholdings;
    emit displayUpdatedIncome_signal(expectedMonthlyWitholdings, monthlyNetIncome);
}

/**
 * @brief BudgetHandler::updateCategoryAmounts_slot
 * @param housing
 * @param utilities
 * @param food
 * @param personalCare
 * @param insurance
 * @param transportation
 * @param giving
 * @param saving
 * @param entertainment
 * @param medical
 * @param misc
 */
void BudgetHandler::updateCategoryAmounts_slot(double housing, double utilities, double food, double personalCare, double insurance,
                                               double transportation, double giving, double saving, double entertainment, double medical, double misc)
{
    inputGiving = giving;
    inputSaving = saving;
    inputFood = food;
    inputUtilities = utilities;
    inputHousing = housing;
    inputTransportation = transportation;
    inputHealth = medical;
    inputInsurance = insurance;
    inputEntertainment = entertainment;
    inputPersonalCare = personalCare;
    inputMisc = misc;

    emit sendMonthlySummary_signal(monthlyNetIncome, calculateTotalMonthlyExpenses());
}

/**
 * @brief BudgetHandler::calculateTotalMonthlyExpenses
 */
double BudgetHandler::calculateTotalMonthlyExpenses()
{
    return inputGiving +
           inputSaving +
           inputFood +
           inputUtilities +
           inputHousing +
           inputTransportation +
           inputHealth +
            inputInsurance +
           inputEntertainment +
           inputPersonalCare +
           inputMisc;
}

void BudgetHandler::populateSuggestedCategories_slot(){
    emit populateCategories_signal(
                suggestedHousing * monthlyNetIncome,
                suggestedUtilities * monthlyNetIncome,
                suggestedFood * monthlyNetIncome,
                suggestedPersonalCare * monthlyNetIncome,
                suggestedTransportation * monthlyNetIncome,
                suggestedInsurance * monthlyNetIncome,
                suggestedGiving * monthlyNetIncome,
                suggestedSaving * monthlyNetIncome,
                suggestedEntertainment * monthlyNetIncome,
                suggestedHealth * monthlyNetIncome,
                suggestedMisc * monthlyNetIncome
                );
}

void BudgetHandler::sendCategoryAmounts_slot(){
    emit populateCategories_signal(
                inputHousing,
                inputUtilities,
                inputFood,
                inputPersonalCare,
                inputTransportation,
                inputInsurance,
                inputGiving,
                inputSaving,
                inputEntertainment,
                inputHealth,
                inputMisc);
}

void BudgetHandler::sendCategoryPercentages_slot(){
    emit populateCategories_signal(
                inputHousing / monthlyNetIncome * 100,
                inputUtilities / monthlyNetIncome * 100,
                inputFood / monthlyNetIncome * 100,
                inputPersonalCare / monthlyNetIncome * 100,
                inputTransportation / monthlyNetIncome * 100,
                inputInsurance / monthlyNetIncome * 100,
                inputGiving / monthlyNetIncome * 100,
                inputSaving / monthlyNetIncome * 100,
                inputEntertainment / monthlyNetIncome * 100,
                inputHealth / monthlyNetIncome * 100,
                inputMisc / monthlyNetIncome * 100);
}
