#ifndef __DEFINE_H__
#define __DEFINE_H__
#define GET_SET(__TYPE__,__NAME__)\
private:\
	__TYPE__ m_##__NAME__; \
public:\
	inline void set##__NAME__(__TYPE__ new_value)\
	{\
	m_##__NAME__ = new_value; \
	}\
	inline __TYPE__ get##__NAME__()\
	{\
	return m_##__NAME__; \
	}
#define GET_SET_POINTER(__TYPE__,__NAME__)\
private:\
	__TYPE__ *m_##__NAME__; \
public:\
	inline void set##__NAME__(__TYPE__ *new_value)\
	{\
	m_##__NAME__ = new_value; \
	}\
	inline __TYPE__* get##__NAME__()\
	{\
	return m_##__NAME__; \
	}

enum ResourceType
{
	ATLAS,TEXTURE
};




#endif