#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (std::pair<ComponentsID, BaseComponent*> element : m_pComponents)
	{
		delete(element.second);
	}
}

void dae::GameObject::Update(float dt)
{
	for (std::pair<ComponentsID,BaseComponent*> element : m_pComponents)
	{
		element.second->Update(dt);
	}
}

void dae::GameObject::Render() const
{
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);

	for (std::pair<ComponentsID, BaseComponent*> element : m_pComponents)
	{
		element.second->Render();
	}
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

//void dae::GameObject::SetPosition(float x, float y)
//{
//	m_Transform.SetPosition(x, y, 0.0f);
//}

void dae::GameObject::AddComponent(BaseComponent* pComp, ComponentsID compID)
{
	m_pComponents.insert({compID,pComp});

}

