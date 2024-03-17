#include "CheckValidation.h"

const uint8_t SECTION = 0;
const uint8_t INT = 1;
const uint8_t FLOAT = 2;
const uint8_t STRING = 3;
const uint8_t ARRAY = 4;
const uint8_t BOOL = 5;

class Parameter {
private:
    int8_t type_;
    std::string key_;
    std::string value_;
    std::vector <Parameter*> subsections_{};
public:
    void AddKey(Parameter* p);
    Parameter Get(const std::string& str) const;
    Parameter* AddSection(const std::string& section_name) const;
    Parameter* FindName(const std::string& name) const;

    std::string GetName() const;
    std::vector<Parameter*> GetSubsections() const;
    std::string GetValue() const;
    int8_t GetType() const;
    void SetType();

    bool IsInt() const;
    uint32_t AsInt() const;
    uint32_t AsIntOrDefault(uint32_t val) const;

    bool IsFloat() const;
    float AsFloat() const;
    float AsFloatOrDefault(float val) const;

    bool IsString() const;
    std::string AsString() const;
    std::string AsStringOrDefault(const std::string& str) const;

    bool IsBool() const;
    bool AsBool() const;
    bool AsBoolOrDefault(bool q) const;

    bool IsArray() const;

    bool IsSection() const;

    Parameter operator[](int i) const;

    explicit Parameter(const std::string& key, const std::string& value = "") {
        type_ = -1;
        key_ = key;
        value_ = value;
        SetType();
    }

    Parameter(){
        type_ = -1;
    }
};

void operator<<(std::ostream& os, const Parameter& param);

