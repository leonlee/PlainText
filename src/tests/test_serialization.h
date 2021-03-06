#ifndef TEST_SERIALIZATION_H
#define TEST_SERIALIZATION_H

#include "testcase.h"

#include <QFile>
#include <QTest>

#include "characterstats.h"
#include "diskutil.h"
#include "realm.h"


class SerializationTest : public TestCase {

    Q_OBJECT

    private slots:
        void testUserStrings() {

            QString userString = "[1, 1, 1, 1, 1, 1]";
            CharacterStats expected(1);
            CharacterStats actual;
            CharacterStats::fromUserString(userString, actual);
            QCOMPARE(actual, expected);
        }

        void testObjectsSyncedToDisk() {

            QTest::qWait(20);
            Realm::instance()->enqueueModifiedObjects();

            // wait for sync thread to catch up
            int waitTimeMs = 0;
            while (!QFile::exists(DiskUtil::gameObjectPath("Room", 1)) ||
                   !QFile::exists(DiskUtil::gameObjectPath("Room", 2)) ||
                   !QFile::exists(DiskUtil::gameObjectPath("Portal", 3)) ||
                   !QFile::exists(DiskUtil::gameObjectPath("Player", 4))) {
                QTest::qWait(20);
                waitTimeMs += 20;
                QVERIFY(waitTimeMs < 5000);
            }

            {
                QFile file(DiskUtil::gameObjectPath("Room", 1));
                QVERIFY(file.open(QIODevice::ReadOnly));
                QCOMPARE(QString(file.readAll()), QString("{\n"
                    "  \"name\": \"Room A\",\n"
                    "  \"type\": \"Room\",\n"
                    "  \"position\": [ 0, 0, 0 ],\n"
                    "  \"flags\": \"\",\n"
                    "  \"portals\": [ \"portal:3\" ]\n"
                "}"));
            }

            {
                QFile file(DiskUtil::gameObjectPath("Room", 2));
                QVERIFY(file.open(QIODevice::ReadOnly));
                QCOMPARE(QString(file.readAll()), QString("{\n"
                    "  \"name\": \"Room B\",\n"
                    "  \"type\": \"Room\",\n"
                    "  \"position\": [ 0, 50, 0 ],\n"
                    "  \"flags\": \"\",\n"
                    "  \"portals\": [ \"portal:3\", \"portal:6\" ]\n"
                "}"));
            }

            {
                QFile file(DiskUtil::gameObjectPath("Portal", 3));
                QVERIFY(file.open(QIODevice::ReadOnly));
                QCOMPARE(QString(file.readAll()), QString("{\n"
                    "  \"name\": \"a-to-b\",\n"
                    "  \"name2\": \"b-to-a\",\n"
                    "  \"room\": \"room:1\",\n"
                    "  \"room2\": \"room:2\",\n"
                    "  \"flags\": \"CanSeeThrough|CanHearThrough|CanPassThrough\"\n"
                "}"));
            }

            {
                QFile file(DiskUtil::gameObjectPath("Player", 4));
                QVERIFY(file.open(QIODevice::ReadOnly));
                QCOMPARE(QString(file.readAll()), QString("{\n"
                    "  \"name\": \"Arie\",\n"
                    "  \"position\": [ 0, 0, 0 ],\n"
                    "  \"weight\": 0,\n"
                    "  \"cost\": 0,\n"
                    "  \"flags\": \"\",\n"
                    "  \"stats\": [0, 0, 0, 0, 0, 0],\n"
                    "  \"height\": 0,\n"
                    "  \"currentRoom\": \"room:1\",\n"
                    "  \"direction\": [ 0, 0, 0 ],\n"
                    "  \"race\": \"0\",\n"
                    "  \"characterClass\": \"0\",\n"
                    "  \"gender\": \"male\",\n"
                    "  \"respawnTime\": 0,\n"
                    "  \"respawnTimeVariation\": 0,\n"
                    "  \"hp\": 1,\n"
                    "  \"maxHp\": 1,\n"
                    "  \"mp\": 0,\n"
                    "  \"maxMp\": 0,\n"
                    "  \"gold\": 0,\n"
                    "  \"weapon\": \"0\",\n"
                    "  \"secondaryWeapon\": \"0\",\n"
                    "  \"shield\": \"0\",\n"
                    "  \"admin\": true\n"
                "}"));
            }
        }
};

#endif // TEST_SERIALIZATION_H
