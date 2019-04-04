#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <glm\gtc\matrix_transform.hpp>

struct Collider {

	virtual bool checkCollision(const glm::vec3& next_pos, float radius) = 0;

	float computeImpulseCorrection(float massA, glm::vec3 ra, glm::mat3 invIa, float massB, glm::vec3 rb, glm::mat3 invIb, float vrel, float epsilon, glm::vec3 normal) {

	}

	void updateColliders(Collider* A, Collider* B) {

	}
};

struct RigidSphere :Collider {
	bool checkCollision(const glm::vec3& next_pos, float radius) override {
		return true;
	}
};

struct PlaneCol : Collider {
	bool checkCollision(const glm::vec3& next_pos, float radius) override {
		return true;
	}
};