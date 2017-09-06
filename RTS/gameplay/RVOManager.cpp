#include "RVOManager.h"
#include "misc/G.h"
#include "misc/WindowsInput.h"
#include "rvo/RVO.h"
RVOManager::RVOManager() {
	setName("rvo_manager");
}
RVOManager::~RVOManager() {
	delete sim;
}
void RVOManager::init() {
	sim = new RVO::RVOSimulator();
	sim->setTimeStep(0.25f);
	/*float neighborDist, size_t maxNeighbors,
		float timeHorizon, float timeHorizonObst,
		float radius, float maxSpeed,*/
	sim->setAgentDefaults(15.0f, 10, 10.0f, 10.0f, 1.5f, 2.0f);

	void setAgentDefaults(float neighborDist, size_t maxNeighbors,
		float timeHorizon, float timeHorizonObst,
		float radius, float maxSpeed,
		const Vector2 &velocity = Vector2());

	for (size_t i = 0; i < 250; ++i) {
		sim->addAgent(200.0f *
			RVO::Vector2(std::cos(i * 2.0f * Math_PI / 250.0f),
				std::sin(i * 2.0f * Math_PI / 250.0f)));
		goals.push_back(-sim->getAgentPosition(i));
	}
}
void RVOManager::update(float deltaTime) {
	/*
	* Set the preferred velocity to be a vector of unit magnitude (speed) in the
	* direction of the goal.
	*/
	for (int i = 0; i < static_cast<int>(sim->getNumAgents()); ++i) {
		RVO::Vector2 goalVector = goals[i] - sim->getAgentPosition(i);
		RVO::Vector2 vec = sim->getAgentPosition(i) / 40.0f;
		RVO::Vector2 velo = vec + sim->getAgentVelocity(i) / 4.0f;
		OERenderer->line2D(Vector2(vec.x(), vec.y()), Vector2(velo.x(), velo.y()), Color::cyan());

		if (RVO::absSq(goalVector) > 1.0f) {
			goalVector = RVO::normalize(goalVector);
		}

		sim->setAgentPrefVelocity(i, goalVector);
	}

	for (size_t i = 0; i < sim->getNumAgents(); ++i) {
		if (RVO::absSq(sim->getAgentPosition(i) - goals[i]) > sim->getAgentRadius(i) * sim->getAgentRadius(i)) {
			//printf_s("goal!");
		}
	}
	sim->doStep();
}