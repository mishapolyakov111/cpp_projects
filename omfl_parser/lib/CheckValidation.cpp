#include "CheckValidation.h"

std::string DeleteSpaces(const std::string& str) {
    std::string tmp_str;
    int start_idx = 0;
    int32_t end_idx = str.size() - 1;

    while (str[start_idx] == ' ' or str[start_idx] == '\t' or str[start_idx] == '\r'){
        start_idx++;
    }

    while ((str[end_idx] == ' ' or str[end_idx] == '\t' or str[end_idx] == '\r') and end_idx >= 0){
        end_idx--;
    }

    for (int i = start_idx; i <= end_idx; ++i) {
        tmp_str += str[i];
    }

    return tmp_str;
}

std::string DeleteComments(const std::string& str){
    std::string str_without_comments;
    bool can_be_string = false;
    bool have_comment;
    for (int i = str.size() - 1; i >= 0; --i) {
        if (str[i] == '\"'){
            can_be_string = true;
        }
        if (str[i] == '#' and !can_be_string){
            str_without_comments = str.substr(0, i);
            have_comment = true;
            break;
        }
    }

    if (str_without_comments.empty() and !have_comment){
        return str;
    }

    return str_without_comments;
}

bool CharValid(char c) {
    if (c >= '0' and c <= '9' or
        c == '-' or
        c == '_' or
        c >= 'A' and c <= 'Z' or
        c >= 'a' and c <= 'z') {
        return true;
    }

    return false;
}

std::vector<std::string> SplitArray(const std::string& str){
    std::vector<std::string> splitted_array;
    std::string array = str.substr(1, str.size() - 2);
    array += ',';
    std::string line_to_push;
    std::stack<char> stack;
    bool q = false;

    for (int i = 0; i < array.size(); ++i) {
        if (stack.empty() and array[i] == ',' and !q){
            line_to_push = DeleteSpaces(line_to_push);
            splitted_array.push_back(line_to_push);
            line_to_push = "";
        } else {
            line_to_push += array[i];
            if (array[i] == '\"'){
                q = !q;
            } else if (array[i] == ']' and !q){
                stack.pop();
            } else if (array[i] == '[' and !q){
                stack.push('[');
            }
        }
    }

    return splitted_array;
}

bool IsLineValid(const std::string &str){
    if (DeleteSpaces(str).empty()){
        return true;
    }

    if (SectionValid(str)){
        return true;
    }

    if (str.find('=') == -1){
        return false;
    }

    std::string name = str.substr(0, str.find('='));
    std::string value = str.substr(str.find('=') + 1);

    return IsNameValid(name) and IsValueValid(value);
}

bool IsNameValid(const std::string& name) {
    std::string name_to_check = DeleteSpaces(name);
    if (name_to_check.empty()) {
        return false;
    }
    for (int i = 0; i < name_to_check.size(); ++i) {
        char c = name_to_check[i];
        if (!CharValid(c)){
            return false;
        }
    }

    return true;
}

bool IsValueValid(const std::string& value) {
    std::string value_to_check = DeleteSpaces(value);
    if (value_to_check.empty()){
        return false;
    }

    return StringValid(value_to_check) or
            IntValid(value_to_check) or
            FloatValid(value_to_check) or
            ArrayValid(value_to_check) or
            BoolValid(value_to_check);
}

bool StringValid(const std::string& value) {
    int count = 0;
    for (int i = 0; i < value.size(); ++i) {
        if (value[i] == '\"') {
            count++;
        }
    }

    return count == 2 and value[0] == '\"' and value[value.size() - 1] == '\"';
}

bool IntValid(const std::string& value) {
    if (value.size() == 1){
        return value[0] >= '0' and value[0] <= '9';
    }

    bool valid = true;
    bool valid1 = value[0] == '+' or
                value[0] == '-' or
                value[0] >= '0' and value[0] <= '9';

    for (int i = 1; i < value.size(); ++i) {
        valid = value[i] >= '0' and value[i] <= '9';
        if (!valid) {
            break;
        }
    }

    return valid and valid1;
}

bool IsBracketsCorrect(const std::string& value){
    std::stack<char> stack;
    bool correct = true;
    bool q;
    for (int j = 0; j < value.size(); ++j) {
        if (value[j] == '\"'){
            q = !q;
        } else if (value[j] == '[' and !q) {
            stack.push(value[j]);
        } else if (value[j] == ']' and !q) {
            if (stack.empty()) {
                correct = false;
                break;
            }

            if (stack.top() != '[') {
                correct = false;
                break;
            }
            stack.pop();
        }
    }

    if (!stack.empty()){
        return false;
    }

    return correct;
}

bool ArrayValid(const std::string& value) {
    if (!(value[0] == '[' and value[value.size()-1] == ']')) {
        return false;
    }

    if (!IsBracketsCorrect(value)) {
        return false;
    }

    std::vector <std::string> divided_array = SplitArray(value);

    for (int i = 0; i < divided_array.size(); ++i) {
        if(!IsValueValid(divided_array[i]) and !DeleteSpaces(divided_array[i]).empty()){
            return false;
        }
    }

    return true;
}

bool FloatValid(const std::string& value) {
    int dot_count = 0;
    bool valid;
    bool sign = value[0] == '+' or value[0] == '-';

    if (sign and value.size() < 4){
        return false;
    }
    bool valid1 = value[0] == '+' or
                  value[0] == '-' or
                  value[0] >= '0' and value[0] <= '9';

    for (int i = 1; i < value.size(); ++i) {
        valid = value[i] >= '0' and value[i] <= '9' or value[i] == '.';
        if (value[i] == '.'){
            dot_count++;
        }
    }

    return valid1 and valid and dot_count == 1 and value[value.size() - 1] != '.';
}

bool BoolValid(const std::string& value){
    return value == "false" or value == "true";
}

bool SectionValid(const std::string& section_value){
    std::string value = DeleteSpaces(section_value);
    if (!(value[0] == '[' and value[value.size()-1] == ']')) {
        return false;
    }

    std::string section_name = value.substr(1, value.size() - 2);
    std::string tmp_name;
    bool valid;

    for (int i = 0; i < section_name.size(); ++i) {
        if(section_name[i] == '.'){
            valid = IsNameValid(tmp_name);
            if (!valid){
                return false;
            }
            tmp_name = "";
        } else {
            tmp_name += section_name[i];
        }
    }

    valid = IsNameValid(tmp_name);
    if (!valid){
        return false;
    }

    return true;
}