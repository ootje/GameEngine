#pragma once
#include <map>
#include <vector>

#include "Transform.h"
#include "BaseComponent.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

namespace dae
{
	enum class componentID : int
	{
		base = 0,
		render = 1,
		text = 2,
	};
	
	class Texture2D;
	class GameObject final
	{
	public:
		void Update(float dt);
		void Render() const;

		GameObject() = default;
		virtual ~GameObject();

		void AddComponent(BaseComponent* pComp, int id);// , ComponentsID compID);

		// child - parent relationships
		
		BaseComponent* GetComponent(int id) const;
		std::vector<BaseComponent*> GetComponents(int id) const;
		
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		//Transform m_Transform;
		std::map<BaseComponent*,int> m_pComponents;
	};
}
