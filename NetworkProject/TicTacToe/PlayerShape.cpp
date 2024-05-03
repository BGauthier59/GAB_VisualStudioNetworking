#include "PlayerShape.h"

PlayerShape::PlayerShape(PlayerTeam team, int x, int y) : playerTeam(team), posX(x), posY(y)
{
	texture.loadFromFile(team == PlayerTeam::TEAM_1 ? "cross.png" : "circle.png");
	sprite.setTexture(texture);
	sprite.setPosition(166.6f * x, 166.6f * y);
}

void PlayerShape::Draw(RenderWindow& w)
{
	w.draw(sprite);
}
