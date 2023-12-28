#ifndef INVESTMENTSIMULATOR_H
#define INVESTMENTSIMULATOR_H

#include <QObject>
class InvestmentSimulator : public QObject
{
    Q_OBJECT
public:
    InvestmentSimulator();

private:
    double inputInitialAmount;
    double inputCompoundingFrequency;
    double inputInterestRate;
    double inputTimeInvested;
    double inputMonthlyContributions;
    double finalAmount;
    double earningsFromCompoundInterest;

public slots:
    void calculateCompoundInterest_slot(double, double, double, double, double);

signals:
    void updateFinalAmount_signal(double, double);
};
#endif // INVESTMENTSIMULATOR_H
