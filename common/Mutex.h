#ifndef _C_MUTEX_H_
#define _C_MUTEX_H_

#ifdef WIN32
#include "windows.h"
#else
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#endif

// class to encapsulate mutex logic across Win32/Unix
class CMutex
{
public:
	CMutex();
	virtual ~CMutex();

	void	lock();
	void	unlock();

	class CGuard
	{
	public:
		CGuard( CMutex &mutex ) : _mutex( mutex ) { _mutex.lock(); }
		~CGuard()								  { _mutex.unlock(); }
	private:
		CMutex &_mutex;

		// Declared, but not implemented to prevent default behavior generated by compiler
		CGuard( const CGuard & );
		CGuard & operator=( const CGuard & );
	};

private:
#ifdef WIN32
	CRITICAL_SECTION		_cs;
#else
	pthread_mutex_t			_mutex;
	pthread_cond_t			_cv;
#endif

private:
// Declared, but not implemented to prevent default behavior generated by compiler
	CMutex( const CMutex & );
	CMutex & operator=( const CMutex & );
};

#endif // _MUTEX_H_

