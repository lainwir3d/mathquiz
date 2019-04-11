#include "question.h"

Question::Question(QObject *parent) : QObject(parent)
{
    m_id = "generic_1";
    m_question = "Calculez";
    m_imageUri = "";
    m_formula = "1 + 1";

    m_readOnly = false;
    m_timeLimit_ms = 2000;
    m_difficulty = 1;
}

void Question::appendAnswer(Answer *answer)
{
    if(!answer){
        qDebug() << "Could not append answer, nullptr!";
        return;
    }

    m_answers.append(answer);
}

bool Question::checkAnswer(Answer *answer)
{
    if(!answer){
        qDebug() << "Could not check answer, nullptr!";
        return false;
    }

    bool ok = false;

    for(int i=0; i < m_answers.length() ; i++){
        Answer * a = m_answers.at(i);

        if( *(a) == *(answer) ){
            ok = true;
            break;
        }
    }

    return ok;
}

void Question::setId(QString id)
{
    if(m_readOnly) return;

    if(m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}


void Question::setQuestion(QString question)
{
    if(m_readOnly) return;

    if (m_question == question)
        return;

    m_question = question;
    emit questionChanged(m_question);
}

void Question::setImageUri(QString imageUri)
{
    if(m_readOnly) return;

    if (m_imageUri == imageUri)
        return;

    m_imageUri = imageUri;
    emit imageUriChanged(m_imageUri);
}

void Question::setFormula(QString formula)
{
    if(m_readOnly) return;

    if (m_formula == formula)
        return;

    m_formula = formula;
    emit formulaChanged(m_formula);
}

void Question::setReadOnly(bool readOnly)
{
    if(m_readOnly != readOnly){
        m_readOnly = readOnly;
    }
}

void Question::setTimeLimit_ms(int timeLimit_ms)
{
    if (m_timeLimit_ms == timeLimit_ms)
        return;

    m_timeLimit_ms = timeLimit_ms;
    emit timeLimit_msChanged(m_timeLimit_ms);
}

void Question::setDifficulty(int difficulty)
{
    if (m_difficulty == difficulty)
        return;

    m_difficulty = difficulty;
    emit difficultyChanged(m_difficulty);
}

void Question::setGroup(QString group)
{
    if (m_group == group)
        return;

    m_group = group;
    emit groupChanged(m_group);
}
