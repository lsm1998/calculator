#include "logic.h"
#include "qdebug.h"

CalculatorLogic::~CalculatorLogic() = default;

CalculatorLogic &CalculatorLogic::getInstance()
{
    static CalculatorLogic instance;
    return instance;
}

void CalculatorLogic::setEditorFunc(const std::function<void(QString)> &func)
{
    this->editorFunc = func;
}

void CalculatorLogic::append(const QString &str)
{
    if (str == "0" && this->showText == "0") // 忽略多次输入0
    {
        return;
    } else if (str == ".")
    {
        if (this->showText.contains(".")) // 忽略已经存在小数点
        {
            return;
        } else if (this->showText.isEmpty())
        {
            this->showText = "0";
        }
    }
    this->showText += str;
    // 去除前面的0
    if (this->showText.lastIndexOf("0") == 0 && this->showText.length() > 1 && !this->showText.contains("."))
    {
        this->showText = this->showText.right(this->showText.length() - 1);
    }
    editorFunc(this->showText);
}

void CalculatorLogic::clear()
{
    this->showText.clear();
    editorFunc(this->showText);
}

void CalculatorLogic::calculate(const QString &str)
{
    if (!this->showText.isEmpty())
    {
        if (str == "+/-")
        {
            this->showText = QString::number(-atof(this->showText.toStdString().c_str()));
        } else if (str == "%")
        {
            this->showText = QString::number(atof(this->showText.toStdString().c_str()) / 100);
        } else if (str == "=")
        {
            this->calculate();
        } else
        {
            this->calculate();
            this->prevText = this->showText;
            this->showText.clear();
            this->symbol = str;
        }
        editorFunc(this->showText);
    }
}

void CalculatorLogic::calculate()
{
    if (this->prevText.isEmpty() || this->symbol.isEmpty() || this->showText.isEmpty())
    {
        return;
    }
    if (this->symbol == "+")
    {
        this->showText = QString::number(
                atof(this->prevText.toStdString().c_str()) + atof(this->showText.toStdString().c_str()));
    } else if (this->symbol == "-")
    {
        this->showText = QString::number(
                atof(this->prevText.toStdString().c_str()) - atof(this->showText.toStdString().c_str()));
    } else if (this->symbol == "*")
    {
        this->showText = QString::number(
                atof(this->prevText.toStdString().c_str()) * atof(this->showText.toStdString().c_str()));
    } else if (this->symbol == "/" && this->checkDivideZero())
    {
        this->showText = QString::number(
                atof(this->prevText.toStdString().c_str()) / atof(this->showText.toStdString().c_str()));
    }
}

bool CalculatorLogic::checkDivideZero()
{
    if (this->showText == "0")
    {
        this->showText = "错误";
        return false;
    }
    return true;
}
