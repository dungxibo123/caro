#include "Data.h"

bool _PLAYER::operator>(_PLAYER other)
{
	if (this->wins > other.wins) return true;
	else return false;
}

bool _PLAYER::operator<(_PLAYER other)
{
	if (this->wins < other.wins) return true;
	else return false;
}

bool _PLAYER::operator==(_PLAYER other)
{
	if (this->name == other.name) return true;
	else return false;
}
