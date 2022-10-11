#include <iostream>

#include "OGMesh.h"
#include "ResourceManager.h"
#include "glew/glew.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

OGMesh::OGMesh(const std::string& path)
{
	LoadMesh(path);
}

void OGMesh::Draw()
{
	//GLfloat x, y, z, nx, ny, nz, tx, ty;
	//int size = MeshData.size();
	//
	////if (MeshType == 4)
	////{
	////	glBegin(GL_TRIANGLES);
	////}
	////else if (MeshType == 8)
	//{
	//	glBegin(GL_QUADS);
	//}

	//for (int i = 0; i < size; i++)
	//{
	//	nx = MeshData[i].normal.x;
	//	ny = MeshData[i].normal.y;
	//	nz = MeshData[i].normal.z;

	//	glNormal3f(nx, ny, nz);

	//	if (TextCoordState)
	//	{
	//		tx = MeshData[i].texCoord.x;
	//		ty = MeshData[i].texCoord.y;

	//		glTexCoord2f(tx, ty);
	//	}

	//	x = MeshData[i].pos.x;
	//	y = MeshData[i].pos.y;
	//	z = MeshData[i].pos.z;
	//
	//	glVertex3f(x, y, z);
	//}
	//glEnd();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
}

void OGMesh::LoadMesh(const std::string &path)
{
	FileName = path;

	if (ResourceManager::Instance()->CheckMeshData(path))
	{
		std::cout << "Mesh data already exists : " << path << std::endl;
		MeshData = ResourceManager::Instance()->CheckMeshData(path)->GetMeshData();
		Indices = ResourceManager::Instance()->CheckMeshData(path)->GetIndicesData();
		VAO = ResourceManager::Instance()->CheckMeshData(path)->GetVAO();
		VBO = ResourceManager::Instance()->CheckMeshData(path)->GetVBO();
		EBO = ResourceManager::Instance()->CheckMeshData(path)->GetEBO();

		return;
	}
	else
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path.c_str(),
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs);

		if (!scene)
		{
			std::cout << "Mesh load failed!: " << path << std::endl;
			assert(0 == 0);
		}

		const aiMesh* model = scene->mMeshes[0];

		TextCoordState = model->HasTextureCoords(0) ? true : false;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < model->mNumVertices; i++)
		{
			const aiVector3D* pPos = &(model->mVertices[i]);
			const aiVector3D* pNormal = &(model->mNormals[i]);
			const aiVector3D* pTexCoord = TextCoordState ? &(model->mTextureCoords[0][i]) : &aiZeroVector;

			Vertex vert(glm::vec3(pPos->x, pPos->y, pPos->z),
				glm::vec2(pTexCoord->x, pTexCoord->y),
				glm::vec3(pNormal->x, pNormal->y, pNormal->z));

			MeshData.push_back(vert);
		}

		for (unsigned int i = 0; i < model->mNumFaces; i++)
		{
			const aiFace& face = model->mFaces[i];
			assert(face.mNumIndices == 3);
			Indices.push_back(face.mIndices[0]);
			Indices.push_back(face.mIndices[1]);
			Indices.push_back(face.mIndices[2]);
		}

		InitMesh();

		ResourceManager::Instance()->InsertMeshData(path, this);
	}
}

void OGMesh::InitMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, MeshData.size() * sizeof(Vertex), &MeshData[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);
}