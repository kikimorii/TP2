#include "sign.h"

Sign::Sign()
    : nextSign(nullptr)
    , firstName()
    , lastName()
    , birthday()
    , zodiac()
{
    std::cout << "Object Sign with birthday " << birthday[0] << "/" << birthday[1] << "/" << birthday[2] << " is created!" << std::endl;
}

Sign::Sign(const std::string firstName_, const std::string lastName_, const int(&birthday_)[3], const int zodiac_)
    : nextSign(nullptr)
    , firstName(firstName_)
    , lastName(lastName_)
    , birthday()
    , zodiac(zodiac_)
{
    birthday[0] = birthday_[0];
    birthday[1] = birthday_[1];
    birthday[2] = birthday_[2];
    std::cout << "Object Sign with birthday " << birthday[0] << "/" << birthday[1] << "/" << birthday[2] << " is created!" << std::endl;
}

Sign::Sign(const Sign& sign)
    : nextSign(nullptr)
    , firstName(sign.GetFirstName())
    , lastName(sign.GetLastName())
    , birthday()
    , zodiac(sign.GetZodiac())
{
    sign.GetBirthday(&birthday[0], &birthday[1], &birthday[2]);
    std::cout << "Object Sign with birthday " << birthday[0] << "/" << birthday[1] << "/" << birthday[2] << " is created!" << std::endl;
}

Sign::~Sign()
{
    std::cout << "Object Sign with birthday " << birthday[0] << "/" << birthday[1] << "/" << birthday[2] << " is destroyed!" << std::endl;
}

Sign* Sign::GetNextSign()
{
    return nextSign;
}

void Sign::SetNextSign(Sign* sign)
{
    nextSign = sign;
}

std::string Sign::GetFirstName() const
{
    return firstName;
}

std::string Sign::GetLastName() const
{
    return lastName;
}

void Sign::GetBirthday(int* day, int* month, int* year) const
{
    *day = birthday[0];
    *month = birthday[1];
    *year = birthday[2];
}

int Sign::GetZodiac() const
{
    return zodiac;
}

void Sign::SetFirstName(const std::string& firstName_)
{
    firstName = firstName_;
}

void Sign::SetLastName(const std::string& lastName_)
{
    lastName = lastName_;
}

void Sign::SetBirthday(const int(&birthday_)[3])
{
    birthday[0] = birthday_[0];
    birthday[1] = birthday_[1];
    birthday[2] = birthday_[2];
}

void Sign::SetZodiac(const int zodiac_)
{
    zodiac = zodiac_;
}

std::ostream& operator<<(std::ostream& outStream, const Sign& sign)
{
    outStream << "First name: " << sign.GetFirstName() << std::endl;
    outStream << "Last name: " << sign.GetLastName() << std::endl;
    int day, month, year;
    sign.GetBirthday(&day, &month, &year);
    outStream << "Birthday: " << day << "/" << month << "/" << year << std::endl;
    outStream << "Zodiac: " << sign.GetZodiac() << std::endl;
    return outStream;
}

std::istream& operator>>(std::istream& inStream, Sign& sign)
{
    std::string firstName;
    std::string lastName;
    int birthday[3];
    int zodiac;
    inStream >> firstName >> lastName >> birthday[0] >> birthday[1] >> birthday[2] >> zodiac;
    sign.SetFirstName(firstName);
    sign.SetLastName(lastName);
    sign.SetBirthday(birthday);
    sign.SetZodiac(zodiac);
    return inStream;
}

SignContainer::SignContainer()
    : firstSign(nullptr)
    , lastSign(nullptr)
    , length(0)
{
    std::cout << "Object SignContainer is created!" << std::endl;
}

SignContainer::SignContainer(Sign* sign)
    : firstSign(sign)
    , lastSign(sign)
    , length(1)
{
    std::cout << "Object SignContainer is created!" << std::endl;
}

