#include "learningpath.h"

LearningPath::LearningPath(QObject *parent)
    : QObject{parent}
{
    // Fill in textData with empty strings so it doesn't throw errors when we add data later on.
    textData.resize(2);
    for (int i = 0; i < 2; i++)
    {
        textData[i].resize(8);
        for (int j = 0; j < 8; j++)
        {
            textData[i][j].resize(10);
        }
    }

    // ---------- Section 1 ----------

    // S1, Module 1

    textData[0][0][0] = "Module 1: Budget Basics.\n\n"
                        "We're going to talk about the fundamentals of budgeting, and how budgeting can help you achieve "
                        "your financial goals, whether it be saving for retirement, creating a rainy day fund, or paying "
                        "off debts.\n\n"
                        "Budgeting might sound restricting, but in reality, budgeting can be incredibly freeing. "
                        "It provides freedom from financial stresses such as worrying how you're going to pay your bills or "
                        "pay off your student loans.";

    textData[0][0][1] = "So how does this work?\n\n"
                        "The idea behind budgeting is to map out all of your spending. This includes rent, food, entertainment, etc. "
                        "Once you understand where all your money is going, you'll realize what a strong sense of confidence "
                        "and security over your financial situation this simple activity gives you.";

    textData[0][0][2] = "One thing to keep in mind before you create your budget is that budgeting is a continous process. Your "
                        "first budget isn't going to be your final version. With that in mind, we'll jump into creating your "
                        "very first budget in the next module.";


    // S1, Module 2

    textData[0][1][0] = "Module 2: Creating Your Budget\n\n"
                        "There are a few simple steps to creating a budget which we’ll explore in the following pages.\n\n";

    textData[0][1][1] = "Step 1: List out your monthly net income. That’s the income you make after taxes. "
                        "This number is the most important part of any budget.\n\n"
                        "Step 2: The next thing to do is to list out your most important expenses, which we can call must-haves. "
                        "Must-haves include rent, utilities, food, insurance/health, transportation, etc";

    textData[0][1][2] = "Step 3: List out wants (subscriptions, hobbies, entertainment, eating out, etc)\n\n"
                        "Step 4: Have a “buffer” category in your budget for unpredictable expenses, such as car repairs, uber, doctor visit, etc.\n\n"
                        "Step 5: The final item in your budget is savings/debt payments.";

    textData[0][1][3] = "Now that you've listed out all your expenses, it's time to determine how much money you want to spend on "
                        "each list item. You should aim to create what's called a zero-sum budget, where all of your net income "
                        "is allocated into one of your categories. If you have some left over, you can add it to the savings category.";

    textData[0][1][4] = "How much left is there to pay off my debt or save money? We will figure out how to increase this "
                        "number in the following modules";


    // S1, Module 3

    textData[0][2][0] = "Module 3: Budgeting Tips And Optimization\n\n"
                        "Sometimes, after creating your budget, you might realize you don't have enough income to allocate "
                        "funds in important areas such as savings or debt payment. In this case, you have to prioritize and cut out spending other "
                        "areas.";

    textData[0][2][1] = "In order to optimize your budget, you have to find places to cut spending. The biggest cuts you can possibly make "
                        "are often in the 'must-haves' category, which include housing, transportation, and food.\n\n"
                        "These changes may include: riding your bike to work every day instead of driving, buying less expensive "
                        "food, or even moving to a cheaper area or smaller house/apartment. For most people, these areas make up a large chunk "
                        "of the budget, which also means they can be the biggest cost savers if one is willing to make a change.";

    textData[0][2][2] = "The other area to look for possible budget cuts is 'wants' which include entertainment, subcription services, "
                        "hobbies, eating out, etc. A big one for many people is eating out and/or food delivery, which can add up to thousands "
                        "of dollars a year if done frequently.";


    // S1, Module 4

    textData[0][3][0] = "Module 4: Savings And Debt Payments\n\n";

    textData[0][3][1] = "There are a few different types of savings.\n\n"
                        "One is a 'rainy day fund' which is money set aside for unexpected and lower-cost expenses, like home "
                        "maintenance or traffic tickets.\n\n"
                        "Another type of savings is an 'emergency fund' which is to cover unexpected events that are stressful and "
                        "costly.\n\n"
                        "Of course, there is also long term retirement savings for when you exit the workforce, which most people "
                        "are familiar with";


    // ---------- Section 2 ----------


    // S2, Module 1

    textData[1][0][0] = "Module 1: Why Invest?\n\n"
                        "The core purpose of investing to make your money work for you by creating more of iteself. This ties "
                        "into the concept of interest, which we'll discuss in more detail later.";

    textData[1][0][1] = "An important concept to understand here is inflation, which is the rising of prices leading to a decrease in buying "
                        "power per unit of currency. The average rate of inflation in the United States is 3.8% a year. That means, "
                        "if I keep $100 in my savings account at 0% appreciation, that money will have lost 38% of its buying power.\n\n"
                        "Luckily, we can combat this by investing our money in the right places, which will lead to it growing faster "
                        "than it gets devalued by inflation.";

    textData[1][0][2] = "Through investing, we can make the most out of our money, beat inflation, and secure our retirement with "
                        "the money we've made often with little to no effort.";

    // S2, Module 2

    textData[1][1][0] = "Module 2: Options For Investing\n\n"
                        "There are a few common ways to invest your money which we'll explore in the following pages.";

    textData[1][1][1] = "The first place to invest your money is a 401K, which some people may be familiar with. A 401K is "
                        "a company-sponsered retirement account that employees can contribute some of their income to. Often, "
                        "employers will match contributions, making it a great idea to max out the amount of money you can "
                        "put into your 401K.";

    textData[1][1][2] = "Another place to invest your money is an index fund. An index fund tracks the performance of a specific "
                        "'index' like the S&P 500 for example, and buys a representative sample of all the stocks in that index. "
                        "This is what's called 'diversification' which lowers the risk because the results aren't just depenent "
                        "on a single stock performing well. An index fund is a great investment option.";

    textData[1][1][3] = "Another way to invest your money is individual stocks that you choose yourself. If you take this route, "
                        "be extremely cautious as this can be far more risky than a investing in a fund. This typically isn't "
                        "reccomended for most investers.";

    // S2, Module 3

    textData[1][2][0] = "Module 3: Interest & Compounding Interest";

    textData[1][2][1] = "In order to beat inflation, we must make over 3.8% annually off our investment. Luckily, this is very doable, "
                        "pretty much any diverse investment portfolio or fund will do better than 3.8% on average. For example, if "
                        "we look at the S&P 500, it has an average annual growth rate of 10.7% per year.";

    textData[1][2][2] = "As mentioned earlier, the point of investing is to make money off your money; to easily grow your wealth.\n\n"
                        "Something amazing about investing is the idea of compound interest. For example, if I have 1,000 dollars that "
                        "compounds annually at 10%, then by next year it will be 1,100. Now, it compounds off the new total, so the "
                        "year after, it will be 1,210 instead of 1,200. Your money grows exponentially.";

    // S2, Module 4

    textData[1][3][0] = "Module 4: The Stock Market\n\n"
                        "We've talked about stocks and funds, but we haven't gone into much detail about how the stock market works "
                        "or how it affects stock prices.\n\n"
                        "We'll discuss this in the following pages.";

    textData[1][3][1] = "The stock market is the aggregation of buyers and sellers of stocks, which represent ownership claims on "
                        "businesses. The price of stocks is broadly determined by supply and demand. If there is a high demand "
                        "for a company's shares, the prices go up, and vice versa.";
}

/**
 * @brief LearningPath::getTextData
 * @return textData
 */
vector<vector<vector<QString>>> LearningPath::getTextData()
{
    return textData;
}
