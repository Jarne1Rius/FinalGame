#include "BaseComponent.h"
#include "Extra.h"
#include <vector>
#include "BasicMaterial.h"
namespace Rius
{
	class TriangleRenderer : public BaseComponent
	{
	public:
		TriangleRenderer(const std::vector<glm::vec2>& triangle,const std::vector<glm::vec2>& textCoord );
		~TriangleRenderer();
		void SetMaterial(BasicMaterial* material) { m_Material = material; m_Material->Initialize(); }
		void Initialize() override;
		void Update() override;
		void Render() const override;
		std::vector<glm::vec2> GetTriangle() const { return m_Triangle; }
	private:
		void SetIndicesAndVertices();
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		std::vector<float> m_Vertices;
		std::vector<int> m_Indices;
		std::vector<glm::vec2> m_Triangle;
		std::vector<glm::vec2> m_TextCoord;
		BasicMaterial* m_Material;
	};
}