SignContainer::SignContainer(const SignContainer& signContainer)
    : firstSign(nullptr)
    , lastSign(nullptr)
    , length(0)
{
    Sign* sign = signContainer.GetFirstSign();
    while (sign != nullptr)
    {
        Add(sign);
    }
    std::cout << "Object SignContainer is created!" << std::endl;
}

SignContainer::~SignContainer()
{
    std::cout << "Object SignContainer is destroyed!" << std::endl;
}

void SignContainer::Add(Sign* newSign)
{
    int day, month, year;
    newSign->GetBirthday(&day, &month, &year);
    Sign* prevSign = nullptr;
    Sign* currentSign = firstSign;
    for (int i = 0; i < length; i++)
    {
        int day_, month_, year_;
        currentSign->GetBirthday(&day_, &month_, &year_);
        bool greater = false;
        if (year_ >= year)
        {
            if (year_ == year && month_ >= month)
            {
                if (month_ == month && day_ > day)
                {
                    greater = true;
                }
            }
        }
        if (greater)
        {
            if (prevSign == nullptr)
            {
                newSign->SetNextSign(currentSign);
                firstSign = newSign;
                return;
            }
            prevSign->SetNextSign(newSign);
            newSign->SetNextSign(currentSign);
            length++;
            return;
        }
        currentSign = currentSign->GetNextSign();
    }
    if (length == 0)
    {
        firstSign = newSign;
    }
    else
    {
        lastSign->SetNextSign(newSign);
    }
    lastSign = newSign;
    length++;
}

void SignContainer::Delete(int index)
{
    if (index == 0)
    {
        if (length == 1)
        {
            delete firstSign;
            firstSign = nullptr;
            length--;
            return;
        }
        Sign* newFirstSign = firstSign->GetNextSign();
        delete firstSign;
        firstSign = newFirstSign;
        length--;
        return;
    }
    Sign* signBeforeSignDelete = firstSign;
    for (int i = 0; i < index - 1; i++)
    {
        signBeforeSignDelete = signBeforeSignDelete->GetNextSign();
    }
    if (index == length - 1)
    {
        delete lastSign;
        signBeforeSignDelete->SetNextSign(nullptr);
        lastSign = signBeforeSignDelete;
        length--;
        return;
    }
    Sign* signDelete = signBeforeSignDelete->GetNextSign();
    Sign* signAfterSignDelete = signDelete->GetNextSign();
    delete signDelete;
    signBeforeSignDelete->SetNextSign(signAfterSignDelete);
    length--;
}

void SignContainer::Print() const
{
    if (length == 0)
    {
        std::cout << "Container is empty!" << std::endl;
    }
    Sign* currentSign = firstSign;
    for (int i = 0; i < length; i++)
    {
        std::cout << *currentSign;
        currentSign = currentSign->GetNextSign();
    }
}

void SignContainer::PrintByIndex(int index) const
{
    Sign* currentSign = firstSign;
    for (int i = 0; i < index; i++)
    {
        currentSign = currentSign->GetNextSign();
    }
    std::cout << *currentSign;
}

void SignContainer::PrintWithZodiac(int zodiac) const
{
    if (length == 0)
    {
        std::cout << "Container is empty!" << std::endl;
    }
    Sign* currentSign = firstSign;
    bool isZodiac = false;
    for (int i = 0; i < length; i++)
    {
        if (currentSign->GetZodiac() != zodiac)
        {
            continue;
        }
        std::cout << *currentSign;
        currentSign = currentSign->GetNextSign();
        isZodiac = true;
    }
    if (!isZodiac)
    {
        std::cout << "Elements with zodiac=" << zodiac << " in container doesn't exist!" << std::endl;
    }
}

Sign* SignContainer::GetFirstSign() const
{
    return firstSign;
}

Sign* SignContainer::GetSign(int index) const
{
    Sign* currentSign = firstSign;
    for (int i = 0; i < index; i++)
    {
        currentSign = currentSign->GetNextSign();
    }
    return currentSign;
}