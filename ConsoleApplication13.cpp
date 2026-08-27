#include <iostream>

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, MixLevel = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

string GetOpTypeSymbol(enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

int RandomNumber(int From, int To)
{
	//Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

string GetQuestionLevelText(enQuestionsLevel QuestionsLevel)
{
	string arrQuestionsLevel[4] = { "Esay","Med","Hard","Mix" };
	return arrQuestionsLevel[QuestionsLevel - 1];
}

short ReadHowManyQuestion()
{
	short NumberOfQuestion;

	do
	{
		cout << "How Many Question do you want to answer: ";
		cin >> NumberOfQuestion;
	} while (NumberOfQuestion < 1 || NumberOfQuestion>10);

	return NumberOfQuestion;
}

enQuestionsLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter Question Level: [1] Easy, [2] Med, [3] Hard, [4] Mix: ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel>4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
	short OperationType;

	do
	{
		cout << "Enter Operation Type: [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix: ";
		cin >> OperationType;
	} while (OperationType < 1 || OperationType>5);

	return (enOperationType)OperationType;
}

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionsLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestion;
	enOperationType OpType;
	enQuestionsLevel QuestionsLevel;
	short NumberOfWrongAnswer = 0;
	short NumberOrRightAnswer = 0;
	bool IsPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

enOperationType GetRandomOperationType()
{
	int OP = RandomNumber(1, 4);
	return (enOperationType)OP;
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionsLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionsLevel == enQuestionsLevel::MixLevel)
	{
		QuestionsLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OperationType == enOperationType::MixOp)
	{
		OperationType = GetRandomOperationType();
	}

	Question.OperationType = OperationType;

	switch (QuestionsLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionsLevel;

		return Question;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionsLevel;

		return Question;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionsLevel;

		return Question;
	}

	return Question;
}

void GenerateQuizzQuestion(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "] \n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n____________" << endl;
}

void SetScreenColor(bool Right)
{
	if (Right)
	{
		system("color 2F");
    }
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswer++;

		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOrRightAnswer++;

		cout << "Right Answer :-) \n";
	}

	cout << "\n";
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.IsPass = (Quizz.NumberOrRightAnswer >= Quizz.NumberOfWrongAnswer);
}

string GetFinalResultText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "___________________________________\n\n";
	cout << "Final Result is " << GetFinalResultText(Quizz.IsPass);
	cout << "\n___________________________________\n\n";
	cout << "Number of Question     : " << Quizz.NumberOfQuestion << endl;
	cout << "Question level         : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type         : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.NumberOrRightAnswer << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswer << endl;
	cout << "___________________________________\n";
}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestion = ReadHowManyQuestion();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuizzQuestion(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResults(Quizz);
}

void ReseltScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ReseltScreen();
		PlayMathGame();

		cout << "\nDo you to play again: Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}