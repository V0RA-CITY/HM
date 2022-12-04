#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"
class HouseBuilderA;


class House : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;


	

private:
	char look[7][14];
	const uint16_t score = 40;
};



class HouseBuilder
{
public:
	HouseBuilder();
	~HouseBuilder();

private:

};


class HouseBuilderA
{
	friend class House;
public:

	HouseBuilderA();
	~HouseBuilderA();

	void Build(House &obj)
	{
		obj.
	};

private:

};


class HouseDirector
{
public:
	HouseDirector();
	~HouseDirector();

	void Construct();
private:

};
