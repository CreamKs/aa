// 모델 버퍼 
#include "buffer.h"
#include "sphere.h"


std::vector<Vertex> vertices;
GLuint vertexCount = loadObj("sphere.obj", vertices);

GLuint VAO[MODEL_COUNT], VBO;  // MODEL_COUNT는 config.h에 정의되어있음


void vertexInput(int idx) {  // vertex
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	switch (idx) {  // 여기에 노말값이 담긴 버텍스 데이터 추가
	case 0:
		break;
	case 1:
		break;
	}
}

void setBuffer(int idx, int bufferMode) {
	if (bufferMode == modeInit) {  // bufferMode == modeUpdate 라면 해당 부분은 실행하지 않음
		glGenVertexArrays(1, &VAO[idx]);
		glBindVertexArray(VAO[idx]);
		glGenBuffers(1, &VBO);
	}

	if (bufferMode == modeInit || bufferMode == modeUpdate) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		vertexInput(idx);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
		glEnableVertexAttribArray(1);
	}
}
