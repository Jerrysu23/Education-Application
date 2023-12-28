#include "view.h"
#include "investmentsimulator.h"
#include "physicsscenewidget.h"
//#include "textbox2danimationwidget.h"
#include "ui_view.h"
#include <QMessageBox>
#include <QPixmap>

using std::string;
using std::vector;

/**
 * @brief View::View
 * @param investmentSimulator
 * @param budgetHandler
 * @param parent
 */
View::View(InvestmentSimulator& investmentSimulator, BudgetHandler& budgetHandler, LearningPath& learningPath, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);

    pageTextData = learningPath.getTextData();

    // Welcome Page connections
    connect(ui->startLearningButton, &QPushButton::clicked, this, &View::goToMenu_slot);

    // Menu Page connections
    connect(ui->learningPathButton, &QPushButton::clicked, this, &View::goToLearningPath_slot);
    connect(ui->budgetingSimulatorButton, &QPushButton::clicked, this, &View::goToBudgetingSimulator_slot);
    connect(ui->investingSimulatorButton, &QPushButton::clicked, this, &View::goToInvestingSimulator_slot);
    connect(ui->backToWelcomeScreenButton, &QPushButton::clicked, this, &View::goToWelcomeScreen_slot);

    // Budget Simulator connections
    connect(ui->calculateBudgetSummariesButton, &QPushButton::clicked, this, &View::calculateBudgetSummaries_slot);
    connect(ui->calculateMonthlyIncomeButton, &QPushButton::clicked, this, &View::calculateMonthlyIncome_slot);
    connect(ui->populateSuggestedCateogoriesButton, &QPushButton::clicked, &budgetHandler, &BudgetHandler::populateSuggestedCategories_slot);
    connect(&budgetHandler, &BudgetHandler::populateCategories_signal, this, &View::populateCategories_slot);
    connect(this, &View::sendMonthlyGrossIncome_signal, &budgetHandler, &BudgetHandler::calculateBudgetSummaries_slot);
    connect(&budgetHandler, &BudgetHandler::displayUpdatedIncome_signal, this, &View::updateMonthlyIncome_slot);
    connect(this, &View::updateBudgetCategoryEntries_signal, &budgetHandler, &BudgetHandler::updateCategoryAmounts_slot);
    connect(&budgetHandler, &BudgetHandler::sendMonthlySummary_signal, this, &View::updateSummaries_slot);
    connect(ui->mainMenuBudgetPageButton, &QPushButton::clicked, this, &View::goToMenu_slot);
    connect(ui->showPercentagesCheckBox, &QCheckBox::toggled, this, &View::showPercentages_slot);
    connect(this, &View::getCategoryPercentages_signal, &budgetHandler, &BudgetHandler::sendCategoryPercentages_slot);
    connect(this, &View::getCategoryDollarAmounts_signal, &budgetHandler, &BudgetHandler::sendCategoryAmounts_slot);

    // Investing Simulator connections
    connect(ui->calculateButton, &QPushButton::clicked, this, &View::calculateCompoundInterest_slot);
    connect(this, &View::calculateCompoundInterest_signal, &investmentSimulator, &InvestmentSimulator::calculateCompoundInterest_slot);
    connect(&investmentSimulator, &InvestmentSimulator::updateFinalAmount_signal, this, &View::updateFinalInvestedAmount_slot);
    connect(ui->mainMenuInvestingPageButton, &QPushButton::clicked, this, &View::goToMenu_slot);

    // Learning Path connections
    connect(ui->mainMenuLearningPathButton, &QPushButton::clicked, this, &View::goToMenu_slot);
    connect(ui->section1Module1Button, &QPushButton::clicked, this, &View::goToSection1Module1_slot);
    connect(ui->section1Module2Button, &QPushButton::clicked, this, &View::goToSection1Module2_slot);
    connect(ui->section1Module3Button, &QPushButton::clicked, this, &View::goToSection1Module3_slot);
    connect(ui->section1Module4Button, &QPushButton::clicked, this, &View::goToSection1Module4_slot);
    connect(ui->section2Module1Button, &QPushButton::clicked, this, &View::goToSection2Module1_slot);
    connect(ui->section2Module2Button, &QPushButton::clicked, this, &View::goToSection2Module2_slot);
    connect(ui->section2Module3Button, &QPushButton::clicked, this, &View::goToSection2Module3_slot);
    connect(ui->section2Module4Button, &QPushButton::clicked, this, &View::goToSection2Module4_slot);
    connect(ui->pageNextButton, &QPushButton::clicked, this, &View::nextPage_slot);

    // Quiz connections
    connect(ui->questionNextButton, &QPushButton::clicked, this, &View::nextQuestion_slot);
    connect(ui->section1Quiz1Button, &QPushButton::clicked, this, &View::goToSection1Quiz1_slot);
    connect(ui->section1Quiz2Button, &QPushButton::clicked, this, &View::goToSection1Quiz2_slot);
    connect(ui->section2Quiz1Button, &QPushButton::clicked, this, &View::goToSection2Quiz1_slot);
    connect(ui->section2Quiz2Button, &QPushButton::clicked, this, &View::goToSection2Quiz2_slot);
    connect(ui->answerAButton, &QPushButton::clicked, this, &View::buttonA_slot);
    connect(ui->answerBButton, &QPushButton::clicked, this, &View::buttonB_slot);
    connect(ui->answerCButton, &QPushButton::clicked, this, &View::buttonC_slot);
    connect(ui->answerDButton, &QPushButton::clicked, this, &View::buttonD_slot);
    connect(ui->scorePageButton, &QPushButton::clicked, this, &View::scorePageButton_slot);


    // Physics connections
    connect(this, &View::startPhysics_signal, ui->PhysicsWindow, &PhysicsSceneWidget::runPhysics_slot);

    ui->percent->setVisible(false);
    ui->percent_2->setVisible(false);
    ui->percent_3->setVisible(false);
    ui->percent_4->setVisible(false);
    ui->percent_5->setVisible(false);
    ui->percent_6->setVisible(false);
    ui->percent_7->setVisible(false);
    ui->percent_8->setVisible(false);
    ui->percent_9->setVisible(false);
    ui->percent_10->setVisible(false);
    ui->percent_11->setVisible(false);

    // Set the default page to the welcome screen
    ui->stackedWidget->setCurrentIndex(0);
    QPixmap pixmap(":/pieChart.png");
    ui->pieChartImageLabel->setPixmap(pixmap);
    QPixmap compoundInterestPixmap(":/compound interest.jpeg");
    ui->compoundVsSimpleInterestGraph->setPixmap(compoundInterestPixmap);
}

