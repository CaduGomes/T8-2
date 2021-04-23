#ifndef USER_H
#define USER_H
#include <QString>

class User
{
private:
    QString m_cpf;
    QString m_name;
    QString m_pwd;
public:
    User(QString name, QString pwd, QString cpf);

    void setName(QString name) { m_name = name; }
    void setPwd(QString pwd) { m_pwd = pwd; }
    void setCPF(QString cpf) {m_cpf = cpf;}

    QString getName() {return m_name; }
    QString getPwd() { return m_pwd; }
    QString getCPF() {return m_cpf;}
};

#endif
