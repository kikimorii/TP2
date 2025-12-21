#include "sign.h"
#include <fstream>
#include <vector>
#include <string>

void FirstInterrogativeThenExclamation()
{
    std::ifstream file("sentences.txt");
    std::vector<std::string> arrOfInterrogativeSentences;
    std::vector<std::string> arrOfExclamationSentences;
    char currentSymbol;
    std::string currentSentence;
    file >> currentSymbol;
    currentSentence += currentSymbol;
    while (!file.eof())
    {
        file >> currentSymbol;
        currentSentence += currentSymbol;
        if (currentSymbol == '?' && currentSentence != "?")
        {
            arrOfInterrogativeSentences.emplace_back(currentSentence);
            currentSentence = "";
        }
        else if (currentSymbol == '!' && currentSentence != "!")
        {
            arrOfExclamationSentences.emplace_back(currentSentence);
            currentSentence = "";
        }
    }
    
    for (std::string& string : arrOfInterrogativeSentences)
    {
        std::cout << string << std::endl;
    }
    for (std::string& string : arrOfExclamationSentences)
    {
        std::cout << string << std::endl;
    }
}

int main()
{
    std::cout << "Commands:" << std::endl;
    std::cout << "1 [firstName] [lastName] [day] [month] [year] [zodiac] : create new sign" << std::endl;
    std::cout << "2 [index] : delete sign by index" << std::endl;
    std::cout << "3 [index] [firstName] [lastName] [day] [month] [year] [zodiac] : update sign by index" << std::endl;
    std::cout << "4 [index] : print sign by index" << std::endl;
    std::cout << "5 [zodiac] : print all signs with sign.zodiac=zodiac" << std::endl;
    std::cout << "6 : print all signs" << std::endl;
    std::cout << "7 [filename] : display all sentences from file with name=[filename]" << std::endl;
    std::cout << "8 : quit" << std::endl;
    
    SignContainer signContainer;
    int command = 0;
    while (command != 8)
    {
        std::cin >> command;
        switch (command)
        {
            case 1:
            {
                std::string firstName;
                std::string lastName;
                int day = 0;
                int month = 0;
                int year = 0;
                int birthday[3];
                int zodiac = 0;
                std::cin >> firstName >> lastName >> birthday[0] >> birthday[1] >> birthday[2] >> zodiac;
                Sign* sign = new Sign(firstName, lastName, birthday, zodiac);
                signContainer.Add(sign);
                break;
            }
            case 2:
            {
                int index;
                std::cin >> index;
                signContainer.Delete(index);
                break;
            }
            case 3:
            {
                int index;
                std::string firstName;
                std::string lastName;
                int day = 0;
                int month = 0;
                int year = 0;
                int birthday[3];
                int zodiac = 0;
                std::cin >> index >> firstName >> lastName >> birthday[0] >> birthday[1] >> birthday[2] >> zodiac;
                Sign* sign = signContainer.GetSign(index);
                sign->SetFirstName(firstName);
                sign->SetLastName(lastName);
                sign->SetBirthday(birthday);
                sign->SetZodiac(zodiac);
                break;
            }
            case 4:
            {
                int index;
                std::cin >> index;
                signContainer.PrintByIndex(index);
                break;
            }
            case 5:
            {
                int zodiac;
                std::cin >> zodiac;
                signContainer.PrintWithZodiac(zodiac);
                break;
            }
            case 6:
            {
                signContainer.Print();
                break;
            }
            case 7:
            {
                FirstInterrogativeThenExclamation();
                break;
            }
        }
    }
    return 0;
}