/**
 * @brief View::~View
 */
View::~View()
{
    delete ui;
}

/**
 * @brief View::goToWelcomeScreen_slot
 */
void View::goToWelcomeScreen_slot()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief View::goToMenu_slot
 */
void View::goToMenu_slot()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief View::goToLearningPath_slot
 */
void View::goToLearningPath_slot()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/**
 * @brief View::goToBudgetingSimulator_slot
 */
void View::goToBudgetingSimulator_slot()
{
    ui->stackedWidget->setCurrentIndex(3);
}

/**
 * @brief View::goToInvestingSimulator_slot
 */
void View::goToInvestingSimulator_slot()
{
    ui->stackedWidget->setCurrentIndex(4);
}
/**
 * @brief View::goToSection1Quiz1_slot
 */
void View::goToSection1Quiz1_slot()
{
    ui->quizProgressBar->setValue(0);
    currSection = 1;
    currQuiz = 1;
    currQuestion = 1;
    loadQuizPage();
}
/**
 * @brief View::goToSection1Quiz2_slot
 */
void View::goToSection1Quiz2_slot()
{
    ui->quizProgressBar->setValue(0);
    currSection = 1;
    currQuiz = 2;
    currQuestion = 1;
    loadQuizPage();
}
/**
 * @brief View::goToSection2Quiz1_slot
 */
void View::goToSection2Quiz1_slot()
{
    ui->quizProgressBar->setValue(0);
    currSection = 2;
    currQuiz = 1;
    currQuestion = 1;
    loadQuizPage();
}
/**
 * @brief View::goToSection2Quiz2_slot
 */
void View::goToSection2Quiz2_slot()
{
    ui->quizProgressBar->setValue(0);
    currSection = 2;
    currQuiz = 2;
    currQuestion = 1;
    loadQuizPage();
}

/**
 * @brief View::goToSection1Module1_slot
 */
void View::goToSection1Module1_slot()
{
    currSection = 1;
    currModule = 1;
    currPage = 1;
    loadPage();
}

/**
 * @brief View::goToSection1Module2_slot
 */
void View::goToSection1Module2_slot()
{
    currSection = 1;
    currModule = 2;
    currPage = 1;
    loadPage();
}

/**
 * @brief View::goToSection1Module3_slot
 */
void View::goToSection1Module3_slot()
{
    currSection = 1;
    currModule = 3;
    currPage = 1;
    loadPage();
}

/**
 * @brief View::goToSection1Module4_slot
 */
void View::goToSection1Module4_slot()
{
    currSection = 1;
    currModule = 4;
    currPage = 1;
    loadPage();
}

/**
 * @brief View::goToSection2Module1_slot
 */
