#ifndef _EngineEvent_HPP_
#define _EngineEvent_HPP_

enum EngineEvent
{
	UP,
    DOWN,
	RIGHT,
	LEFT,
	ACTION,

    COUNT // trick to get enum length
    // C++ spec: If the first enumerator has no initializer, 
    // the value of the corresponding constant is zero.
};

#endif
