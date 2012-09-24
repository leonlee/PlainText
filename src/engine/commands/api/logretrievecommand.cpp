#include "logretrievecommand.h"

#include "diskutil.h"
#include "retrievestatslogmessage.h"
#include "realm.h"
#include "util.h"


#define super ApiCommand

LogRetrieveCommand::LogRetrieveCommand(Player *player, QObject *parent) :
    super(player, parent) {

    setDescription("Syntax: api-log-retrieve <request-id> stats <stats-type> <number-of-days>");
}

LogRetrieveCommand::~LogRetrieveCommand() {
}

void LogRetrieveCommand::execute(const QString &command) {

    super::execute(command);

    if (takeWord() != "stats") {
        sendError(400, "First argument should be stats");
        return;
    }

    QString statsType = takeWord();
    int numDays = takeWord().toInt();

    if (DiskUtil::logDir().isEmpty()) {
        sendError(503, "Logging unavailable");
        return;
    }

    Realm::instance()->enqueueLogMessage(new RetrieveStatsLogMessage(player(), requestId(),
                                                                     statsType, numDays));
}
