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
	sim->setAgentDefaults(15.0f, 10, 
		10.0f, 10.0f, 
		1.5f, 2.0f);
	//  float neighborDist, size_t maxNeighbors,
	//	float timeHorizon, float timeHorizonObst,
	//	float radius, float maxSpeed,

	for (size_t i = 0; i < 250; ++i) {
		sim->addAgent(200.0f *
			RVO::Vector2(std::cos(i * 2.0f * Math_PI / 250.0f),
				std::sin(i * 2.0f * Math_PI / 250.0f)));
		goals.push_back(-sim->getAgentPosition(i));
	}
}
int32 RVOManager::add(Vector2 pos) {
	return sim->addAgent(RVO::Vector2(pos.x, pos.y));
}
void RVOManager::updateVelocity(int32 handle, Vector2 preferredVelocity) {
	sim->setAgentPrefVelocity(handle, RVO::Vector2(preferredVelocity.x, preferredVelocity.y));
}
void RVOManager::update(float deltaTime) {
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
	/*for (size_t i = 0; i < sim->getNumAgents(); ++i) {
		if (RVO::absSq(sim->getAgentPosition(i) - goals[i]) > sim->getAgentRadius(i) * sim->getAgentRadius(i)) {
			//printf_s("goal!");
		}
	}*/
	sim->doStep();
}