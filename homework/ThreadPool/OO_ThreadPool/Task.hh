#ifndef __TASK_HPP__
#define __TASK_HPP__

class Task {
public:
    Task() = default;
    virtual ~Task() {}
    
    virtual void process() = 0;
};

#endif
