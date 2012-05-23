#include "gameexception.h"

#include <cstdio>


const char *GameException::s_messages[] = {
    "Unknown game object type",
    "Cannot open game object file",
    "Corrupt game object file",
    "Invalid game object file name",
    "Invalid game object pointer",
    "Invalid function code",
    "Invalid exit format"
};

GameException::GameException(Cause cause) :
    std::exception(),
    m_customMessage(false),
    m_message(const_cast<char *>(s_messages[cause])) {
}

GameException::GameException(Cause cause, const char *objectType, uint id) :
    std::exception(),
    m_customMessage(true) {

    m_message = new char[100];
    if (objectType) {
        sprintf(m_message, "%s (Object: %s:%d)", s_messages[cause], objectType, id);
    } else {
        sprintf(m_message, "%s (Object: undefined:%d)", s_messages[cause], id);
    }
}

GameException::~GameException() throw () {

    if (m_customMessage) {
        delete[] m_message;
    }
}

const char *GameException::what() const throw () {

    return m_message;
}