// 모델 변환 
#include "translate.h"
//모델 좌표 cpp파일은 여기에 임포트 -> ex) #include "cube_ebo.cpp"
#include "sphere.h"

extern GLuint ID;
extern GLuint VAO[MODEL_COUNT];  // MODEL_COUNT는 config.h에 정의되어있음

glm::vec3 cameraPos, cameraDirection, cameraUp;
glm::vec3 lightPos, lightColor, objColor;
glm::mat4 transformMatrix, view, projection, LightTrans;

unsigned int projectionLocation, viewLocation, modelLocation, viewPosLocation;
unsigned int lightPosLocation, lightColorLocation, objColorLocation;


void finishTransform(int idx) {  // 변환 전달 
	projectionLocation = glGetUniformLocation(ID, "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	viewLocation = glGetUniformLocation(ID, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	lightPosLocation = glGetUniformLocation(ID, "lightPos"); // lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, lightPos.x, lightPos.y, lightPos.z);

	lightColorLocation = glGetUniformLocation(ID, "lightColor"); // lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, lightColor.x, lightColor.y, lightColor.z);

	objColorLocation = glGetUniformLocation(ID, "objectColor"); // object Color값 전달: (1.0, 0.5, 0.3)의 색
	glUniform3f(objColorLocation, objColor.x, objColor.y, objColor.z);

	viewPosLocation = glGetUniformLocation(ID, "viewPos"); // viewPos 값 전달: 카메라 위치
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

	modelLocation = glGetUniformLocation(ID, "model"); // 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix)); // modelTransform 변수에 변환 값 적용하기

	glBindVertexArray(VAO[idx]);  // 각 모델마다 지정된 VAO만 사용
}

void setCamera() {  // 카메라 세팅
	using namespace glm;
	view = mat4(1.0f);
	cameraPos = vec3(0.0f, 0.0f, 100.0f);
	cameraDirection = vec3(0.0f, 0.0f, 0.0f);
	cameraUp = vec3(0.0f, 1.0f, 0.0f);
	view = lookAt(cameraPos, cameraDirection, cameraUp);
}

void setProjection(int projectionMode) {  // 투영 세팅
	using namespace glm;
	projection = mat4(1.0f);
	switch (projectionMode) {
	case modePers:
		projection = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);
		break;
	case modeOrtho:
		projection = ortho(-3.0f, 3.0f, -3.0f, 3.0f, 1.0f, 100.0f);
		break;
	}
}

void setLight() {  // 조명 세팅
	using namespace glm;
	lightPos = vec3( 0.0f, 0.0f, 100.0f);  // 조명 위치
	lightColor = vec3(1.0f, 1.0f, 1.0f);
}

void setTransformLight(int idx) {
	glm::vec4 temp = glm::vec4(lightPos.x, lightPos.y, lightPos.z, 1.0f);
	LightTrans = glm::mat4(1.0f);
	LightTrans = glm::translate(LightTrans, glm::vec3(lightPos));
	if (idx == 1) LightTrans = glm::rotate(LightTrans, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	if(idx == 2) LightTrans = glm::rotate(LightTrans, glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	lightPos = glm::vec3(temp * LightTrans);
}

void setColorLight(int idx) {
	if (idx == 1) lightColor = glm::vec3(1.0f, 0.0f, 0.0f);
	if (idx == 2) lightColor = glm::vec3(0.0f, 1.0f, 0.0f);
	if (idx == 3) lightColor = glm::vec3(0.0f, 0.0f, 1.0f);
}

void setTransform(int idx) {  // 변환 세팅
	using namespace glm;
	transformMatrix = mat4(1.0f);
	switch (idx) {  // 변환 추가 
	case 0:
		transformMatrix = glm::scale(transformMatrix, glm::vec3(1.0, 1.0, 1.0));
		objColor = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case 1:
		transformMatrix = glm::scale(transformMatrix, glm::vec3(0.7, 0.7, 0.7));
		objColor = glm::vec3(0.0f, 1.0f, 0.0f);
		transformMatrix = glm::translate(transformMatrix, glm::vec3(-27.0, 0.0, 0.0));
		break;
	case 2:
		transformMatrix = glm::scale(transformMatrix, glm::vec3(0.5, 0.5, 0.5));
		objColor = glm::vec3(0.0f, 0.0f, 1.0f);
		transformMatrix = glm::translate(transformMatrix, glm::vec3(-60.0, 0.0, 0.0));
		break;
	}
}

void modelOutput(int idx) {  // 모델 출력 
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());  // 큐브 출력
}
