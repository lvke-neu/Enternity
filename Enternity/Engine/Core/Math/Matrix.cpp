#include "Matrix.h"
#include <cmath>

namespace Enternity
{
	void MatrixRotationYawPitchRoll(Matrix4x4f& matrix, const float yaw, const float pitch, const float roll)
	{
		float cYaw, cPitch, cRoll, sYaw, sPitch, sRoll;

		// Get the cosine and sin of the yaw, pitch, and roll.
		cYaw = std::cos(yaw);
		cPitch = std::cos(pitch);
		cRoll = std::cos(roll);

		sYaw = std::sin(yaw);
		sPitch = std::sin(pitch);
		sRoll = std::sin(roll);

		// Calculate the yaw, pitch, roll rotation matrix.
		Matrix4x4f tmp = { {{
			{ (cRoll * cYaw) + (sRoll * sPitch * sYaw), (sRoll * cPitch), (cRoll * -sYaw) + (sRoll * sPitch * cYaw), 0.0f },
			{ (-sRoll * cYaw) + (cRoll * sPitch * sYaw), (cRoll * cPitch), (sRoll * sYaw) + (cRoll * sPitch * cYaw), 0.0f },
			{ (cPitch * sYaw), -sPitch, (cPitch * cYaw), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		}} };

		matrix = tmp;

		return;
	}
}