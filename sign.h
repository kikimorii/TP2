#include <string>
#include <iostream>

class Sign
{
private:
    Sign* nextSign;
    std::string firstName;
    std::string lastName;
    int birthday[3];
    int zodiac;
public:
    Sign();
    Sign(const std::string firstName_, const std::string lastName_, const int(&birthday_)[3], const int zodiac_);
    Sign(const Sign& sign);
    ~Sign();
    Sign* GetNextSign();
    void SetNextSign(Sign* sign);
    std::string GetFirstName() const;
    std::string GetLastName() const;
    void GetBirthday(int* day, int* month, int* year) const;
    int GetZodiac() const;
    void SetFirstName(const std::string& firstName_);
    void SetLastName(const std::string& lastName_);
    void SetBirthday(const int(&birthday_)[3]);
    void SetZodiac(const int zodiac_);
};

std::ostream& operator<<(std::ostream& outStream, const Sign& sign);
std::istream& operator>>(std::istream& inStream, Sign& sign);

class SignContainer
{
private:
    Sign* firstSign;
    Sign* lastSign;
    int length;
public:
    SignContainer();
    SignContainer(Sign* sign);
    SignContainer(const SignContainer& signContainer);
    ~SignContainer();
    void Add(Sign* sign);
    void Delete(int index);
    void Print() const;
    void PrintByIndex(int index) const;
    void PrintWithZodiac(int zodiac) const;
    Sign* GetFirstSign() const;
    Sign* GetSign(int index) const;
};