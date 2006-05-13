///@file observable.h Contains observed part of pattern Observer

#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

#include "observer.h"
#include "destroyable.h"

#include "stl_ext.h"

namespace xicor {

    ///@brief Parent class for Observer storage management
    /// ability.
    class Observable: public iDestroyable {
    protected:
        List<iObserver*> observer_list;
    public:
        ///@brief Adds observer to the list. No error checks.
        virtual void attachObserver(iObserver* const observer)
        {
            observer_list.push_back(observer);
            observer_list.unique();
        }

        ///@brief Removes observer from the list. No error checks.
        virtual void detachObserver(iObserver* const observer)
        {
            observer_list.remove(observer);
        }

        ///@brief Updates observers from the list. No error checks.
        virtual void notifyObservers()
        {
            List<iObserver*>::iterator itr;
            for(itr = observer_list.begin(); itr != observer_list.end(); itr++)
                (*itr)->updateObserved();
        }
    };

} //namespace xicor

#endif //_OBSERVABLE_H_
