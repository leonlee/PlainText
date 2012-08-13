#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

#include <QString>


class Session;

class Player : public Character {

    Q_OBJECT

    public:
        Player(Realm *realm, uint id, Options options = NoOptions);
        virtual ~Player();

        const QString &passwordSalt() const { return m_passwordSalt; }
        void setPasswordSalt(const QString &passwordSalt);
        Q_PROPERTY(QString passwordSalt READ passwordSalt WRITE setPasswordSalt)

        const QString &passwordHash() const { return m_passwordHash; }
        void setPasswordHash(const QString &passwordHash);
        Q_PROPERTY(QString passwordHash READ passwordHash WRITE setPasswordHash)

        bool isAdmin() const { return m_admin; }
        void setAdmin(bool admin);
        Q_PROPERTY(bool admin READ isAdmin WRITE setAdmin)

        Session *session() const { return m_session; }
        void setSession(Session *session);

        virtual void send(const QString &message, Color color = Silver) const;

        Q_INVOKABLE void sendSellableItemsList(const GameObjectPtrList &items);

        Q_INVOKABLE void look();

        virtual void invokeTimer(int timerId);

    signals:
        void write(const QString &data) const;

    protected:
        virtual void changeName(const QString &name);

        virtual void enteredArea();

    private:
        QString m_passwordSalt;
        QString m_passwordHash;

        int m_regenerationIntervalId;

        bool m_admin;

        Session *m_session;
};

#endif // PLAYER_H