void View::goToSection2Module1_slot()
{
    currSection = 2;
    currModule = 1;
    currPage = 1;
    loadPage();
}

/**
 * @brief View::goToSection2Module2_slot
 */
void View::goToSection2Module2_slot()
{
    currSection = 2;
    currModule = 2;
    currPage = 1;
    loadPage();
}

/**
 * @brief View::goToSection2Module3_slot
 */
void View::goToSection2Module3_slot()
{
    currSection = 2;
    currModule = 3;
    currPage = 1;
    loadPage();
}

/**
 * @brief View::goToSection2Module4_slot
 */
void View::goToSection2Module4_slot()
{
    currSection = 2;
    currModule = 4;
    currPage = 1;
    loadPage();
}

/**
 * @brief View::nextPage_slot
 */
void View::nextPage_slot()
{
    int numOfPages = 0;
    while (pageTextData[currSection - 1][currModule - 1][numOfPages] != "")
    {
        numOfPages++;
    }

    if (currPage >= numOfPages)
    {
        ui->stackedWidget->setCurrentIndex(2);
        unlockNextModuleOrQuiz();
    }
    else
    {
        currPage++;
        loadPage();
    }
}

/**
 * @brief View::nextQuestion_slot
 */
void View::nextQuestion_slot()
{
    if ((int)userMoves.size() < currQuestion)
    {
           QMessageBox::information(this, tr("Invalid Entry"), tr("Please select an option !"), QMessageBox::Ok);
           return;
    }

    if (currQuestion >= getNumberOfQuestion()) //
    {
        calculateQuizScore();
        if (quizScore < 3)
        {
            QMessageBox::information(this, tr("Feedback"), tr("You can't advance to the next Module ! Please take the Quiz again."), QMessageBox::Ok);
            ui->stackedWidget->setCurrentIndex(2);
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(6);
            ui->finalScoreLabel->setText("Final Score " + QString::fromStdString(std::to_string(quizScore)) + " / " + QString::number(getNumberOfQuestion()));
            ui->stackedWidgetQuizTemplates->setCurrentIndex(1);
            emit startPhysics_signal();
            unlockNextModuleOrQuiz();
            userMoves.clear();
        }
        userMoves.clear();

    }
    else
    {
        currQuestion++;
        loadQuizPage();
    }
}
/**
 * @brief View::goToSection2Module2_slot
 */
void View::scorePageButton_slot()
{
    ui->stackedWidget->setCurrentIndex(2);
}
/**
 * @brief View::getNumberOfQuestion
 */
int View::getNumberOfQuestion(){
    if (currSection == 1 && currQuiz == 1)
    {
        return section1Quiz1Answers.size();
    }
    if (currSection == 1 && currQuiz == 2)
    {
        return section1Quiz2Answers.size();
    }

    if (currSection == 2 && currQuiz == 1)
    {
        return section2Quiz1Answers.size();
    }
    if (currSection == 2 && currQuiz == 2)
    {
        return section2Quiz2Answers.size();
    }
    return 0;
}

/**
 * @brief View::loadPage
 */
void View::loadPage()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->pageText->setText(pageTextData[currSection - 1][currModule - 1][currPage-1]);
    ui->pageNum->setText(QString::fromStdString(std::to_string(currPage)));
}

/**
 * @brief View::loadQuizPage
 */
