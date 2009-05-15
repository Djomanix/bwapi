#pragma once

#include <Util/Types.h>

#include <BW/OrderID.h>
#include <BW/UnitType.h>
#include <BW/TechType.h>
#include <BW/UpgradeType.h>
#include <BW/TilePosition.h>

namespace Util  { class Logger; }
namespace BW    { class Position; };
namespace BW    { struct Unit; };
namespace BWAPI { class UnitPrototype;  };
namespace BWAPI { class AbilityPrototype;  };
namespace BWAPI { class Player;  };

namespace BWAPI
{
  /**
   * Interface for broodwar unit, can be used to obtain any information and
   * issue commands.
   */
  class Unit
  {
    public:
      /** 
       * @param bwUnit         #bwUnit                          
       * @param bwOriginalUnit #bwOriginalUnit
       * @param bwUnitLocal    #bwUnitLocal
       * @param index          #index
       */
      Unit(BW::Unit* bwUnit,
           BW::Unit* bwOriginalUnit,
           BW::Unit* bwUnitLocal,
           u16 index);
      ~Unit();
      BW::UnitType getType() const;
      u16 getHealthPoints() const; 
      u32 getShieldPoints() const; 
      const BW::Position& getPosition() const;
      BW::TilePosition getTilePosition() const;
      Unit* getTarget() const;
      Unit* getOrderTarget() const;
      Unit* getBuildUnit() const;
      Unit* getChild() const;
      BW::Position getTargetPosition() const;
      Player* getOwner() const;
      u8 getBuildQueueSlot() const;
      /** Gets #bwUnit->BW#Unit#buildQueue */
      BW::UnitType* getBuildQueue() const;
      /** Returns if the unit has empty building queue */
      bool hasEmptyBuildQueue() const;
      /** Returns if the unit has full building queue */
      bool hasFullBuildQueue() const;

      /** Gets distance of unit edges. */
      u16 getDistance(Unit *unit) const; 
      /** Gets distance of unit center and position. */
      u16 getDistance(BW::Position position) const; 
      /** Gets distance of unit centers. */
      u16 getCenterDistance(Unit *unit) const; 
      /**< Gets bwUnit->BW#Unit#orderID. */
      BW::OrderID::Enum getOrderID() const;
      /**< Gets bwUnit->BW#Unit#secondaryOrderID. */
      BW::OrderID::Enum getSecondaryOrderID() const;
      bool isIdle() const;
      /* Timer specifiing how long it will take to finish the current order
       * (verified for mining).
       */
      u8 getOrderTimer() const;
      u16 getRemainingBuildTime() const;
      /**
       * Gets if the unit is alive (it exists), it uses hp > 0 heuristic for
       * now.
       */
      bool isValid() const;
      /** Gets if the unit is alive - exists and it's construction is done. */
      bool isReady() const;
      /** Gets if the unit construction is done */
      bool isCompleted() const;
      bool isLifted() const;
      /** Only active when UserInput flag is enabled */
      bool isSelected() const;

      /** Gets #bwOriginalUnit */
      BW::Unit *getOriginalRawData() const;
      /** Gets #bwUnitLocal */
      BW::Unit *getRawDataLocal() const;

      /**
       * Order this unit to right click on the specified location. Note that
       * right click on location will always result in move.
       */
      void orderAttackLocation(BW::Position position, u8 OrderID);
      /**
       * Orders this unit to attack Location on the specified unit. Note that attack location
       * on unit can result in lot of commands (attack)
       */
      /**
       * Order this unit to right click on the specified location. Note that
       * right click on location will always result in move.
       */
      void orderRightClick(BW::Position position);
      /**
       * Orders this unit to right click on the specified unit. Note that right
       * click on unit can result in lot of commands (attack, gather, follow,
       * set rally point)
       */
      void orderRightClick(Unit *target);
      /** Orders this unit to train (construct) the specified unit. */
      void trainUnit(BW::UnitType type);
      /** Orders to build the specified building. */
      void build(BW::TilePosition position, BW::UnitType type);
      /** Orders to build the invent the specified tech. */
      void invent(BW::TechType tech);
      /** Orders to build the invent the specified upgrade. */
      void upgrade(BW::UpgradeType upgrade);
      static Unit* BWUnitToBWAPIUnit(BW::Unit* unit);
      std::string getName() const;
      Unit* getNext() const;
      /** Gets if the current unit mineral (there are 3 Types of minerals) */
      bool isMineral() const;
      /**
       * Gets index of the unit in the unit array. Note that the index is same
       * for the original unit array, BWAPI::Unit array and BWAI::Unit array, so
       * it is good way to compare units of different types and for conversion.
       * @return 0-based index of the unit in the unit array.
       */
      u16 getIndex() const;
      void setSelected(bool selectedState);

    private:
      /** Gets #bwUnit */
      BW::Unit *getRawData() const;

      bool hasEmptyBuildQueueSync() const;
      BW::UnitType* getBuildQueueSync() const;
      u8 getBuildQueueSlotSync() const;
      /** Orders to select this unit (previous selection will be lost. */
      void orderSelect();
      /** Gets distance between two positions. */
      u16 getDistance(int x1, int y1, int x2, int y2) const; 

      BW::Unit* bwUnit; /**< Pointer to our copy of of unit data table. */
      BW::Unit* bwUnitLocal; /**< Pointer to our local (precomputed) version of unit data table  @ref localData. */ 
      BW::Unit* bwOriginalUnit; /**< Pointer to broodwar unit data table. */
      u16 index; /**< Index of the unit in the array (can be computed, it's just optimisation) */
      bool userSelected;
      bool visible;
  };
};

