#pragma once

template<class... Ts>
struct Overloaded : Ts... {
	using Ts::operator()...;
};

template<class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;
