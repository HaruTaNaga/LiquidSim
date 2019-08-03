#pragma once
#include "GameScene.h"

class ParticleEmitterComponent;
class ModelComponent;

class ParticleScene : public GameScene
{
public:
	ParticleScene(void);
	virtual ~ParticleScene(void);

protected:

	 void Initialize() override;
	 void Update() override;
	 void Draw() override;

private:

	ParticleEmitterComponent* m_pParticleEmitter;
	ModelComponent* m_pModel;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ParticleScene(const ParticleScene &obj);
	ParticleScene& operator=(const ParticleScene& obj);
};

