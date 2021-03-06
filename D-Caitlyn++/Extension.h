#pragma once
#include "Menu.h"

static bool InFountain(IUnit *unit)
{
	//TODO: Implement
	return unit->HasBuff("kappachino");
}

inline int EnemiesInRange(IUnit* Source, float range)
{
	auto Targets = GEntityList->GetAllHeros(false, true);
	auto enemiesInRange = 0;

	for (auto target : Targets)
	{
		if (target != nullptr)
		{
			auto flDistance = (target->GetPosition() - Source->GetPosition()).Length();
			if (flDistance < range)
			{
				enemiesInRange++;
			}
		}
	}
	return enemiesInRange;
}

inline float GetDistance(IUnit* Player, IUnit* target)
{
	return (Player->GetPosition() - target->GetPosition()).Length2D();
}

inline int CountEnemiesInRange(float range)
{
	int enemies = 0;
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && GetDistance(GEntityList->Player(), enemy) <= range)
		{
			enemies++;
		}
	}
	return enemies;
}

inline void CastQ(IUnit* target)
{
	if (Q->IsReady() && target != nullptr && !target->IsWard())
	{
		if (myHero->IsValidTarget(target, Q->Range()))
		{
			auto dmg = GDamage->GetSpellDamage(myHero, target, kSlotQ);
			AdvPredictionOutput prediction_output;
			Q->RunPrediction(target, true, kCollidesWithYasuoWall, &prediction_output);
			if (prediction_output.HitChance >= kHitChanceHigh && CountEnemiesInRange(400) == 0 && !myHero->GetRealAutoAttackRange(target))
			{
				if (target->GetHealth() < dmg)
				{
					Q->CastOnTarget(target);
				}
				else if (target->HasBuff("caitlynyordletrapinternal") || target->HasBuffOfType(BUFF_Stun) || target->HasBuffOfType(BUFF_Snare))
				{
					Q->CastOnTarget(target);
				}
			}
		}
	}
}

inline std::string ToLower(std::string StringToLower)
{
	auto Lowered = StringToLower;
	for (int i = 0; i < Lowered[i]; i++)
	{
		Lowered[i] = tolower(Lowered[i]);
	} return Lowered;
}

inline bool Contains(std::string Container, std::string Contained)
{
	auto LoweredContainer = ToLower(Container); auto LoweredContained = ToLower(Contained);
	if (LoweredContainer.find(LoweredContained) != std::string::npos)
		return true;
	else return false;
}