#ifndef Parameter_h_
#define Parameter_h_

class IParameter
{
public:
	virtual bool isParameter(void) const { return true; }
};

template <typename T>
class Parameter : public IParameter
{
protected:
	T value;

public:
	Parameter(const T & v)
	{
		value = v;
	}

	T getParameter(void) const { return value; }
};

#endif