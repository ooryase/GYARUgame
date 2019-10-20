#pragma once

class VirtualParticle
{
protected:
	int baseX, baseY;
public:
	bool Dead;

	VirtualParticle(int x,int y);

	void virtual Update(int deltaTime) = 0;
	void virtual Draw() const = 0;
};