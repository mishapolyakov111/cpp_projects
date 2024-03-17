#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::string DeleteSpaces(const std::string& str);
std::string DeleteComments(const std::string& str);
std::vector<std::string> SplitArray(const std::string& str);

bool IsLineValid(const std::string &str);

bool IsNameValid(const std::string& name);
bool IsValueValid(const std::string& value);

bool StringValid(const std::string& value);
bool IntValid(const std::string& value);
bool FloatValid(const std::string& value);
bool ArrayValid(const std::string& value);
bool IsBracketsCorrect(const std::string& value);
bool BoolValid(const std::string& value);
bool SectionValid(const std::string& value);