#ifndef UGE_TRANSFORM_H
#define UGE_TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include <vector>

namespace UGE
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		const glm::vec3&		getPosition() const;
		void					setPosition(const glm::vec3 &position);
		glm::vec3				getWorldPosition() const;

		const glm::quat&		getRotation() const;
		void					setRotation(const glm::quat &rotation);
		void					rotate(float angleDeg, const glm::vec3 &axis);

		const glm::vec3&		getSize() const;
		void					setSize(const glm::vec3 &size);

		const glm::vec3&		getRight() const;
		const glm::vec3&		getUp() const;
		const glm::vec3&		getForward() const;

		const glm::mat4&		getModelMatrix() const;
		const glm::mat4&		getScaledModelMatrix() const;

		void					addChild(Transform &child);

		void					interpolate(const Transform &a, const Transform &b, float f);

	private:
		void					updateModelMatrix();
		void					updateOrientationVectors();

		void					removeFromParent();

		glm::vec3				mPosition;
		glm::vec3				mWorldPosition;
		glm::quat				mRotation;
		glm::vec3				mSize;
		glm::vec3				mRight;
		glm::vec3				mUp;
		glm::vec3				mForward;
		glm::mat4				mModelMatrix;
		glm::mat4				mScaledModelMatrix;
		std::vector<Transform*>	mChildren;
		Transform*				mParent;
	};
}

#endif