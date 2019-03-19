#include "answer.h"

Answer::Answer(QObject *parent) : QObject(parent)
{

}

bool operator==(const Answer &lanswer, const Answer &ranswer)
{
    bool ok = false;
    if(lanswer.formula() == ranswer.formula()){
        ok = true;
    }

    return ok;
}

void Answer::setFormula(QString formula)
{
    if (m_formula == formula)
        return;

    m_formula = formula;
    emit formulaChanged(m_formula);
}


