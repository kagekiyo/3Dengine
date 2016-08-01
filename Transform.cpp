#include "Transform.h"
#include "glm/gtx/transform.hpp"
#include <algorithm>

namespace UGE
{
	Transform::Transform()
		: mSize(1.0f)
		, mParent(nullptr)
	{
		updateModelMatrix();
		updateOrientationVectors();
	}

	Transform::~Transform()
	{
		removeFromParent();
	}

	const glm::vec3& Transform::getPosition() const
	{
		return mPosition;
	}

	void Transform::setPosition(const glm::vec3 &position)
	{
		mPosition = position;
		updateModelMatrix();
	}

	glm::vec3 Transform::getWorldPosition() const
	{
		return mWorldPosition;
	}

	const glm::quat& Transform::getRotation() const
	{
		return mRotation;
	}

	void Transform::setRotation(const glm::quat &rotation)
	{
		mRotation = rotation;
		updateModelMatrix();
	}

	void Transform::rotate(float angleDeg, const glm::vec3 &axis)
	{
		mRotation = glm::rotate(mRotation, angleDeg, axis);
		updateModelMatrix();
		updateOrientationVectors();
	}

	const glm::vec3& Transform::getSize() const
	{
		return mSize;
	}

	void Transform::setSize(const glm::vec3 &size)
	{
		mSize = size;
		updateModelMatrix();
	}

	const glm::vec3& Transform::getRight() const
	{
		return mRight;
	}

	const glm::vec3& Transform::getUp() const
	{
		return mUp;
	}

	const glm::vec3& Transform::getForward() const
	{
		return mForward;
	}

	const glm::mat4& Transform::getModelMatrix() const
	{
		return mModelMatrix;
	}

	const glm::mat4& Transform::getScaledModelMatrix() const
	{
		return mScaledModelMatrix;
	}

	void Transform::addChild(Transform &child)
	{
		child.removeFromParent();

		mParent = this;

		mChildren.push_back(&child);
	}

	void Transform::interpolate(const Transform &a, const Transform &b, float f)
	{
		f = glm::clamp(f, 0.0f, 1.0f);

		auto positionDiff = b.getPosition() - a.getPosition();
		mPosition = a.getPosition() + positionDiff * f;

		auto sizeDiff = b.getSize() - a.getSize();
		mSize = a.getSize() + sizeDiff * f;

		mRotation = glm::slerp(a.getRotation(), b.getRotation(), f);

		updateModelMatrix();
		updateOrientationVectors();
	}

	void Transform::updateModelMatrix()
	{
		mModelMatrix = glm::translate(glm::mat4(), mPosition);
		mModelMatrix *= glm::mat4_cast(mRotation);
		mScaledModelMatrix = glm::scale(mModelMatrix, mSize);

		mWorldPosition = glm::vec3(mModelMatrix[3][0], mModelMatrix[3][1], mModelMatrix[3][2]);
	}

	void Transform::updateOrientationVectors()
	{
		mRight = glm::rotate(mRotation, glm::vec3(1.0f, 0.0f, 0.0f));
		mUp = glm::rotate(mRotation, glm::vec3(0.0f, 1.0f, 0.0f));
		mForward = glm::rotate(mRotation, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void Transform::removeFromParent()
	{
		if(mParent)
		{
			auto &children = mParent->mChildren;
			auto it = std::find(children.begin(), children.end(), this);
			if(it != children.end())
				children.erase(it);
			mParent = nullptr;
		}
	}
}
