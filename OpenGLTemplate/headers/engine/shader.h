#pragma once
#include "core.h"

namespace Engine {
	namespace Shader {
		struct Vertex {
			glm::vec3 position;
			glm::vec4 color;
		};

		GLuint createVAO();
		void createVBO(GLuint vaoID, GLsizeiptr verticesByteSize, const void* vertices, GLuint bindingIndex, int vertexLen, GLenum usage);
		void addVertexAttrib(GLuint vaoID, GLuint location, GLuint attribLen, GLuint offset, GLuint bindingIndex);
		void createEBO(GLuint vaoID, GLsizeiptr indicesByteSize, GLuint* indices, GLenum usage);
		void useVAO(GLuint vaoID);
		void unbindVAO();

		class Shader {
		private:
			unsigned int shaderID;

		public:
			Shader(const std::string& vertexPath, const std::string& fragmentPath);
			void use();
			void setBool(const std::string& name, bool value);
			void setInt(const std::string& name, int value);
			void setFloat(const std::string& name, float value);
			void setMat3(const std::string& name, const GLfloat* mat);
			void setMat4(const std::string& name, const GLfloat* mat);
			void setVec2(const std::string& name, glm::vec2 vec);
			void setVec3(const std::string& name, glm::vec3 vec);
			void setVec4(const std::string& name, glm::vec4 vec);
		};
	}
}
