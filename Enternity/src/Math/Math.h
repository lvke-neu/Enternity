#include "Macro/Macro.h"
#include <glm/glm.hpp>

BEGIN_ENTERNITY

namespace Math
{
	/*copy from hazel engine by cherno*/
	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
}

END_ENTERNITY