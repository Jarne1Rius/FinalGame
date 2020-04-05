#include "MiniginPCH.h"
#include "BoxCollider2D.h"
#include "Extra.h"
#include "ExtraMathFiles.h"
#include "CircleCollider2D.h"
Rius::BoxCollider2D::BoxCollider2D()
{
	m_AllColliders.push_back(this);
}

Rius::BoxCollider2D::~BoxCollider2D()
{
}

void Rius::BoxCollider2D::Initialize()
{
}

void Rius::BoxCollider2D::Update()
{

}

void Rius::BoxCollider2D::Render() const
{
}

bool Rius::BoxCollider2D::CheckCollision(CircleCollider2D* circle)
{
	return Collision(this->m_Rectangle, circle->GetCircle2D());
}

bool Rius::BoxCollider2D::CheckCollision(BoxCollider2D* collider)
{
	return Collision(this->m_Rectangle, collider->m_Rectangle);
}
