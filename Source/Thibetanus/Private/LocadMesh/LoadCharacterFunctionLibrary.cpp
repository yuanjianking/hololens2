// Fill out your copyright notice in the Description page of Project Settings.


#include "LocadMesh/LoadCharacterFunctionLibrary.h"
#include "Engine.h"
#include <string>
#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
//
//void FindMeshInfo(const aiScene* scene, aiNode* node, FReturnedData& result)
//{
//
//	for (uint32 i = 0; i < node->mNumMeshes; i++)
//	{
//		std::string TestString = node->mName.C_Str();
//		FString Fs = FString(TestString.c_str());
//		UE_LOG(LogTemp, Warning, TEXT("FindMeshInfo. %s\n"), *Fs);
//		int meshidx = *node->mMeshes;
//		aiMesh* mesh = scene->mMeshes[meshidx];
//		FMeshInfo& mi = result.meshInfo[meshidx];
//
//		//transform.
//		aiMatrix4x4 tempTrans = node->mTransformation;
//		FMatrix tempMatrix;
//		tempMatrix.M[0][0] = tempTrans.a1; tempMatrix.M[0][1] = tempTrans.b1; tempMatrix.M[0][2] = tempTrans.c1; tempMatrix.M[0][3] = tempTrans.d1;
//		tempMatrix.M[1][0] = tempTrans.a2; tempMatrix.M[1][1] = tempTrans.b2; tempMatrix.M[1][2] = tempTrans.c2; tempMatrix.M[1][3] = tempTrans.d2;
//		tempMatrix.M[2][0] = tempTrans.a3; tempMatrix.M[2][1] = tempTrans.b3; tempMatrix.M[2][2] = tempTrans.c3; tempMatrix.M[2][3] = tempTrans.d3;
//		tempMatrix.M[3][0] = tempTrans.a4; tempMatrix.M[3][1] = tempTrans.b4; tempMatrix.M[3][2] = tempTrans.c4; tempMatrix.M[3][3] = tempTrans.d4;
//		mi.RelativeTransform = FTransform(tempMatrix);
//
//		//vet
//		for (uint32 j = 0; j < mesh->mNumVertices; ++j)
//		{
//			FVector vertex = FVector(
//				mesh->mVertices[j].x,
//				mesh->mVertices[j].y,
//				mesh->mVertices[j].z);
//
//			vertex = mi.RelativeTransform.TransformFVector4(vertex);
//			mi.Vertices.Push(vertex);
//
//			//Normal
//			if (mesh->HasNormals())
//			{
//				FVector normal = FVector(
//					mesh->mNormals[j].x,
//					mesh->mNormals[j].y,
//					mesh->mNormals[j].z);
//
//				//normal = mi.RelativeTransform.TransformFVector4(normal);
//				mi.Normals.Push(normal);
//			}
//			else
//			{
//				mi.Normals.Push(FVector::ZeroVector);
//			}
//
//			//UV Coordinates - inconsistent coordinates
//			if (mesh->HasTextureCoords(0))
//			{
//				FVector2D uv = FVector2D(mesh->mTextureCoords[0][j].x, -mesh->mTextureCoords[0][j].y);
//				mi.UV0.Add(uv);
//			}
//
//			//Tangent
//			if (mesh->HasTangentsAndBitangents())
//			{
//				FProcMeshTangent meshTangent = FProcMeshTangent(
//					mesh->mTangents[j].x,
//					mesh->mTangents[j].y,
//					mesh->mTangents[j].z
//				);
//				mi.Tangents.Push(meshTangent);
//			}
//
//			//Vertex color
//			if (mesh->HasVertexColors(0))
//			{
//				FLinearColor color = FLinearColor(
//					mesh->mColors[0][j].r,
//					mesh->mColors[0][j].g,
//					mesh->mColors[0][j].b,
//					mesh->mColors[0][j].a
//				);
//				mi.VertexColors.Push(color);
//			}
//
//		}
//	}
//}
//
//
//void FindMesh(const aiScene* scene, aiNode* node, FReturnedData& retdata)
//{
//	FindMeshInfo(scene, node, retdata);
//
//	for (uint32 m = 0; m < node->mNumChildren; ++m)
//	{
//		FindMesh(scene, node->mChildren[m], retdata);
//	}
//}
//
//


FReturnedData ULoadCharacterFunctionLibrary::LoadMesh(FString filepath, EPathType type)
{
	FReturnedData result;
	result.bSuccess = false;
	result.meshInfo.Empty();
	result.NumMeshes = 0;

	if (filepath.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT(""));
		return result;
	}

	std::string file;
	switch (type)
	{
	case EPathType::Absolute:
		file = TCHAR_TO_UTF8(*filepath);
		break;
	case EPathType::Relative:
		file = TCHAR_TO_UTF8(*FPaths::Combine(FPaths::ProjectContentDir(), filepath));
		break;
	}

	//Assimp::Importer mImporter;

	//const aiScene* mScenePtr = mImporter.ReadFile(file, aiProcess_Triangulate | aiProcess_MakeLeftHanded | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes);

	/*if (mScenePtr == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(""));
		return result;
	}*/

	//if (mScenePtr->HasMeshes())
	//{
	//	result.meshInfo.SetNum(mScenePtr->mNumMeshes, false);

	////	FindMesh(mScenePtr, mScenePtr->mRootNode, result);

	//	for (uint32 i = 0; i < mScenePtr->mNumMeshes; ++i)
	//	{
	//		//Triangle number
	//		for (uint32 l = 0; l < mScenePtr->mMeshes[i]->mNumFaces; ++l)
	//		{
	//			for (uint32 m = 0; m < mScenePtr->mMeshes[i]->mFaces[l].mNumIndices; ++m)
	//			{
	//				result.meshInfo[i].Triangles.Push(mScenePtr->mMeshes[i]->mFaces[l].mIndices[m]);
	//			}
	//		}
	//	}

	//	result.bSuccess = true;
	//}

	return result;
}
//
//TArray<FString> ULoadCharacterFunctionLibrary::GetAllFilesInDirectory(const FString directory, const bool fullPath, const bool withoutExtention, const FString onlyFilesStartingWith, const FString onlyFilesWithExtension)
//{
//	// Get all files in directory
//	TArray<FString> directoriesToSkip;
//	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//	FLocalTimestampDirectoryVisitor Visitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
//	PlatformFile.IterateDirectory(*directory, Visitor);
//	TArray<FString> files;
//
//	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
//	{
//		const FString filePath = TimestampIt.Key();
//		const FString fileName = FPaths::GetCleanFilename(filePath);
//		bool shouldAddFile = true;
//
//		if (!onlyFilesStartingWith.IsEmpty())
//		{
//			const FString left = fileName.Left(onlyFilesStartingWith.Len());
//
//			if (!(fileName.Left(onlyFilesStartingWith.Len()).Equals(onlyFilesStartingWith)))
//				shouldAddFile = false;
//		}
//
//		if (!onlyFilesWithExtension.IsEmpty())
//		{
//			if (!(FPaths::GetExtension(fileName, false).Equals(onlyFilesWithExtension, ESearchCase::IgnoreCase)))
//				shouldAddFile = false;
//		}
//
//
//		if (shouldAddFile)
//		{
//			if (withoutExtention)
//				files.Add(fullPath ? filePath : FPaths::GetBaseFilename(filePath));
//			else
//				files.Add(fullPath ? filePath : FPaths::GetCleanFilename(filePath));
//		}
//	}
//
//	return files;
//}
