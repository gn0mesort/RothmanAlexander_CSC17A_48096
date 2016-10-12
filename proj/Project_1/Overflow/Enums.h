#ifndef ENUMS_H
#define ENUMS_H

#include <string>

#include "Byte.h"

namespace Flow{
enum class Exit : unsigned char {
    None = 0,
    North = 1,
    East = 2,
    South = 4,
    West = 8
};

enum class RoomType : unsigned char {
    None = 0,
    Encounter = 1,
    Treasure = 2,
    Merchant = 4,
    Inn = 8
};

enum class JobType : unsigned char {
    None = 0,
    Knight = 1,
    Cleric = 2,
    Mage = 4,
    Lancer = 8
};

enum class ItemType : unsigned char {
    None = 0,
    Potion = 1,
    Armor = 2,
    Weapon = 4
};

enum class DamageElement : unsigned char {
    None = 0,
    Healing = 1,
    Fire = 2,
    Ice = 4,
    Lightning = 8,
    Wind = 16,
    Holy = 32,
    Shadow = 64,
    Nightmare = 128,
    Absolute = 255
};

 std::string toString(Exit);
 std::string toString(RoomType);
 std::string toString(JobType);
 std::string toString(ItemType);
 std::string toString(DamageElement);
 
 class EnumUtils{
 public:
    template<class T>
    static int toValue(T value){
        return static_cast<int>(value);
    }
    template<class T>
    static Byte::Byte<T> toByte(T value){
        return Byte::Byte<T>(value);
    }
 private:
 };
}
#endif /* ENUMS_H */

