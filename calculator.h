#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <ctgmath>

class Calculator
{
public:

	double dDensityMSL = 1.225;
	double dPressureMSL = 101325;
	double dGravity = 9.80665;
	double dCdA = 0.5217;
	double dCr = 0.0033;
	double dCm = 0.9;

	float density(float temp, float heightAmsl)
	{
		double dDensity;
		dDensity = dDensityMSL * (373 / temp) * exp(-dDensityMSL * dGravity * (heightAmsl / dPressureMSL));
		return dDensity;
	}

	float varA(float windSpeed, float Crvn, float Frg, float rho, float power)
	{
		float varA;
		float arg1 = pow(windSpeed, 3);
		float arg2 = pow(Crvn, 3);
		float arg2a = (arg1 - arg2) / 27;
		float arg3 = 5 * windSpeed * Crvn;
		float arg4 = 8 * pow(Crvn, 2);
		float arg5 = dCdA * rho;
		float arg5a = arg4 / arg5;
		float arg5b = arg3 + arg5a - 6 * Frg;
		float arg5c = windSpeed * arg5b;
		float arg6 = 9 * dCdA * rho;
		float arg6a = arg5c / arg6;
		float arg7 = 2 * Frg * Crvn;
		float arg8 = dCdA * rho;
		float arg9 = pow(arg8, 2);
		float arg10 = 3 * arg9;
		float arg10a = arg7 / arg10;
		float arg11 = dCm * dCdA * rho;
		float arg12 = power / arg11;
				
		varA = arg2a - arg6a + arg10a + arg12;
		return varA;
	}

	float varB(float windSpeed, float Crvn, float Frg, float rho)
	{
		float varB;
		float arg1 = 9 * dCdA*rho;
		float arg2 = 2 / arg1;
		float arg3 = 3 * Frg;
		float arg4 = 4 * windSpeed * Crvn;
		float arg5 = pow(windSpeed, 2);
		float arg6 = arg5 * dCdA * (rho / 2);
		float arg7 = 2 * Crvn;
		float arg8 = dCdA * rho;
		float arg9 = arg7 / arg8;
		float arg10 = arg3 - arg4 - arg6 - arg9;

		varB = arg2 * arg10;
		return varB;
	}

	float speed(float varA, float varB, float windSpeed, float Crvn, float rho)
	{
		float speed;
		float half = 1 / 2;
		float third = 1 / 3;

		float arg1 = pow(varA, 2);
		float arg2 = pow(varB, 3);
		float arg3 = arg1 + arg2;
		float arg4 = sqrt(arg3);
		float arg5 = varA + arg4;
		float arg6 = cbrt(arg5);
		float arg7 = varA - arg4;
		float arg8 = cbrt(arg7);
		float arg9 = dCdA * rho;
		float arg10 = Crvn / arg9;
		float arg11 = windSpeed + arg10;
		float arg12 = (2 / 3) * arg11;
		
		float speedMS = arg6 + arg8 - arg12;
		speed = speedMS * 3.6;
		return speed;
	}

	float rollingFriction(float massBike, float massRider, float slope)
	{
		float centiSlope = slope / 100;
		float beta = atan(centiSlope);

		float rollingFriction;

		rollingFriction = dGravity * (massBike + massRider) * (dCr*cos(beta) + sin(beta));
		return rollingFriction;
	}
};
