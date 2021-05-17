#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (auto element : m_pComponents)
	{
		delete(element.first);
	}
}

void dae::GameObject::Update(float dt)
{
	for (auto element : m_pComponents)
	{
		element.first->Update(dt);
	}
}

void dae::GameObject::Render() const
{
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);

	for (auto element : m_pComponents)
	{
		element.first->Render();
	}
}

void dae::GameObject::AddComponent(BaseComponent* pComp, int id)
{
	m_pComponents.insert(std::make_pair(pComp,id));
}

BaseComponent* dae::GameObject::GetComponent(int id) const
{
	auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [id](std::pair<BaseComponent*, int> pair) {return pair.second == id; });
	if (it != m_pComponents.end())
	{
		return it->first;
	}
	return nullptr;
}

std::vector<BaseComponent*> dae::GameObject::GetComponents(int id)const
{
	std::vector<BaseComponent*> output{};

	for(auto& element : m_pComponents)
	{
		if (element.second == id)
		{
			output.push_back(element.first);
		}
	}
	return output;
}
