

#include <iostream>
using namespace std;
enum enLevel { easy = 1, med = 2, hard = 3, mix = 4 };
enum enOperation { add = 1, sub = 2, mul = 3, Div = 4, mixOp = 5 };
struct stQuestion
{
    short number1;
    short number2;
    enLevel Level;
    enOperation Operation;
    short correctAnswer;
    short playerAnswer;
    bool result = false;
};
struct stQuizz
{
    stQuestion QuestionList[100];
    short numberOfQuestion;
    short numberOfCorrect=0;
    short numberOfWrong=0;
    enLevel level;
    enOperation operation;
    bool isPass = false;
};
int randomNumber(int from, int to)
{
    int random = rand() % (to - from + 1) + from;
    return random;
}
int simpleCalculate(int number1, int number2, enOperation Operation)
{
    switch (Operation)
    {
    case enOperation::add:
        return number1 + number2;
    case enOperation::sub:
        return number1 - number2;
    case enOperation::mul:
        return number1 * number2;
    case enOperation::Div:
        return number1 / number2;
    default:
        return number1 + number2;
    }
}
enLevel readLevel()
{
    int number;
    do
    {
        cout << " your choice : [1]:easy,[2]:med,[3]:hard,[4]:mix  ? \n";
        cin >> number;
    } while (number < 1 || number>4);
    return enLevel(number);
}
enOperation readOperation()
{
    int number;
    do
    {
        cout << " your choice : [1]:add,[2]:sub, [3]:mul, [4]:div [5]:mix ? \n";
        cin >> number;
    } while (number < 1 || number>5);
    return enOperation(number);
}
string levelText(enLevel Level)
{
    string arr[4] = { "easy","med","hard","mix" };
    return arr[Level - 1];
}
string operationText(enOperation operation)
{
    string arr[5] = { "+","-","*","/","mixOp" };
    return arr[operation - 1];
}
stQuestion generateQuestion(enLevel Level, enOperation Operation)
{
    stQuestion Question;
    if (Level == enLevel::mix)
    {
        Level = enLevel(randomNumber(1, 3));
    }
    if (Operation == enOperation::mixOp)
    {
        Operation = enOperation(randomNumber(1, 4));
    }
    Question.Operation = Operation;

    switch (Level)
    {
    case enLevel::easy:
        Question.number1 = randomNumber(1, 10);
        Question.number2 = randomNumber(1, 10);
        Question.correctAnswer = simpleCalculate(Question.number1, Question.number2, Operation);
        Question.Level = Level;
        return Question;
    case enLevel::med:
        Question.number1 = randomNumber(20, 30);
        Question.number2 = randomNumber(20, 30);
        Question.correctAnswer = simpleCalculate(Question.number1, Question.number2, Operation);
        Question.Level = Level;
        return Question;
    case enLevel::hard:
        Question.number1 = randomNumber(30, 50);
        Question.number2 = randomNumber(30, 50);
        Question.correctAnswer = simpleCalculate(Question.number1, Question.number2, Operation);
        Question.Level = Level;
        return Question;
    }
    return Question;

}
void generateQuizzOfQuestion(stQuizz& Quizz)
{
    for (int i = 0; i < Quizz.numberOfQuestion; i++)
    {
        Quizz.QuestionList[i] = generateQuestion(Quizz.level, Quizz.operation);
    }
}
int howManyRound()
{
    int round;
    do
    {
        cout << " how many round  1 to 10 ? \n";
        cin >> round;
    } while (round < 1 || round >10);
    return round;
}
void setScreenColor(bool right)
{
    if (right)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}
short playerChoice()
{
    int result;
    cout << " enter result \n";
    cin >> result;
    return result;
}
void printQuestion(stQuizz Quizz, int number)
{
    cout << " question [" << number + 1 << " / " << Quizz.numberOfQuestion << "] \n";
    cout << Quizz.QuestionList[number].number1 << endl;
    cout << operationText(Quizz.QuestionList[number].Operation) << endl;
    cout << Quizz.QuestionList[number].number2 << endl;
}
string resuult(bool resu)
{
    if (resu)
        return " pass";
    else
        return "fail";
}
void correctNswer(stQuizz& quizz, int numberOfQuestion)
{
    if (quizz.QuestionList[numberOfQuestion].correctAnswer != quizz.QuestionList[numberOfQuestion].playerAnswer)
    {
        quizz.QuestionList[numberOfQuestion].result = false;
        quizz.numberOfWrong++;

        cout << "wrong aswer \n";
        cout << " the right answer : ";
        cout << quizz.QuestionList[numberOfQuestion].correctAnswer << endl;
        cout << "\n\n";
    }
    else
    {
        quizz.QuestionList[numberOfQuestion].result = true;
        quizz.numberOfCorrect++;

        cout << " right aswer \n\n\n";
    }
    setScreenColor(quizz.QuestionList[numberOfQuestion].result);

}

void askUserAndCoreectResult(stQuizz& quizz)
{
    for (int i = 0; i < quizz.numberOfQuestion; i++)
    {
        printQuestion(quizz, i);
        quizz.QuestionList[i].playerAnswer = playerChoice();
        correctNswer(quizz, i);
    }
    quizz.isPass = (quizz.numberOfCorrect >= quizz.numberOfWrong);
}
void printFinalResult(stQuizz& Quizz)
{

    cout << "\n\n_____________________________________________\n\n";
    cout << " final result : " << resuult(Quizz.isPass) << endl;
    cout << " question of quizz : " << Quizz.numberOfQuestion << endl;
    cout << " number of correct answer : " << Quizz.numberOfCorrect << endl;
    cout << " number of wrong answer : " << Quizz.numberOfWrong << endl;
    cout << " operator : " << operationText(Quizz.operation) << endl;
    cout << " level : " << levelText(Quizz.level);


}
void playGame()
{
    stQuizz Quizz;
    Quizz.numberOfQuestion = howManyRound();
    Quizz.level = readLevel();
    Quizz.operation = readOperation();

    generateQuizzOfQuestion(Quizz);
    askUserAndCoreectResult(Quizz);
    printFinalResult(Quizz);
}
void resetScreen()
{
    system("cls");
    system("color 0F");
}
void startGame()
{
    char playAgain = 'y';
    do
    {
        resetScreen();
        playGame();

        cout << "\n\n\n do you want play agein \n";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');



}


int main()
{
    srand((unsigned)time(NULL));
    startGame();
}

