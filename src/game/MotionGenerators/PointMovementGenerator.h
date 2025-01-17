/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MANGOS_POINTMOVEMENTGENERATOR_H
#define MANGOS_POINTMOVEMENTGENERATOR_H

#include "MovementGenerator.h"

template<class T>
class PointMovementGenerator
    : public MovementGeneratorMedium< T, PointMovementGenerator<T> >
{
    public:
        PointMovementGenerator(uint32 _id, float _x, float _y, float _z, bool _generatePath, uint32 forcedMovement, float speed = 0.f, bool effect = false) :
            id(_id), i_x(_x), i_y(_y), i_z(_z), m_generatePath(_generatePath), m_speedChanged(false), m_forcedMovement(forcedMovement), m_speed(speed), m_effect(effect) {}

        virtual void Initialize(T&);
        void Finalize(T&);
        void Interrupt(T&);
        void Reset(T& unit);
        bool Update(T&, const uint32& diff);

        void MovementInform(T&);

        MovementGeneratorType GetMovementGeneratorType() const override
        {
            if (m_effect)
                return EFFECT_MOTION_TYPE;
            return POINT_MOTION_TYPE;
        }

        bool GetDestination(float& x, float& y, float& z) const { x = i_x; y = i_y; z = i_z; return true; }

        virtual void UnitSpeedChanged() override
        {
            if (m_speed <= 0.f) // if custom speed - do not react to speed change
                m_speedChanged = true;
        }
    private:
        uint32 id;
        float i_x, i_y, i_z;
        bool m_generatePath;
        bool m_speedChanged;
        uint32 m_forcedMovement;
        float m_speed;
        bool m_effect;
};

class AssistanceMovementGenerator
    : public PointMovementGenerator<Creature>
{
    public:
        AssistanceMovementGenerator(float _x, float _y, float _z) :
            PointMovementGenerator<Creature>(0, _x, _y, _z, true, 0) {}

        MovementGeneratorType GetMovementGeneratorType() const override { return ASSISTANCE_MOTION_TYPE; }
        void Initialize(Creature&) override;
        void Finalize(Unit&) override;
};

// Does almost nothing - just doesn't allows previous movegen interrupt current effect. Can be reused for charge effect
class EffectMovementGenerator : public MovementGenerator
{
    public:
        explicit EffectMovementGenerator(uint32 Id) : m_Id(Id) {}
        void Initialize(Unit&) override {}
        void Finalize(Unit& unit) override;
        void Interrupt(Unit&) override {}
        void Reset(Unit&) override {}
        bool Update(Unit& unit, const uint32&) override;
        MovementGeneratorType GetMovementGeneratorType() const override { return EFFECT_MOTION_TYPE; }
    private:
        uint32 m_Id;
};

class FlyOrLandMovementGenerator : public PointMovementGenerator<Creature>
{
    public:
        FlyOrLandMovementGenerator(uint32 _id, float _x, float _y, float _z, bool liftOff) :
            PointMovementGenerator<Creature>(_id, _x, _y, _z, false, 0),
            m_liftOff(liftOff) {}

        void Initialize(Unit& unit) override;
    private:
        bool m_liftOff;
};

#endif
