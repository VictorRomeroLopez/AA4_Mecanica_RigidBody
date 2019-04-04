#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <time.h>

namespace Box {
	void drawCube();
}
namespace Axis {
	void drawAxis();
}

namespace Sphere {
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
	extern void drawSphere();
}
namespace Capsule {
	extern void updateCapsule(glm::vec3 posA, glm::vec3 posB, float radius = 1.f);
	extern void drawCapsule();
}
namespace Particles {
	extern const int maxParticles;
	extern void updateParticles(int startIdx, int count, float* array_data);
	extern void drawParticles(int startIdx, int count);
}
namespace Mesh {
	extern const int numCols;
	extern const int numRows;
	extern void updateMesh(float* array_data);
	extern void drawMesh();
}
namespace Fiber {
extern const int numVerts;
	extern void updateFiber(float* array_data);
	extern void drawFiber();
}
namespace Cube {
	extern void updateCube(const glm::mat4& transform);
	extern void drawCube();
}

// Boolean variables allow to show/hide the primitives
bool renderSphere = false;
bool renderCapsule = false;
bool renderParticles = false;
bool renderMesh = false;
bool renderFiber = false;
bool renderCube = false;

#pragma region GUI_VARIABLES
float spherePositions[3][3];
float sphereRadiuses[3]{.5f,.75f,1};
float timer = 0;
float timeToRestart = 0.1f;
#pragma endregion

//You may have to change this code
void renderPrims() {
	Box::drawCube();
	Axis::drawAxis();

	if (renderSphere)
		Sphere::drawSphere();
	if (renderCapsule)
		Capsule::drawCapsule();

	if (renderParticles) {
		int startDrawingFromParticle = 0;
		int numParticlesToDraw = Particles::maxParticles;
		Particles::drawParticles(startDrawingFromParticle, numParticlesToDraw);
	}

	if (renderMesh)
		Mesh::drawMesh();
	if (renderFiber)
		Fiber::drawFiber();

	if (renderCube)
		Cube::drawCube();

	for (int i = 0; i < 3; i++) {
		Sphere::drawSphere();
		Sphere::updateSphere(glm::vec3(spherePositions[i][0], spherePositions[i][1], spherePositions[i][2]), sphereRadiuses[i]);
	}
}


void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);

	// Do your GUI code here....
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		ImGui::DragFloat("Random time reset", &timeToRestart, 0.1f, 0.1f, 20);
		
		if (ImGui::TreeNode("Sphere 1")) {
			ImGui::DragFloat3("Center", spherePositions[0], 0.01f);
			ImGui::DragFloat("Radius", &sphereRadiuses[0], 0.01f, 0.1f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Sphere 2")) {
			ImGui::DragFloat3("Center", spherePositions[1], 0.01f);
			ImGui::DragFloat("Radius", &sphereRadiuses[1], 0.01f, 0.1f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Sphere 3")) {
			ImGui::DragFloat3("Center", spherePositions[2], 0.01f);
			ImGui::DragFloat("Radius", &sphereRadiuses[2], 0.01f, 0.1f, 1);
			ImGui::TreePop();
		}
	}
	// .........................
	
	ImGui::End();

	// Example code -- ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	bool show_test_window = false;
	if(show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void resetSpheresPositions() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (j == 1)
				spherePositions[i][j] = rand() % 8 + 1;
			else
				spherePositions[i][j] = rand() % 8 - 4;
		}
	}
}

void PhysicsInit() {
	// Do your initialization code here...
	srand(time(NULL));
	resetSpheresPositions();
	// ...................................
}

void PhysicsUpdate(float dt) {
	// Do your update code here...
	timer += dt;
	if (timer >= timeToRestart) {
		resetSpheresPositions();
		timer = 0;
	}

	// ...........................
}

void PhysicsCleanup() {
	// Do your cleanup code here...
	// ............................
}