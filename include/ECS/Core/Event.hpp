#pragma once

#include "Types.hpp"
#include <any>

class Event {
    public:
        Event() = delete;

        explicit Event(EventType eventType): m_Type(eventType) {}

        template<typename T>
        void SetParam(EventType eventType, T value) {
            m_Data[eventType] = value;
        }

        template<typename T>
        T GetParam(EventType eventType) {
            return std::any_cast<T>(m_Data[eventType]);
        }

        EventType GetType() const {
            return m_Type;
        }

    private:
        EventType m_Type{};
        std::unordered_map<EventType, std::any> m_Data{};
};