#pragma once
#include "../../../PhysicsLib/Collidable.h"
#include <string>

class EnemyMidle : public Collidable
{
public:
	EnemyMidle();
	~EnemyMidle();

	void Init(std::shared_ptr<Physics> _physics);
	void Final(std::shared_ptr<Physics> _physics);
	void Update(std::shared_ptr<Physics> _physics);
	void Draw(std::shared_ptr<Physics> _physics);

	void OnCollide(const std::shared_ptr<Collidable>& _colider);

};

