#include "questionbase.h"

QString QuestionBase::_classname = "QuestionBase";

QuestionBase::QuestionBase(QObject *parent) : QObject(parent)
{

}

Question *QuestionBase::question(QString id)
{
    if(m_questionById.contains(id)){
        return m_questionById.value(id);
    }else{
        return nullptr;
    }
}

bool QuestionBase::parseStandardFolders(QMap<QString, QuestionBase *> **bases)
{
    QMap<QString, QuestionBase *> * _bases = new QMap<QString, QuestionBase *>();

    QDir appdir = QCoreApplication::applicationDirPath() + "/share/questions/";
    QStringList filelist = appdir.entryList();

    for(int i=0; i < filelist.count() ; i++){
        QString fname = filelist.at(i);

        if(fname.endsWith(".json")){
            qDebug() << QString("%1::%2 - Found question base file '%3'").arg(_classname).arg(__func__).arg(fname);
            QFile f(appdir.filePath(fname));
            if(f.open(QFile::ReadOnly)){
                QByteArray filecontent = f.readAll();
                QuestionBase * b = decodeUTF8Json(&filecontent);
                if(b){
                    _bases->insert(b->id(), b);
                }else{
                    qDebug() << QString("%1::%2 - Could NOT decode file '%3'").arg(_classname).arg(__func__).arg(fname);
                }
                f.close();
            }else{
                qDebug() << QString("%1::%2 - Could not open question base file '%3'. Skipping.").arg(_classname).arg(__func__).arg(fname);
            }
        }
    }

    *bases = _bases;

    return true;
}

QuestionBase *QuestionBase::decodeUTF8Json(QByteArray *barray)
{
    QuestionBase * base = nullptr;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(*barray, &err);

    if(!doc.isNull()){
        QJsonObject obj = doc.object();

        if(obj["_objectType"] == "questionBase"){
            if(obj.contains("id") && obj.contains("version") && obj.contains("questions")){
                base = new QuestionBase();

                base->setId(obj.value("id").toString("ID inconnu"));
                base->setVersion(obj.value("version").toString("Version inconnu"));
                base->setAuthor(obj.value("author").toString("Auteur inconnu"));

                QJsonArray qArray = obj.value("questions").toArray();

                for(int i=0; i < qArray.size() ; i++){
                    QJsonObject qObj = qArray.at(i).toObject();

                    if( ( qObj.contains("formula") || qObj.contains("question") ) && qObj.contains("difficulty") && qObj.contains("id") && qObj.contains("answers")){
                        Question * q = new Question();

                        QString id = qObj.value("id").toString();
                        int difficulty = qObj.value("difficulty").toInt(-1);
                        QString formula = qObj.value("formula").toString();
                        QString question = qObj.value("question").toString();
                        QJsonArray answersArray = qObj.value("answers").toArray();
                        QString group = qObj.value("group").toString();

                        if((!id.isEmpty()) && (difficulty != -1) && ( (!formula.isEmpty()) || (!question.isEmpty()) ) && (answersArray.size() > 0) ){
                            q->setDifficulty(difficulty);
                            q->setFormula(formula);
                            q->setId(id);
                            q->setQuestion(question);
                            q->setGroup(group);

                            for(int j=0; j < answersArray.size() ; j++){
                                QJsonObject aObj = answersArray.at(j).toObject();

                                if(aObj.contains("formula")){
                                    QString answer_str = aObj.value("formula").toString();

                                    if(!answer_str.isEmpty()){
                                        Answer * a = new Answer();
                                        a->setFormula(answer_str);
                                        q->appendAnswer(a);
                                    }else{
                                        qDebug() << QString("%1::%2 - Answer object for Question at index %3 has 'formula' key empty or invalid. Ignoring Question.").arg(_classname).arg(__func__).arg(i);
                                        delete q;
                                        break;
                                    }
                                }else{
                                    qDebug() << QString("%1::%2 - Answer object for Question at index %3 does not contain necessary key 'formula'. Ignoring Question.").arg(_classname).arg(__func__).arg(i);
                                    delete q;
                                    break;
                                }
                            }

                        base->appendQuestion(q, group);

                        }else{
                            qDebug() << QString("%1::%2 - Could not read mandatory keys for Question at index %3: conversion error. Ignoring.").arg(_classname).arg(__func__).arg(i);
                            delete q;
                        }

                    }else{
                        qDebug() << QString("%1::%2 - Question at index %3 is missing mandatory keys 'formula' OR 'question' / 'difficulty' / 'id' / 'answers'. Ignoring.").arg(_classname).arg(__func__).arg(i);
                    }
                }
            }else{
                qDebug() << QString("%1::%2 - Question base is missing mandatory keys 'id', 'version' and 'questions'.").arg(_classname).arg(__func__);
            }
        }else{
            qDebug() << QString("%1::%2 - Wrong JSON root type.'").arg(_classname).arg(__func__);
        }
    }else{
        qDebug() << QString("%1::%2 - Invalid JSON root document. Parse error: \n %3 (%4)'").arg(_classname).arg(__func__).arg(err.errorString()).arg(err.offset);
    }

    return base;
}

bool QuestionBase::appendQuestion(Question *q, QString group)
{
    if(q){
        m_questionList.append(q);
        m_questionById.insert(q->id(), q);


        if(m_questionListByGroup.contains(q->group())){
            QuestionGroup * g = m_questionListByGroup.value(q->group());
            g->insertQuestion(q);
        }else{
            QuestionGroup * g = new QuestionGroup();
            g->setName(q->group());
            g->insertQuestion(q);

            m_questionListByGroup.insert(g->name(), g);
        }

        return true;
    }else{
        return false;
    }
}

void QuestionBase::setId(QString id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void QuestionBase::setAuthor(QString author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged(m_author);
}

void QuestionBase::setVersion(QString version)
{
    if (m_version == version)
        return;

    m_version = version;
    emit versionChanged(m_version);
}
