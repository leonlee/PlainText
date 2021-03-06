#include "room.h"


#define super GameObject

Room::Room(Realm *realm, uint id, Options options) :
    super(realm, GameObjectType::Room, id, options),
    m_position(0, 0, 0) {
}

Room::~Room() {
}

void Room::setPosition(const Point3D &position) {

    if (m_position != position) {
        m_position = position;

        setModified();
    }
}

void Room::addExit(const GameObjectPtr &exit) {

    if (!m_exits.contains(exit)) {
        m_exits << exit;

        setModified();
    }
}

void Room::removeExit(const GameObjectPtr &exit) {

    if (m_exits.removeOne(exit)) {
        setModified();
    }
}

void Room::setExits(const GameObjectPtrList &exits) {

    if (m_exits != exits) {
        m_exits = exits;

        setModified();
    }
}

void Room::addPortal(const GameObjectPtr &portal) {

    if (!m_portals.contains(portal)) {
        m_portals << portal;

        setModified();
    }
}

void Room::removePortal(const GameObjectPtr &portal) {

    if (m_portals.removeOne(portal)) {
        setModified();
    }
}

void Room::setPortals(const GameObjectPtrList &portals) {

    if (m_portals != portals) {
        m_portals = portals;

        setModified();
    }
}

void Room::addPlayer(const GameObjectPtr &player) {

    if (!m_players.contains(player)) {
        m_players << player;
    }
}

void Room::removePlayer(const GameObjectPtr &player) {

    m_players.removeOne(player);
}

void Room::setPlayers(const GameObjectPtrList &players) {

    m_players = players;
}

void Room::addNPC(const GameObjectPtr &npc) {

    if (!m_npcs.contains(npc)) {
        m_npcs << npc;
    }
}

void Room::removeNPC(const GameObjectPtr &npc) {

    m_npcs.removeOne(npc);
}

void Room::setNPCs(const GameObjectPtrList &npcs) {

    if (m_npcs != npcs) {
        m_npcs = npcs;
    }
}

void Room::addItem(const GameObjectPtr &item) {

    if (!m_items.contains(item)) {
        m_items << item;

        setModified();
    }
}

void Room::removeItem(const GameObjectPtr &item) {

    if (m_items.removeOne(item)) {
        setModified();
    }
}

void Room::setItems(const GameObjectPtrList &items) {

    if (m_items != items) {
        m_items = items;

        setModified();
    }
}
