#include "Serialization.h"
#include "stdafx.h"
#include "Serialization.h"

void Serialization::YAMLOutVar(char * name, DirectX::XMFLOAT3 var, YAML::Emitter & out)
{
	
	out << YAML::Key << name;
	out << YAML::Flow;
	out << YAML::BeginSeq << var.x << var.y << var.z << YAML::EndSeq;

}

void Serialization::YAMLOutVar(char * name, physx::PxVec3 var, YAML::Emitter & out)
{
	out << YAML::Key << name;
	out << YAML::Flow;
	out << YAML::BeginSeq << var.x << var.y << var.z << YAML::EndSeq;
}

void Serialization::YAMLOutVar(char * name, DirectX::XMFLOAT4 var, YAML::Emitter & out)
{

	out << YAML::Key << name;
	out << YAML::Flow;
	out << YAML::BeginSeq << var.x << var.y << var.z << var.w << YAML::EndSeq;

}

void Serialization::YAMLOutVar(char * name, physx::PxFilterData var, YAML::Emitter & out)
{
	out << YAML::Key << name;
	out << YAML::Flow;
	out << YAML::BeginSeq << var.word0 << var.word1 << var.word2 << var.word3 << YAML::EndSeq;
}

void Serialization::YAMLOutVar(char * name, const physx::PxMaterial & var, YAML::Emitter & out)
{
	out << YAML::Key << name;
	out << YAML::Flow;
	out << YAML::BeginSeq << var.getStaticFriction()
		<< var.getDynamicFriction() << var.getRestitution() << YAML::EndSeq;

}

void Serialization::YAMLOutVar(char * name, const physx::PxMaterial * var, YAML::Emitter & out)
{
	out << YAML::Key << name;
	out << YAML::Flow;
	out << YAML::BeginSeq << var->getStaticFriction()
		<< var->getDynamicFriction() << var->getRestitution() << YAML::EndSeq;
}

void Serialization::YAMLOutVar(char * name, shared_ptr<physx::PxGeometry> var, YAML::Emitter & out)
{
	int type = var->getType();
	out << YAML::Key << name;
	out << YAML::Flow;

	switch (type)
	{
	case 0://sphere
		//out << YAML::BeginSeq << type << dynamic_cast<physx::PxSphereGeometry*>(var.get());
		break;


	default:
		break;
	}
}

void Serialization::YAMLParseVar(char * name, DirectX::XMFLOAT3& var, YAML::Node & node)
{
	YAML::Node values = node[name];
	var.x = values[0].as<float>();
	var.y = values[1].as<float>();
	var.z = values[2].as<float>();


}

void Serialization::YAMLParseVar(char * name, physx::PxVec3 & var, YAML::Node & node)
{
	YAML::Node values = node[name];
	var.x = values[0].as<float>();
	var.y = values[1].as<float>();
	var.z = values[2].as<float>();
}

void Serialization::YAMLParseVar(char * name, DirectX::XMFLOAT4& var, YAML::Node & node)
{
	YAML::Node values = node[name];
	var.x = values[0].as<float>();
	var.y = values[1].as<float>();
	var.z = values[2].as<float>();
	var.w = values[3].as<float>();

}

void Serialization::YAMLParseVar(char * name, physx::PxFilterData& var, YAML::Node & node)
{
	YAML::Node values = node[name];
	var.word0 = values[0].as<physx::PxU32>();
	var.word1 = values[1].as<physx::PxU32>();
	var.word2 = values[2].as<physx::PxU32>();
	var.word3 = values[3].as<physx::PxU32>();
}

void Serialization::YAMLParseVar(char * name, physx::PxMaterial & var, YAML::Node & node)
{
	YAML::Node values = node[name];
	var.setStaticFriction( values[0].as<physx::PxReal>());
	var.setDynamicFriction(values[1].as<physx::PxReal>());
	var.setRestitution(values[2].as<physx::PxReal>());

}

void Serialization::YAMLParseVar(char * name, physx::PxGeometry & var, YAML::Node & node)
{
	node;
	name;
	var;
	
	
}

