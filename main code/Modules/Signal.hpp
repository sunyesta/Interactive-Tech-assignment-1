#pragma once
#ifndef SIGNAL_HPP
#define SIGNAL_HPP

// reference to static section:
// https://blog.mbedded.ninja/programming/languages/c-plus-plus/callbacks/

class Signal {
   private:
    class Callback {
       private:
        void (*callback)();  // variable storing a callback

       public:
        template <typename ItemType>
        Callback(void (*callback)()) {
            this->callback = callback;
        }
        void call() { this->callback(); }
    };

    Callback **callbacks;
    int callbacksSpace = 1;
    int callbacksCount = 0;

   public:
    Signal();

    void connect(void (*callbackFunc)()) {
        Callback *callback = new Callback(callbackFunc);

        callbacksCount += 1;

        if (callbacksSpace < callbacksCount) {
            callbacksSpace = 2 * callbacksSpace;
            realloc(callbacks, callbacksSpace);
        }

        // adding callback to callbacks list
        callbacks[callbacksCount - 1] = callback;
    };

    void Fire() {
        for (int i = 0; i < callbacksCount; i++) {
            callbacks[i]->call();  // calling callback
        }
    }
    void Signal_exampleUsage() {
        Signal *sig = new Signal();

        auto printHappy = []() { Serial.println("happy!!!!"); };
        sig->connect(printHappy);
    }

#endif /* SIGNAL_HPP */