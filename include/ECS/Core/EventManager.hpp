#pragma once

#include "Types.hpp"
#include "Event.hpp"
#include <list>

class EventManager {
    public:
        void AddListener(EventType eventType, std::function<void(Event&)> const& listener) {
            listeners[eventType].push_back(listener);
        }

        void SendEvent(Event& event) {
		    uint32_t eventType = event.GetType();

		    for (auto const& listener : listeners[eventType]) {
			    listener(event);
		    }
	    }

	    void SendEvent(EventType eventType) {
		    Event event(eventType);

		    for (auto const& listener : listeners[eventType]) {
			    listener(event);
		    }
	    }

    private:
        std::unordered_map<EventType, std::list<std::function<void(Event&)>>> listeners;
};