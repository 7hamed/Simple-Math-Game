#include <iostream>
#include <ctime>
using namespace std;

enum enLevelType { Easy=1 , Medium=2 , Hard=3 , MixLevel=4 };
enum enOperationType { Add=1 , Subtract=2 , Multiply=3 , Divide=4 , MixOperation=5 };

string levelTypeToString(enLevelType level)
{
    string arrLevel[4] = {"Eesy", "Medium", "Hard", "Mix"};
    return arrLevel[level -1];
}

string operationTypeToString(enOperationType op)
{
    string arrOperationSymbol[5] = {"+", "-", "*", "/", "Mix"};
    return arrOperationSymbol[op -1];
}

struct stQuestion{
    int number1;
    int number2;
    enLevelType level;
    enOperationType operation; // can't be MIX
    int result;
    int playerAnswer;
    bool isAnswerRight;
};

struct stGame{
    stQuestion arrQuestions[50];
    short numberOfQuestions;
    enLevelType questionsLevel;
    enOperationType questionsOperation; // can be MIX type
    short numberOfRightAnswers = 0;  // inistial valeu to the struct, dont need to do it in main code
    short numberOfWrongAnswers = 0;
    bool isPass;
};

int randomNumber(int From, int To)
{
    return rand()%(To - From +1) + From ;
}

short readNumberOfQuestions()
{
    short num;
    do{
        cout << "enter Number Of Questions [1 - 50] : ";
        cin >> num;
    }while(num < 1 || num > 50);

    return num;
}

enLevelType readLevelOfQuestions()
{
    short num;
    do{
        cout << "enter the Level of Questions [ 1-Easy | 2-Med | 3-Hard | 4-Mix ] : ";
        cin >> num;
    }while(num < 1 || num > 4);

    return (enLevelType) num;
}

enOperationType readOperationOfQuestions()
{
    short num;
    do{
        cout << "enter the Operation of Questions [ 1-Add | 2-Sub | 3-MUltiply | 4-Divide | 5-Mix ] : ";
        cin >> num;
    }while(num < 1 || num > 5);

    return (enOperationType) num;
}

int simpleCalculator(int num1, int num2, enOperationType op)
{
    switch(op)
    {
        case enOperationType::Add:
            return num1 + num2 ;

        case enOperationType::Subtract:
            return num1 - num2 ;

        case enOperationType::Multiply:
            return num1 * num2 ;
        
        case enOperationType::Divide:
            return num1 / num2 ;
    }
}

stQuestion generateAQuestion(enLevelType level, enOperationType op)
{
    stQuestion question;
    
    if(level == enLevelType::MixLevel)
        level = (enLevelType) randomNumber(1, 3);
    
    if(op == enOperationType::MixOperation)
        op = (enOperationType) randomNumber(1, 4);

    question.operation = op;
    question.level = level;
    
    switch(question.level) // generate a question by level, and calculate the result
    {
        case enLevelType::Easy:
            question.number1 = randomNumber(1, 9);
            question.number2 = randomNumber(1, 9);
            question.result = simpleCalculator(question.number1 , question.number2 , question.operation);
            return question;
        
        case enLevelType::Medium:
            question.number1 = randomNumber(10, 50);
            question.number2 = randomNumber(10, 50);
            question.result = simpleCalculator(question.number1 , question.number2 , question.operation);
            return question;

        case enLevelType::Hard:
            question.number1 = randomNumber(51, 100);
            question.number2 = randomNumber(51, 100);
            question.result = simpleCalculator(question.number1 , question.number2 , question.operation);
            return question;
    }
}

void generateAllQuestions(stGame &game)
{
    for(short i=0 ; i<game.numberOfQuestions ; i++)
    {
        game.arrQuestions[i] = generateAQuestion(game.questionsLevel, game.questionsOperation);
    }
}

void printAQuesion(stGame game, short questionNo)
{
    cout << "[" << questionNo +1 << "/" << game.numberOfQuestions << "]\t";
    cout << game.arrQuestions[questionNo].number1 << " ";
    cout << operationTypeToString(game.arrQuestions[questionNo].operation) << " ";
    cout << game.arrQuestions[questionNo].number2 << " = ? ";
    
    cout << ", enter the Result : ";
}

int readAnswer()
{
    int num;
    cin >> num;
    return num;
}

void setScreenColor(bool condition)
{
    if (condition)
        system("color 2F"); //turn screen to Green
    else
    {
        system("color 4F"); //turn screen to Red
        cout << "\a";
    }
}

void correctQuestionAnswer(stGame &game, short questionNo)
{
    if(game.arrQuestions[questionNo].playerAnswer == game.arrQuestions[questionNo].result)
    {
        game.arrQuestions[questionNo].isAnswerRight = true;
        game.numberOfRightAnswers ++ ;
        cout << "   You Done Well :)\n" << endl;
    }
    else
    {
        game.arrQuestions[questionNo].isAnswerRight = false;
        game.numberOfWrongAnswers ++ ;
        cout << "   Sorry, the Correct Answer is = " << game.arrQuestions[questionNo].result << endl << endl;
    }

    setScreenColor(game.arrQuestions[questionNo].isAnswerRight);
}

void askAndCorrectAllQuestions(stGame &game)
{
    for(short i=0 ; i<game.numberOfQuestions ; i++)
    {
        printAQuesion(game, i);

        game.arrQuestions[i].playerAnswer = readAnswer();
        
        correctQuestionAnswer(game, i);
    }
    
    game.isPass = (game.numberOfRightAnswers >= game.numberOfWrongAnswers) ; // is pass or fail by bool
}

string getFinalResultText(bool condition)
{
    if(condition)
        return "PASS :)";
    else
        return "FAIL :(";
}

void printResultsGame(stGame game)
{
    cout << "\n\t______________________________\n";
    cout << "\t    Final Result is " << getFinalResultText(game.isPass);
    cout << "\n\t______________________________\n";
    cout << "\tNumber of questions : " << game.numberOfQuestions << endl;
    cout << "\tLevel of Questions  : " << levelTypeToString(game.questionsLevel) << endl;
    cout << "\tOperation           : " << operationTypeToString(game.questionsOperation) << endl;
    cout << "\tNumber of Rigth Answers : " << game.numberOfRightAnswers << endl;
    cout << "\tNumber of Wrong Answers : " << game.numberOfWrongAnswers << endl;
    cout << "\t______________________________\n";
}

void resetScreen()
{
    system("cls");
    system("color 0F");
}

void startGame()
{
    stGame game;

    resetScreen();

    game.numberOfQuestions = readNumberOfQuestions();
    game.questionsLevel = readLevelOfQuestions();
    game.questionsOperation = readOperationOfQuestions();

    generateAllQuestions(game);
    askAndCorrectAllQuestions(game);
    printResultsGame(game);
}

int main(){

    srand((unsigned)time(NULL)); // set random seed
    
    char answer;
    do{
    startGame(); // start the Math game

    cout << "  Do you want play again [ y-YES | n-NO ] : ";
    cin >> answer;
    }while(answer == 'y'); // to play again

    resetScreen();

    return 0;
}