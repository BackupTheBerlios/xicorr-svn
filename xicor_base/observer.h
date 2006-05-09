///@file observer.h Contains observer part of pattern Observer interface

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

namespace xicor {
	class Observable;
}

namespace xicor {

	///@brief Interface class represents ability to be notified about
	/// raised events.
	class iObserver {
	public:
		///@brief This method will be used by observed class to notify
		/// observer about changes without any data about them.
		virtual void updateObserved () = 0;
	};

} //namespace xicor

#endif //_OBSERVER_H_