void View::loadQuizPage()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidgetQuizTemplates->setCurrentIndex(0);
    ui->answerAButton->setStyleSheet("");
    ui->answerBButton->setStyleSheet("");
    ui->answerCButton->setStyleSheet("");
    ui->answerDButton->setStyleSheet("");

    //
    // ---------- Section 1, Quiz 1 ----------
    //

    if (currSection == 1 && currQuiz == 1 && currQuestion == 1)
    {
        ui->questionLabel->setText("What is a zero sum budget?");
        ui->answerALabel->setText("A budget where you spend $0 on entertainment");
        ui->answerBLabel->setText("A budget where your net income is $0");
        ui->answerCLabel->setText("A budget where your monthly expenses are less than your net income");
        ui->answerDLabel->setText("A budget where all your net income is allocated into budget categories"); // answer D
        extraPageSetup();
    }

    if (currSection == 1 && currQuiz == 1 && currQuestion == 2)
    {
        ui->questionLabel->setText("Which one of the following should almost certainly NOT be covered by money from your 'buffer' category?");
        ui->answerALabel->setText("An uber ride home after going out on a run and spraining your ankle by accident");
        ui->answerBLabel->setText("The bus pass you buy every month so you can get to work"); // answer B
        ui->answerCLabel->setText("An unexpected tire replacement");
        ui->answerDLabel->setText("Buying a set of pans that will last you 10-15 years");
        extraPageSetup();
    }

    if (currSection == 1 && currQuiz == 1 && currQuestion == 3)
    {
        ui->questionLabel->setText("Which item would NOT be included in the 'must-haves' category?");
        ui->answerALabel->setText("Amazon Prime subscription"); // answer A
        ui->answerBLabel->setText("Rent");
        ui->answerCLabel->setText("Transportation");
        ui->answerDLabel->setText("Groceries");
        extraPageSetup();
    }

    //
    // ---------- Section 1, Quiz 2 ----------
    //

    if (currSection == 1 && currQuiz == 2 && currQuestion == 1)
    {
        ui->questionLabel->setText("The biggest budget cuts can often be made in which category?");
        ui->answerALabel->setText("Must-haves"); // answer A
        ui->answerBLabel->setText("Buffer category");
        ui->answerCLabel->setText("Savings/Debt Payments");
        ui->answerDLabel->setText("None of the above");
        extraPageSetup();
    }

    if (currSection == 1 && currQuiz == 2 && currQuestion == 2)
    {
        ui->questionLabel->setText("What is the biggest expense in most people’s budget?");
        ui->answerALabel->setText("Food");
        ui->answerBLabel->setText("Netflix");
        ui->answerCLabel->setText("Rent"); // answer C
        ui->answerDLabel->setText("Car repairs");
        extraPageSetup();
    }

    if (currSection == 1 && currQuiz == 2 && currQuestion == 3)
    {
        ui->questionLabel->setText("Which type of savings can be used to cover lower-cost unexpected events?");
        ui->answerALabel->setText("Retirement Savings Fund");
        ui->answerBLabel->setText("Mutual Fund");
        ui->answerCLabel->setText("401K");
        ui->answerDLabel->setText("Rainy Day Fund"); // answer D
        extraPageSetup();
    }

    //
    // ---------- Section 2, Quiz 1 ----------
    //

    if (currSection == 2 && currQuiz == 1 && currQuestion == 1)
    {
        ui->questionLabel->setText("Which term represents the rising of prices leading to a decrease in buying power per unit of currency?");
        ui->answerALabel->setText("Stagnation");
        ui->answerBLabel->setText("Inflation"); // answer B
        ui->answerCLabel->setText("Recession");
        ui->answerDLabel->setText("Deflation");
        extraPageSetup();
    }

    if (currSection == 2 && currQuiz == 1 && currQuestion == 2)
    {
        ui->questionLabel->setText("What is a 401K?");
        ui->answerALabel->setText("A small low-interest fund capped at $10,000 used for small emergencies like a car repair or medical expense");
        ui->answerBLabel->setText("A retirement plan exclusive to US military veterans");
        ui->answerCLabel->setText("A government sponsered savings account for low-income earners");
        ui->answerDLabel->setText("A company sponsered retirement account that employees can contribute part of their income to"); // answer D
        extraPageSetup();
    }

    if (currSection == 2 && currQuiz == 1 && currQuestion == 3)
    {
        ui->questionLabel->setText("The point of investing is to...");
        ui->answerALabel->setText("have money saved up for a rainy day");
        ui->answerBLabel->setText("hope your selected cryptocurrency takes off so you can retire next year");
        ui->answerCLabel->setText("make money off your money you currently have and outpace inflation"); // answer C
        ui->answerDLabel->setText("put your money somewhere else so you can't spend it all");
        extraPageSetup();
    }

    //
    // ---------- Section 2, Quiz 2 ----------
    //

    if (currSection == 2 && currQuiz == 2 && currQuestion == 1)
    {
        ui->questionLabel->setText("If you have $1000 that, 'compounds annually' at 10%, then in two years it will be...");
        ui->answerALabel->setText("$1210"); // answer A
        ui->answerBLabel->setText("$1100");
        ui->answerCLabel->setText("$1200");
        ui->answerDLabel->setText("$1110");
        extraPageSetup();
    }

    if (currSection == 2 && currQuiz == 2 && currQuestion == 2)
    {
        ui->questionLabel->setText("What is the average annual growth rate of the S&P 500 ?");
        ui->answerALabel->setText("4-5%");
        ui->answerBLabel->setText("10-11%"); // answer B
        ui->answerCLabel->setText("3-4%");
        ui->answerDLabel->setText("17-19%");
        extraPageSetup();
    }

    if (currSection == 2 && currQuiz == 2 && currQuestion == 3)
    {
        ui->questionLabel->setText("What determines the price of stocks broadly speaking?");
        ui->answerALabel->setText("Supply and demand"); // answer A
        ui->answerBLabel->setText("The Intercontinental Exchange");
        ui->answerCLabel->setText("The legislative branch");
        ui->answerDLabel->setText("The New York Stock Exchange");
        extraPageSetup();
    }
}

