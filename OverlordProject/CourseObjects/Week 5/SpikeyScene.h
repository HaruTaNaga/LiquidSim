#pragma once
#include "GameScene.h"
#include "EffectHelper.h"

class Material;

class SpikeyScene: public GameScene
{
public:
	SpikeyScene(void);
	virtual ~SpikeyScene(void);

protected:

	 void Initialize() override;
	 void Update() override;
	 void Draw() override;

private:

	float m_FpsInterval;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	SpikeyScene( const SpikeyScene &obj);
	SpikeyScene& operator=( const SpikeyScene& obj);
};

