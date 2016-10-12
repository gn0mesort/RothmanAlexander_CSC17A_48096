#include "Enums.h" 

std::string Flow::toString(Flow::Exit exit){
     std::string r = "";
     
     switch(exit){
         case Flow::Exit::None:
         {
             r = "None";
             break;
         }
         case Flow::Exit::North:
         {
             r = "North";
             break;
         }
         case Flow::Exit::East:
         {
             r = "East";
             break;
         }
         case Flow::Exit::South:
         {
             r = "South";
             break;
         }
         case Flow::Exit::West:
         {
             r = "West";
             break;
         }
     }
     
     return r;
 }
 std::string Flow::toString(Flow::RoomType);
 std::string Flow::toString(Flow::JobType);
 std::string Flow::toString(Flow::ItemType);
 std::string Flow::toString(Flow::DamageElement);