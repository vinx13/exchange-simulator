#ifndef EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H
#define EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H


class MessageHandler {
public:
    virtual Fix42::MessagePtr accept(const Fix42::MessagePtr message) = 0;

    ~MessageHandler() { }
};


#endif //EXCHANGESIMULATOR_SERVER_MESSAGEHANDLER_H
