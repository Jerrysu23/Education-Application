#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "budgethandler.h"
#include "investmentsimulator.h"
#include "learningpath.h"

using std::tuple;
using std::map;

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(InvestmentSimulator&, BudgetHandler&, LearningPath&, QWidget *parent = nullptr);
    ~View();


private:
    Ui::View *ui;
    void unlockNextModuleOrQuiz();
    void hideAllPages();
    void loadPage();
    void loadQuizPage();
    void extraPageSetup();
    void disableAnswerButtons();
    int currSection;
    int currModule;
    int currPage;
    int currQuiz;
    int currQuestion;
    int quizScore = 0;
    void calculateQuizScore();
    int getNumberOfQuestion();
    void setProgressBar();
    vector<vector<vector<QString>>> pageTextData;
    vector<char> section1Quiz1Answers = {'D', 'B', 'A'};
    vector<char> section1Quiz2Answers = {'A', 'C', 'D'};
    vector<char> section2Quiz1Answers = {'B', 'D', 'C'};
    vector<char> section2Quiz2Answers = {'A', 'B', 'A'};
    vector<char> userMoves;

public slots:
    void calculateBudgetSummaries_slot();
    void calculateMonthlyIncome_slot();
    void populateCategories_slot(double, double, double, double, double, double, double, double, double, double, double);
    void updateMonthlyIncome_slot(double, double);
    void updateSummaries_slot(double, double);
    void calculateCompoundInterest_slot();
    void updateFinalInvestedAmount_slot(double, double);
    void showPercentages_slot();
    void nextPage_slot();
    void goToLearningPath_slot();
    void goToMenu_slot();
    void goToBudgetingSimulator_slot();
    void goToInvestingSimulator_slot();
    void goToWelcomeScreen_slot();
    void goToSection1Module1_slot();
    void goToSection1Module2_slot();
    void goToSection1Module3_slot();
    void goToSection1Module4_slot();
    void goToSection2Module1_slot();
    void goToSection2Module2_slot();
    void goToSection2Module3_slot();
    void goToSection2Module4_slot();
    void goToSection1Quiz1_slot();
    void goToSection1Quiz2_slot();
    void nextQuestion_slot();
    void goToSection2Quiz1_slot();
    void goToSection2Quiz2_slot();
    void buttonA_slot();
    void buttonB_slot();
    void buttonC_slot();
    void buttonD_slot();
    void scorePageButton_slot();

signals:
    void calculateCompoundInterest_signal(double, double, double, double, double);
    void sendMonthlyGrossIncome_signal(double);
    void updateBudgetCategoryEntries_signal(double, double, double, double, double, double, double, double, double, double, double);
    void getCategoryPercentages_signal();
    void getCategoryDollarAmounts_signal();
    void startPhysics_signal();
};
#endif // VIEW_H
