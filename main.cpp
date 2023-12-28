#include "view.h"
#include "budgethandler.h"
#include "investmentsimulator.h"
#include "learningpath.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication* a = new QApplication(argc, argv);
    QFile file(":/style.txt");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a->setStyleSheet(styleSheet);
    BudgetHandler budgetHandler;
    InvestmentSimulator investmentSimulator;
    LearningPath learningPath;
    View w(investmentSimulator, budgetHandler, learningPath);
    w.show();
    return a->exec();
}

