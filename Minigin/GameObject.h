#pragma once
#include "Transform.h"
#include "BaseComponent.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

#include <map>

enum class ComponentsID : int
{
	RenderComp = 0,
	TextComp = 1,
	FPSComp = 2,
	QbertComp = 3,
	LivesComp = 4,
	ScoreComp = 5,
};

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		void Update(float dt);
		void Render() const;

		//void SetTexture(const std::string& filename);
		//void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();

		void AddComponent(BaseComponent* pComp,ComponentsID compID);

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::map<ComponentsID,BaseComponent*> m_pComponents;
	};
}
