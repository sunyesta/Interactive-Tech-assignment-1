
#pragma once
#ifndef LOOPABLE_HPP
#define LOOPABLE_HPP

class LoopManager;

class Loopable {
   public:
    int index;
    Loopable();
    virtual void loop();
};

#endif /* LOOPABLE_HPP */