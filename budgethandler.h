#ifndef BUDGETHANDLER_H
#define BUDGETHANDLER_H

#include <QObject>
class BudgetHandler : public QObject
{
    Q_OBJECT

public:
    BudgetHandler();

private:
    double inputMonthlyGrossIncome;
    double expectedMonthlyWitholdings;
    double monthlyNetIncome;

    double suggestedGiving = .05;
    double suggestedSaving = .10;
    double suggestedFood = .15;
    double suggestedUtilities = .05;
    double suggestedHousing = .25;
    double suggestedTransportation = .10;
    double suggestedHealth = .05;
    double suggestedInsurance = .10;
    double suggestedEntertainment = .05;
    double suggestedPersonalCare = .05;
    double suggestedMisc = .05;
    double inputGiving;
    double inputSaving;
    double inputFood;
    double inputUtilities;
    double inputHousing;
    double inputTransportation;
    double inputHealth;
    double inputInsurance;
    double inputEntertainment;
    double inputPersonalCare;
    double inputMisc;
    double calculateTotalMonthlyExpenses();

public slots:
    void calculateBudgetSummaries_slot(double);
    void updateCategoryAmounts_slot(double, double, double, double, double, double, double, double, double, double, double);
    void populateSuggestedCategories_slot();
    void sendCategoryPercentages_slot();
    void sendCategoryAmounts_slot();

signals:
    void displayUpdatedIncome_signal(double, double);
    void sendMonthlySummary_signal(double, double);
    void populateCategories_signal(double, double, double, double, double, double, double, double, double, double, double);

};

#endif // BUDGETHANDLER_H