void View::extraPageSetup()
{
    ui->quizPageNum->setText(QString::fromStdString(std::to_string(currQuestion)));
    ui->answerAButton->setEnabled(true);
    ui->answerBButton->setEnabled(true);
    ui->answerCButton->setEnabled(true);
    ui->answerDButton->setEnabled(true);
}

void View::disableAnswerButtons()
{
    ui->answerAButton->setEnabled(false);
    ui->answerBButton->setEnabled(false);
    ui->answerCButton->setEnabled(false);
    ui->answerDButton->setEnabled(false);
}

/**
* @brief View::buttonA_slot
*/
void View::buttonA_slot()
{
    userMoves.push_back('A');
    ui->answerAButton->setStyleSheet("background-color: red");
    setProgressBar();
    disableAnswerButtons();
    if (currSection == 1 && currQuiz == 1)
    {
        if (userMoves[currQuestion - 1] == section1Quiz1Answers[currQuestion - 1])
        {
             ui->answerAButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 1 && currQuiz == 2)
    {
        if (userMoves[currQuestion - 1] == section1Quiz2Answers[currQuestion - 1])
        {
             ui->answerAButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 2 && currQuiz == 1)
    {
        if (userMoves[currQuestion - 1] == section2Quiz1Answers[currQuestion - 1])
        {
             ui->answerAButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 2 && currQuiz == 2)
    {
        if (userMoves[currQuestion - 1] == section2Quiz2Answers[currQuestion - 1])
        {
             ui->answerAButton->setStyleSheet("background-color: green");
        }
    }
}
/**
* @brief View::buttonB_slot
*/
void View::buttonB_slot()
{
    userMoves.push_back('B');
    ui->answerBButton->setStyleSheet("background-color: red");
    setProgressBar();
    disableAnswerButtons();
    if (currSection == 1 && currQuiz == 1)
    {
        if (userMoves[currQuestion - 1] == section1Quiz1Answers[currQuestion - 1])
        {
             ui->answerBButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 1 && currQuiz == 2)
    {
        if (userMoves[currQuestion - 1] == section1Quiz2Answers[currQuestion - 1])
        {
             ui->answerBButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 2 && currQuiz == 1)
    {
        if (userMoves[currQuestion - 1] == section2Quiz1Answers[currQuestion - 1])
        {
             ui->answerBButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 2 && currQuiz == 2)
    {
        if (userMoves[currQuestion - 1] == section2Quiz2Answers[currQuestion - 1])
        {
             ui->answerBButton->setStyleSheet("background-color: green");
        }
    }
}
/**
* @brief View::buttonC_slot
*/
void View::buttonC_slot()
{
    userMoves.push_back('C');
    ui->answerCButton->setStyleSheet("background-color: red");
    setProgressBar();
    disableAnswerButtons();
    if (currSection == 1 && currQuiz == 1)
    {
        if (userMoves[currQuestion - 1] == section1Quiz1Answers[currQuestion - 1])
        {
             ui->answerCButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 1 && currQuiz == 2)
    {
        if (userMoves[currQuestion - 1] == section1Quiz2Answers[currQuestion - 1])
        {
             ui->answerCButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 2 && currQuiz == 1)
    {
        if (userMoves[currQuestion - 1] == section2Quiz1Answers[currQuestion - 1])
        {
             ui->answerCButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 2 && currQuiz == 2)
    {
        if (userMoves[currQuestion - 1] == section2Quiz2Answers[currQuestion - 1])
        {
             ui->answerCButton->setStyleSheet("background-color: green");
        }
    }
}

/**
* @brief View::buttonD_slot
*/
void View::buttonD_slot()
{
    userMoves.push_back('D');
    ui->answerDButton->setStyleSheet("background-color: red");
    setProgressBar();
    disableAnswerButtons();
    if (currSection == 1 && currQuiz == 1)
    {
        if (userMoves[currQuestion - 1] == section1Quiz1Answers[currQuestion - 1])
        {
             ui->answerDButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 1 && currQuiz == 2)
    {
        if (userMoves[currQuestion - 1] == section1Quiz2Answers[currQuestion - 1])
        {
             ui->answerDButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 2 && currQuiz == 1)
    {
        if (userMoves[currQuestion - 1] == section2Quiz1Answers[currQuestion - 1])
        {
             ui->answerDButton->setStyleSheet("background-color: green");
        }
    }
    if (currSection == 2 && currQuiz == 2)
    {
        if (userMoves[currQuestion - 1] == section2Quiz2Answers[currQuestion - 1])
        {
             ui->answerDButton->setStyleSheet("background-color: green");
        }
    }
}

/**
* @brief View::calculateQuizScore
*/
void View::calculateQuizScore(){
    int finalScore = 0;
    if (currSection == 1 && currQuiz == 1)
    {
        for (unsigned int i = 0; i < section1Quiz1Answers.size(); i++)
        {
            if (userMoves[i] == section1Quiz1Answers[i])
            {
                finalScore++;
            }
        }
    }
    if (currSection == 1 && currQuiz == 2)
    {
        for (unsigned int i = 0; i < section1Quiz2Answers.size(); i++)
        {
            if (userMoves[i] == section1Quiz2Answers[i])
            {
                finalScore++;
            }
        }
    }
    if (currSection == 2 && currQuiz == 1)
    {
        for (unsigned int i = 0; i < section2Quiz1Answers.size(); i++)
        {
            if (userMoves[i] == section2Quiz1Answers[i])
            {
                finalScore++;
            }
        }
    }
    if (currSection == 2 && currQuiz == 2)
    {
        for (unsigned int i = 0; i < section2Quiz2Answers.size(); i++)
        {
            if (userMoves[i] == section2Quiz2Answers[i])
            {
                finalScore++;
            }
        }
    }
    quizScore = finalScore;
}



/**
* @brief View::setProgressBar
*/
void View::setProgressBar()
{
   float progress =  (float)currQuestion/(float)getNumberOfQuestion();
   ui->quizProgressBar->setValue(progress*100);
}

/**
 * @brief View::unlockNextModuleOrQuiz
 */
void View::unlockNextModuleOrQuiz()
{
    if (currSection == 1)
    {
        switch (currModule)
        {
        case 1:
            ui->section1Module2Button->setEnabled(true);
            break;
        case 2:
            ui->section1Quiz1Button->setEnabled(true);
            break;
        case 3:
            ui->section1Module4Button->setEnabled(true);
            break;
        case 4:
            ui->section1Quiz2Button->setEnabled(true);
            break;
        }
        switch (currQuiz)
        {
        case 1:
            ui->section1Module3Button->setEnabled(true);
            break;
        case 2:
            ui->section2Module1Button->setEnabled(true);
            break;
        }
    }
    else if (currSection == 2)
    {
        switch (currModule)
        {
        case 1:
            ui->section2Module2Button->setEnabled(true);
            break;
        case 2:
            ui->section2Quiz1Button->setEnabled(true);
            break;
        case 3:
            ui->section2Module4Button->setEnabled(true);
            break;
        case 4:
            ui->section2Quiz2Button->setEnabled(true);
            break;
        }
        switch (currQuiz)
        {
        case 1:
            ui->section2Module3Button->setEnabled(true);
            break;
        }
    }
}



/**
 * @brief View::calculateCompoundInterest_slot
 */
void View::calculateCompoundInterest_slot()
{
    bool validInput;
    double initialAmount = ui->InitialAmountLineEdit->text().toDouble(&validInput);
    double interestRate = ui->interestRateLineEdit->text().toDouble(&validInput);
    double compoundingFrequency = ui->compoundingFrequencyLineEdit->text().toDouble(&validInput);
    double timeInvested = ui->timeInvestedLineEdit->text().toDouble(&validInput);
    double monthlyContributions = ui->monthlyContributionsLineEdit->text().toDouble(&validInput);

    if (initialAmount <= -1 || interestRate <= 0 || compoundingFrequency <= 0
                           || timeInvested <= 0 || monthlyContributions <= -1)
    {
        validInput = false;
    }
    if (!validInput)
    {
        QMessageBox::information(this, tr("Invalid Text Entry"), tr("Please enter a positive number for every entry"), QMessageBox::Ok);
        return;
    }

    ui->finalAmountLabel->setText("Final Amount: ");
    ui->earningsFromInterestLabel->setText("Amount earned from interest: ");
    ui->totalContributionsDisplayLabel->setText(QString::number(monthlyContributions * 12 * timeInvested));
    emit calculateCompoundInterest_signal(initialAmount, interestRate, compoundingFrequency, timeInvested, monthlyContributions);
}

/**
 * @brief View::updateFinalInvestedAmount_slot
 * @param finalAmount
 * @param earningsFromInterest
 */
void View::updateFinalInvestedAmount_slot(double finalAmount, double earningsFromInterest)
{
    QString finalAmountString = QString::number(finalAmount, 'f', 2);
    QString earningsFromInterestString = QString::number(earningsFromInterest, 'f', 2);
    ui->finalAmountDisplayLabel->setText(finalAmountString);
    ui->amountEarnedFromInterestDisplayLabel->setText(earningsFromInterestString);
}

/**
 * @brief View::calculateBudgetSummaries_slot
 */
void View::calculateBudgetSummaries_slot()
{
    bool ok;
    double housingCategoryInput = ui->housingLineEdit->text().toDouble(&ok);
    double utiltiesCategoryInput = ui->utilitiesLineEdit->text().toDouble(&ok);
    double foodCategoryInput = ui->foodLineEdit->text().toDouble(&ok);
    double personalCareCategoryInput = ui->personalCareLineEdit->text().toDouble(&ok);
    double insuranceCategoryInput = ui->insuranceLineEdit->text().toDouble(&ok);
    double transportationCategoryInput = ui->transportationLineEdit->text().toDouble(&ok);
    double givingCategoryInput = ui->givingLineEdit->text().toDouble(&ok);
    double savingsCategoryInput = ui->savingsLineEdit->text().toDouble(&ok);
    double entertainmentCategoryInput = ui->entertainmentLineEdit->text().toDouble(&ok);
    double medicalCategoryInput = ui->medicalLineEdit->text().toDouble(&ok);
    double miscCategoryInput = ui->miscLineEdit->text().toDouble(&ok);

    if (!ok)
    {
        QMessageBox::information(this, tr("Invalid Text Entry"), tr("An input for a budget category was not a valid number. Please review and try again."), QMessageBox::Ok);
        return;
    }

    emit updateBudgetCategoryEntries_signal(housingCategoryInput, utiltiesCategoryInput, foodCategoryInput, personalCareCategoryInput,
                                            insuranceCategoryInput, transportationCategoryInput, givingCategoryInput, savingsCategoryInput,
                                            entertainmentCategoryInput, medicalCategoryInput, miscCategoryInput);
}

/**
 * @brief View::calculateMonthlyIncome_slot
 */
void View::calculateMonthlyIncome_slot()
{
    bool ok;
    double monthlyGrossIncome = ui->grossIncomeLineEdit->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::information(this, tr("Invalid Text Entry"), tr("The value input for the monthly gross income was not a valid number. Please try again."), QMessageBox::Ok);
        return;
    }
    ui->calculateBudgetSummariesButton->setDisabled(false);
    ui->populateSuggestedCateogoriesButton->setDisabled(false);
    emit sendMonthlyGrossIncome_signal(monthlyGrossIncome);
}

/**
 * @brief View::populateSuggestedCategories_slot
 */
void View::populateCategories_slot(double housing, double utilities, double food, double personalCare, double transportation, double insurance, double giving, double saving, double entertainment, double medical, double misc)
{
    ui->housingLineEdit->clear();
    ui->housingLineEdit->insert(QString::number(housing));
    ui->utilitiesLineEdit->clear();
    ui->utilitiesLineEdit->insert(QString::number(utilities));
    ui->foodLineEdit->clear();
    ui->foodLineEdit->insert(QString::number(food));
    ui->personalCareLineEdit->clear();
    ui->personalCareLineEdit->insert(QString::number(personalCare));
    ui->transportationLineEdit->clear();
    ui->transportationLineEdit->insert(QString::number(transportation));
    ui->insuranceLineEdit->clear();
    ui->insuranceLineEdit->insert(QString::number(insurance));
    ui->givingLineEdit->clear();
    ui->givingLineEdit->insert(QString::number(giving));
    ui->savingsLineEdit->clear();
    ui->savingsLineEdit->insert(QString::number(saving));
    ui->entertainmentLineEdit->clear();
    ui->entertainmentLineEdit->insert(QString::number(entertainment));
    ui->medicalLineEdit->clear();
    ui->medicalLineEdit->insert(QString::number(medical));
    ui->miscLineEdit->clear();
    ui->miscLineEdit->insert(QString::number(misc));

}

/**
 * @brief View::updateMonthlyIncome_slot
 * @param expectedWitholdings
 * @param netMonthlyIncome
 */
void View::updateMonthlyIncome_slot(double expectedWitholdings, double netMonthlyIncome)
{
    ui->calculatedExpectedWitholdingsLabel->setText(QString::number(expectedWitholdings));
    ui->monthlyIncomeCalculatedLabel->setText(QString::number(netMonthlyIncome));
}

/**
 * @brief View::updateSummaries_slot
 * @param netMonthlyIncome
 * @param totalMonthlyExpenses
 */
void View::updateSummaries_slot(double netMonthlyIncome, double totalMonthlyExpenses)
{
    ui->showPercentagesCheckBox->setDisabled(false);
    ui->monthlySummaryNetIncomeDisplayLabel->setText(QString::number(netMonthlyIncome));
    ui->monthlySummaryTotalExpensesDisplayLabel->setText(QString::number(totalMonthlyExpenses));
    ui->monthlySummaryDiscretionaryIncomeDisplayLabel->setText(QString::number(netMonthlyIncome - totalMonthlyExpenses));

    ui->yearlySummaryNetIncomeDisplayLabel->setText(QString::number(netMonthlyIncome * 12));
    ui->yearlySummaryTotalExpensesDisplayLabel->setText(QString::number(totalMonthlyExpenses * 12));
    ui->yearlySummaryDiscretionaryIncomeDisplayLabel->setText(QString::number((netMonthlyIncome * 12) - (totalMonthlyExpenses * 12)));
}

/**
 * @brief View::showPercentages_slot
 */
void View::showPercentages_slot(){
    if (ui->showPercentagesCheckBox->isChecked())
    {
        ui->calculateBudgetSummariesButton->setDisabled(true);
        ui->populateSuggestedCateogoriesButton->setDisabled(true);

        ui->money1->setVisible(false);
        ui->money2->setVisible(false);
        ui->money3->setVisible(false);
        ui->money4->setVisible(false);
        ui->money5->setVisible(false);
        ui->money6->setVisible(false);
        ui->money7->setVisible(false);
        ui->money8->setVisible(false);
        ui->money9->setVisible(false);
        ui->money10->setVisible(false);
        ui->money11->setVisible(false);

        ui->percent->setVisible(true);
        ui->percent_2->setVisible(true);
        ui->percent_3->setVisible(true);
        ui->percent_4->setVisible(true);
        ui->percent_5->setVisible(true);
        ui->percent_6->setVisible(true);
        ui->percent_7->setVisible(true);
        ui->percent_8->setVisible(true);
        ui->percent_9->setVisible(true);
        ui->percent_10->setVisible(true);
        ui->percent_11->setVisible(true);

        ui->housingLineEdit->setAlignment(Qt::AlignRight);
        ui->utilitiesLineEdit->setAlignment(Qt::AlignRight);
        ui->foodLineEdit->setAlignment(Qt::AlignRight);
        ui->personalCareLineEdit->setAlignment(Qt::AlignRight);
        ui->insuranceLineEdit->setAlignment(Qt::AlignRight);
        ui->medicalLineEdit->setAlignment(Qt::AlignRight);
        ui->miscLineEdit->setAlignment(Qt::AlignRight);
        ui->transportationLineEdit->setAlignment(Qt::AlignRight);
        ui->entertainmentLineEdit->setAlignment(Qt::AlignRight);
        ui->savingsLineEdit->setAlignment(Qt::AlignRight);
        ui->givingLineEdit->setAlignment(Qt::AlignRight);

        emit getCategoryPercentages_signal();
    }
    else
    {
        ui->calculateBudgetSummariesButton->setDisabled(false);
        ui->populateSuggestedCateogoriesButton->setDisabled(false);

        ui->money1->setVisible(true);
        ui->money2->setVisible(true);
        ui->money3->setVisible(true);
        ui->money4->setVisible(true);
        ui->money5->setVisible(true);
        ui->money6->setVisible(true);
        ui->money7->setVisible(true);
        ui->money8->setVisible(true);
        ui->money9->setVisible(true);
        ui->money10->setVisible(true);
        ui->money11->setVisible(true);

        ui->percent->setVisible(false);
        ui->percent_2->setVisible(false);
        ui->percent_3->setVisible(false);
        ui->percent_4->setVisible(false);
        ui->percent_5->setVisible(false);
        ui->percent_6->setVisible(false);
        ui->percent_7->setVisible(false);
        ui->percent_8->setVisible(false);
        ui->percent_9->setVisible(false);
        ui->percent_10->setVisible(false);
        ui->percent_11->setVisible(false);

        ui->housingLineEdit->setAlignment(Qt::AlignLeft);
        ui->utilitiesLineEdit->setAlignment(Qt::AlignLeft);
        ui->foodLineEdit->setAlignment(Qt::AlignLeft);
        ui->personalCareLineEdit->setAlignment(Qt::AlignLeft);
        ui->insuranceLineEdit->setAlignment(Qt::AlignLeft);
        ui->medicalLineEdit->setAlignment(Qt::AlignLeft);
        ui->miscLineEdit->setAlignment(Qt::AlignLeft);
        ui->transportationLineEdit->setAlignment(Qt::AlignLeft);
        ui->entertainmentLineEdit->setAlignment(Qt::AlignLeft);
        ui->savingsLineEdit->setAlignment(Qt::AlignLeft);
        ui->givingLineEdit->setAlignment(Qt::AlignLeft);

        emit getCategoryDollarAmounts_signal();
    }
}
