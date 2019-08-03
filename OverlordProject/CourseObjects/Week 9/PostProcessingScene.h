#pragma once
#include "GameScene.h"

class ModelComponent;
class SpriteFont;

class PostProcessingScene : public GameScene
{
public:
	PostProcessingScene(void);
	virtual ~PostProcessingScene(void);

protected:

	 void Initialize() override;
	 void Update( )override;
	 void Draw() override;

private:

	ModelComponent* m_pModel;
	SpriteFont* m_pFont;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	PostProcessingScene(const PostProcessingScene &obj);
	PostProcessingScene& operator=(const PostProcessingScene& obj);
};

