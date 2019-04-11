#include "quiz.h"

QString Quiz::_classname = "Quiz";

Quiz::Quiz(QObject *parent) : QObject(parent)
{

}

bool Quiz::parseStandardFolders(QMap<QString, Quiz *> **quizs, QMap<QString, QuestionBase *> *base)
{
    QMap<QString, Quiz *> * _quizs = new QMap<QString, Quiz *>();

    QDir appdir = QCoreApplication::applicationDirPath() + "/share/quiz/";
    QStringList filelist = appdir.entryList();

    for(int i=0; i < filelist.count() ; i++){
        QString fname = filelist.at(i);

        if(fname.endsWith(".json")){
            qDebug() << QString("%1::%2 - Found quiz file '%3'").arg(_classname).arg(__func__).arg(fname);
            QFile f(appdir.filePath(fname));
            if(f.open(QFile::ReadOnly)){
                QByteArray filecontent = f.readAll();
                Quiz * q = decodeUTF8Json(&filecontent, base);
                if(q){
                    _quizs->insert(q->id(), q);
                }else{
                    qDebug() << QString("%1::%2 - Could NOT decode file '%3'").arg(_classname).arg(__func__).arg(fname);
                }
                f.close();
            }else{
                qDebug() << QString("%1::%2 - Could not open question base file '%3'. Skipping.").arg(_classname).arg(__func__).arg(fname);
            }
        }
    }

    *quizs = _quizs;

    return true;
}

Quiz *Quiz::decodeUTF8Json(QByteArray *barray, QMap<QString, QuestionBase *> * bases)
{
    Quiz * quiz = nullptr;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(*barray, &err);

    if(!doc.isNull()){
        QJsonObject obj = doc.object();

        if(obj["_objectType"] == "quiz"){
            if(obj.contains("id") && obj.contains("version") && obj.contains("questions")){
                quiz = new Quiz();

                quiz->setId(obj.value("id").toString("ID inconnu"));
                quiz->setVersion(obj.value("version").toString("Version inconnu"));
                quiz->setAuthor(obj.value("author").toString("Auteur inconnu"));

                QJsonArray qArray = obj.value("questions").toArray();

                for(int i=0; i < qArray.size() ; i++){
                    QJsonObject qObj = qArray.at(i).toObject();

                    if( qObj.contains("base") && qObj.contains("baseVersion") && qObj.contains("ids") ){

                        QString baseName = qObj.value("base").toString();
                        QString baseVersion = qObj.value("baseVersion").toString();
                        QJsonArray idsArray = qObj.value("ids").toArray();

                        if((!baseName.isEmpty()) && (!baseVersion.isEmpty()) && (idsArray.size() > 0) ){

                            if(bases->contains(baseName)){
                                QuestionBase * base = bases->value(baseName);

                                if(base->version() == baseVersion){

                                    for(int j=0; j < idsArray.size() ; j++){
                                        QVariant aObj = idsArray.at(j).toVariant();

                                        QString qId = aObj.toString();

                                        if(!qId.isEmpty()){
                                            Question * qSrc = base->question(qId);
                                            if(qSrc){
                                                Question * qDst = Question::deepcopy(qSrc);
                                                quiz->appendQuestion(qDst);
                                            }else {
                                                qDebug() << QString("%1::%2 - Question reference id %3 not found in question base %4 version %5. Ignoring Question reference at index %6.").arg(_classname).arg(__func__).arg(qId).arg(baseName).arg(baseVersion).arg(j);
                                            }
                                        }else{
                                            qDebug() << QString("%1::%2 - Could not read ID for Question reference at index %5. Ignoring Question reference.").arg(_classname).arg(__func__).arg(j);
                                        }
                                    }
                                }else{
                                    qDebug() << QString("%1::%2 - Question base dependency (%3 version %4) not met for Question base reference at index %5. Ignoring Question base reference.").arg(_classname).arg(__func__).arg(baseName).arg(baseVersion).arg(i);
                                }
                            }else{
                                qDebug() << QString("%1::%2 - Question base dependency (%3 version %4) not met for Question base reference at index %5. Ignoring Question base reference.").arg(_classname).arg(__func__).arg(baseName).arg(baseVersion).arg(i);
                            }
                        }else{
                            qDebug() << QString("%1::%2 - Could not read mandatory keys for Question at index %3: conversion error. Ignoring.").arg(_classname).arg(__func__).arg(i);
                            delete quiz;
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

    return quiz;
}

bool Quiz::appendQuestion(Question *q)
{
    if(q){
        Question * qcopy = new Question();

        qcopy->setId(q->id());
        qcopy->setGroup(q->group());
        qcopy->setFormula(q->formula());
        qcopy->setImageUri(q->imageUri());
        qcopy->setDifficulty(q->difficulty());
        qcopy->setTimeLimit_ms(q->timeLimit_ms());

        m_questionList.append(qcopy);

        return true;
    }else{
        return false;
    }
}

void Quiz::setId(QString id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void Quiz::setAuthor(QString author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged(m_author);
}

void Quiz::setVersion(QString version)
{
    if (m_version == version)
        return;

    m_version = version;
    emit versionChanged(m_version);
}
