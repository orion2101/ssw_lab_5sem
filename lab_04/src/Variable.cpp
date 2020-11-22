#include "Variable.h"



/**
 * @brief Set type for variable
 * @param[in] type - type of variable
 *
 * @return none
 */
void Variable::SetType(const std::string &type) {
    Variable::type = type;
}


/**
 * @brief Set value for variable
 * @param[in] value - value of variable
 *
 * @return none
 */
void Variable::SetValue(const std::string &value) {
    Variable::value = value;
}


/**
 * @brief Set flag of array
 * @param[in] isArray - flag of array
 *
 * @return none
 */
void Variable::SetIsArray(bool isArray) {
    Variable::isArray = isArray;
}


/**
 * @brief Set range of array-variable
 * @param[in] range - pair of range array-variable
 *
 * @return none
 */
void Variable::SetRange(const std::pair<std::string, std::string> &range) {
    Variable::range = range;
}


/**
 * @brief Get type of variable
 * @param none
 *
 * @return type of variable
 */
const std::string &Variable::GetType() const {
    return type;
}


/**
 * @brief Get value of variable
 * @param none
 *
 * @return value of variable
 */
const std::string &Variable::GetValue() const {
    return value;
}


/**
 * @brief Checks whether the variable is an array
 * @param none
 *
 * @return true  - if variable is array
 * @return false - if variable isn't array
 */
bool Variable::IsArray() const {
    return isArray;
}


/**
 * @brief Get range of array-variable
 * @param none
 *
 * @return range (pair) of array-variable
 */
const std::pair<std::string, std::string> &Variable::GetRange() const {
    return range;
}


