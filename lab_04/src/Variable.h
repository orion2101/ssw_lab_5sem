#ifndef LECS_PARS_VARIABLE_H
#define LECS_PARS_VARIABLE_H

#include <string>

class Variable {
public:
    explicit Variable(const std::string &t_type,
                      const std::string &t_value) : type(t_type), value(t_value) {};

    void SetType   (const std::string &type);
    void SetValue  (const std::string &value);
    void SetIsArray(bool isArray);
    void SetRange  (const std::pair<std::string, std::string> &range);

    const std::string &GetType() const;
    const std::string &GetValue() const;
    bool  IsArray() const;
    const std::pair<std::string, std::string> &GetRange() const;

    ~Variable() = default;
private:
    std::string type;
    std::string value;

    bool        isArray {false};
    std::pair<std::string, std::string> range {"", ""};
};


#endif //LECS_PARS_VARIABLE_H
