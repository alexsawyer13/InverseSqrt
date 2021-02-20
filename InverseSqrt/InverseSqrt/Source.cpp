#include <iostream>

constexpr int constant = 1597526528;
constexpr float threehalves = 1.5F;

float ApproxInverseSqrt(float input)
{
	uint32_t bits = *(uint32_t*)&input;

	uint32_t ans = constant - (bits >> 1);

	float answer = *(float*)&ans;

	return answer;
}

float InverseSqrt(float input)
{
	return powf(input, -0.5);
}

int CalculateConstant(float mu)
{
	return (int) (3.0f * (float) pow(2, 22) * (127.0f - mu));
}

float NewtonsMethod(float input)
{
	float x1 = ApproxInverseSqrt(input);

	float x2 = x1 * (threehalves - 0.5f * x1 * x1 * input);

	return x2;
}

void BothInverseSqrt(float input)
{
	float exact = InverseSqrt(input);
	float approx = ApproxInverseSqrt(input);
	std::cout << "Inverse sqrt of " << input << " = " << exact << "\n"
		<< "Approximation = " << approx << "\n"
		<< "Percentage difference = " << abs((exact - approx) / exact * 100) << "\n";
}

float NewtonsImprovement(float input)
{
	float exact = InverseSqrt(input);
	float approx = ApproxInverseSqrt(input);
	float newtons = NewtonsMethod(input);
	float approxPercentage = abs((exact - approx) / exact * 100);
	float newtonsPercentage = abs((exact - newtons) / exact * 100);
	//std::cout << "Inverse sqrt of " << input << " = " << exact << "\n"
	//	<< "Newton's approximation = " << newtons << "\n"
	//	<< "Percentage difference = " << newtonsPercentage << "\n\n";
	return newtonsPercentage;
}

int main()
{
	int n = 100000;
	float total = 0.0f;
	for (int i = 1; i < n; i++)
	{

		total += NewtonsImprovement(i);
	}

	float average = total / (float) n;

	std::cout << "\n\nThe average percentage error is " << average << "\n";

	return 0;
}