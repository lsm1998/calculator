#ifndef CALCULATOR_LOGIC_H
#define CALCULATOR_LOGIC_H

#include <QObject>
#include <functional>

class CalculatorLogic
{
public:
    ~CalculatorLogic();

    void setEditorFunc(const std::function<void(QString)> &func);

    void append(const QString &str);

    void clear();

    void calculate(const QString &str);

    void calculate();

    bool checkDivideZero();

    static CalculatorLogic& getInstance();

private:
    explicit CalculatorLogic() = default;

private:
    std::function<void(QString)> editorFunc;

    QString showText;

    QString prevText;

    QString symbol;
};

#endif //CALCULATOR_LOGIC_H
