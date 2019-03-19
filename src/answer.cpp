#include "answer.h"

Answer::Answer(QObject *parent) : QObject(parent)
{

}

void Answer::setFormula(QString formula)
{
    if (m_formula == formula)
        return;

    m_formula = formula;
    emit formulaChanged(m_formula);
}


