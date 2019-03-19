#include "questiongroup.h"

QuestionGroup::QuestionGroup(QObject *parent) : QObject(parent)
{

}

bool QuestionGroup::insertQuestion(Question *q)
{
    if(!q){
        qDebug() << "Could not append Question to QuestionGroup, nullptr!";
        return false;
    }

    m_questionsMap.insert(q->id(), q);
    return true;
}

bool QuestionGroup::removeQuestion(Question *q)
{
    if(!q){
        qDebug() << "Could not remove Question from QuestionGroup, nullptr!";
        return false;
    }

    if(m_questionsMap.contains(q->id())){
        m_questionsMap.remove(q->id());
        return true;
    }else{
        qDebug() << "Could not remove Question from QuestionGroup, it doesn't exist already.";
        return false;
    }
}

bool QuestionGroup::removeQuestion(QString id)
{
    if(m_questionsMap.contains(id)){
        m_questionsMap.remove(id);
        return true;
    }else{
        qDebug() << "Could not remove Question from QuestionGroup, it doesn't exist already.";
        return false;
    }
}

void QuestionGroup::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}
