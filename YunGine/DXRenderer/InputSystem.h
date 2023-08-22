#pragma once
#include <vector>
#include <functional>

template<int N>
extern std::vector<std::function<void()>> inputkeybuffer;

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	template<int N>
	void ResistInput(std::function<void()> func)
	{
		inputkeybuffer<N>.push_back(func);
	}

	template<int N>
	void OnInput()
	{
		for (auto func : inputkeybuffer<N>)
		{
			func();
		}
	}
};

