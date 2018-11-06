#pragma once
#include "stdafx.h"
namespace OVLFunc
{
	inline void DXQuatToEuler(const DirectX::XMFLOAT4& q,DirectX::XMFLOAT3& euler )
	{
		double roll{}, pitch{}, yaw{};

		double test = q.x*q.y + -q.z*q.w;
		if (test > 0.499) { // singularity at north pole
			yaw = 2 * atan2(q.x, q.w);
			roll = DirectX::XM_PIDIV2;
			pitch = 0;
			return;
		}
		else if (test < -0.499) { // singularity at south pole
			yaw = -2 * atan2(q.x, q.w);
			roll = -DirectX::XM_PIDIV2 ;
			pitch = 0;
			return;
		}
		else
		{

			// roll (x-axis rotation)
			double sinr_cosp = +2.0 * (q.w * q.z + q.x * q.y);
			double cosr_cosp = +1.0 - 2.0 * (q.z * q.z + q.x * q.x);
			roll = atan2(sinr_cosp, cosr_cosp);

			// pitch (y-axis rotation)
			double sinp = +2.0 * (q.w * q.x - q.y * q.z);
			if (fabs(sinp) >= 1)
				pitch = copysign(DirectX::XM_PI / 2, sinp); // use 90 degrees if out of range
			else
				pitch = asin(sinp);

			// yaw (z-axis rotation)
			double siny_cosp = +2.0 * (q.w * q.y + q.z * q.x);
			double cosy_cosp = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
			yaw = atan2(siny_cosp, cosy_cosp);
		}
		euler.x = DirectX::XMConvertToDegrees( float(pitch));
		euler.y = DirectX::XMConvertToDegrees(float(yaw));
		euler.z = DirectX::XMConvertToDegrees(float(roll));
	}

	inline void PxEulerToAxisAngle(const physx::PxVec3 &euler, physx::PxVec4 & axisAngle)
	{
		double cy = cos(euler.y * 0.5);
		double sy = sin(euler.y * 0.5);
		double cr = cos(-euler.z * 0.5);
		double sr = sin(-euler.z * 0.5);
		double cp = cos(euler.x * 0.5);
		double sp = sin(euler.x * 0.5);


		axisAngle.w =float( cy * cr * cp + sy * sr * sp);
		axisAngle.z =float( cy * sr * cp - sy * cr * sp);
		axisAngle.x =float( cy * cr * sp + sy * sr * cp);
		axisAngle.y =float( sy * cr * cp - cy * sr * sp);
		
	}
	
}