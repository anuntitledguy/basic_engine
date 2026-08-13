#ifndef IOBJECT_H
#define IOBJECT_H

#include <iostream>

class Iobject
{
	public:
		virtual ~Iobject()=default;
		
		virtual void Update(double dt)=0;
		virtual void Draw()=0;
	
	private:
		std::string m_id;
};

#endif
