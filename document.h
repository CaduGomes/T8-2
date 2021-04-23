#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP
#include "user.h"
#include <QString>
#include <QVector>

class Signature
{
public:
    User *m_user;
    bool m_isSigned;

    bool getIsSigned(){return m_isSigned;}

    Signature(User *user, bool sign)
    {
        m_user = user;
        m_isSigned = sign;
    };

    ~Signature()
    {
        delete m_user;
    };
};

class Document
{
private:
    QString m_id;
    QString m_directory;
    QString m_name;
    Signature *m_owner;
public:

    QString getName(){return m_name;}
    QString getDirectory(){return m_directory;};
    QString getID(){return m_id;};
    QString getOwnerId(){return m_owner->m_user->getCPF();};
    QVector<Signature *> m_users;


    Document(QString id, QString directory, QString docName, User *user, QVector<Signature *> &users)
    {
        m_id = id;
        m_owner = new Signature(user, true);
        m_directory = directory;
        m_name = docName;
        m_users = users;
    }

    ~Document()
    {
        delete m_owner;
        for (Signature *s : m_users)
        {
            delete s;
        }
    }
};

#endif
