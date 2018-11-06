#pragma once
#include <yaml-cpp/yaml.h>
#define SERIALIZE_VAR(var,YAMLOut) Serialization::YAMLOutVar(#var,var,YAMLOut)
#define PARSE_VAR(var,YAMLNode) Serialization::YAMLParseVar(#var,var,YAMLNode)


class Serialization
{
public:

	template <class T>
	static void YAMLOutVar(char* name, T var, YAML::Emitter& out)
	{
		out << YAML::Key << string(name);
		out << YAML::Value << var;
	}
	//template <class T>
	//static void YAMLOutVar(char* name, T* var, YAML::Emitter& out)
	//{
	//	out << YAML::Key << string(name);
	//	out << YAML::Value << *var;
	//}
	static void YAMLOutVar(char* name, DirectX::XMFLOAT3 var, YAML::Emitter& out);
	static void YAMLOutVar(char* name, physx::PxVec3 var, YAML::Emitter& out);
	static void YAMLOutVar(char* name, DirectX::XMFLOAT4 var, YAML::Emitter& out);
	static void YAMLOutVar(char* name, physx::PxFilterData var, YAML::Emitter& out);
	static void YAMLOutVar(char* name, const physx::PxMaterial& var, YAML::Emitter& out);
	static void YAMLOutVar(char* name, const physx::PxMaterial* var, YAML::Emitter& out);

	static void YAMLOutVar(char* name, shared_ptr< physx::PxGeometry> var, YAML::Emitter& out);


	template <class T>
	static void YAMLParseVar(char* name, T& var, YAML::Node& node)
	{
		var = node[name].as<T>();
	}
	
	static void YAMLParseVar(char* name, DirectX::XMFLOAT3& var, YAML::Node& node);
	static void YAMLParseVar(char* name, physx::PxVec3& var, YAML::Node& node);
	static void YAMLParseVar(char* name, DirectX::XMFLOAT4& var, YAML::Node& node);
	static void YAMLParseVar(char* name, physx::PxFilterData& var, YAML::Node& node);
	static void YAMLParseVar(char* name, physx::PxMaterial& var, YAML::Node& node);
	static void YAMLParseVar(char* name, physx::PxGeometry& var, YAML::Node& node);



};

