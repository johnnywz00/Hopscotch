//
//  fusemanager.hpp
//  Ravoxyd_
//
//  Created by John Ziegler on 9/1/24.
//  Copyright © 2024 John Ziegler. All rights reserved.
//

#ifndef fusemanager_hpp
#define fusemanager_hpp

#include "jwzsfml.hpp"

struct Fuse {
    
    Fuse (float delay, function<void(void)> f, bool isDaemon = false, string t = "nil") :
            func(f),
            tag(t)
            {
        if (isDaemon)
            removeAfterFire = false;
        secondsDelay = seconds(delay);
    }
    
    void fire () { func(); }

    bool removeAfterFire { true };
    bool removeBeforeFire { false };
    bool isActive = true;
    Time secondsDelay;
    Time readyTime {};
    string tag;
    function<void(void)> func;
};



struct FuseManager {

    void addEvent (Fuse& ev) {
        
        ev.readyTime = elapsed + ev.secondsDelay;
        events.push_back(ev);
		if (ev.tag != "") {
			pendingTags[ev.tag] = true;
		}
    }
    
    void addEvent (float del, function<void(void)> f, bool isDaemon = false, string t = "") {
        
        Fuse fuse {del, f, isDaemon, t};
        fuse.readyTime = elapsed + fuse.secondsDelay;
        events.push_back(fuse);
		if (t != "") {
			pendingTags[t] = true;
		}
	}
	
		/* Only add the event if its tag isn't already pending */
	void addEventIf (Fuse& ev) {
		
		if (!pendingTags[ev.tag]) {
			addEvent(ev);
		}
	}
	
	void addEventIf (string t, float del, function<void(void)> f, bool isDaemon = false) {
		
		if (!pendingTags[t]) {
			addEvent(del, f, isDaemon, t);
		}
	}
    
    void removeByTag (string t) {
        
        for (auto itr = events.begin(); itr != events.end(); ) {
			if ((*itr).tag == t) {
				pendingTags[t] = false;
				events.erase(itr);
			}
            else ++itr;
        }
    }
    
    void removeEvent (Fuse& ev) {
        
        for (auto itr = events.begin(); itr != events.end(); ) {
            if ( &(*itr) == &ev ) {
				pendingTags[ev.tag] = false;
                events.erase(itr);
            }
            else ++itr;
        }
    }
    
    void fireReadyEvents (const Time& t) {
        
        elapsed = t;
        if (events.size() == 0)
            return;
        for (auto itr = events.begin(); itr != events.end(); ++itr) {
            auto& e = *itr;
            if (e.removeBeforeFire || !e.isActive)
                continue;
            if (e.readyTime <= t) {
                e.fire();
                if (!e.removeAfterFire) {
                    e.readyTime = t + e.secondsDelay;
                }
            }
        }
        for (auto itr = events.begin(); itr != events.end(); ) {
            auto& e = *itr;
            if (e.readyTime <= t && (e.removeBeforeFire || e.removeAfterFire)) {
				pendingTags[e.tag] = false;
                events.erase(itr);
            }
            else ++itr;
        }
    }
	
	bool isActive (const string t) {
		return pendingTags[t];
	}
	
	
	void gSet (string s) { flagTable[s] = true; }
	
	void gUnset (string s) { flagTable[s] = false; }
	
	bool gOn (string s) { return flagTable[s]; }
    
    vector<Fuse>    			events;
	unordered_map<string, bool> pendingTags;
	unordered_map<string, bool> flagTable;
    Time            			elapsed;
};





#endif /* fusemanager_hpp */
