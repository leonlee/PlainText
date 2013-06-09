
/**
 * Constructor.
 *
 * @note Don't instantiate this class directly, use Realm.createObject("Group") instead.
 */
function Group() {
}

/**
 * Returns a possibly fuzzy description of the group, depending on the strength (clarity) with which
 * the group is being observed.
 *
 * @param strength The strength with which the group is being observed. 1.0 represents a full
 *                 clear view, while 0.0 means the group has become invisible.
 *
 * @return string
 */
Group.prototype.nameAtStrength = function(strength) {

    var room = this.leader.currentRoom;
    var presentMembers = [this.leader];
    for (var i = 0, length = this.members.length; i < length; i++) {
        var member = this.members[i];
        if (member.currentRoom === room) {
            presentMembers.append(member);
        }
    }

    if (strength > 0.9) {
        return presentMembers.joinFancy();
    } else if (strength > 0.8) {
        var numMales = 0, numFemales = 0;
        for (i = 0, length = presentMembers.length; i < length; i++) {
            if (presentMembers[i].gender === "male") {
                numMales++;
            } else {
                numFemales++;
            }
        }
        var what = numMales > 0 ? numFemales > 0 ? "people" : "men" : "women";
        return presentMembers.length > 8 ? "a lot of " + what :
               presentMembers.length > 2 ? "a group of " + what :
                                           "two " + what;
    } else {
        return presentMembers.length > 8 ? "a lot of people" :
                                           "some people";
    }
};
